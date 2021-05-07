#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView_2->setModel(tmpmateriel.afficher());
     ui->tableView->setModel(tmptravaille.afficher());//refresh



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_4_clicked()
{
    QString mat,model,etat,groupe;




    if( ui->lineEdit_7->text().isEmpty() || ui->lineEdit_8->text().isEmpty()|| ui->lineEdit_9->text().isEmpty() )
    {
        ui->tableView_2->setModel(tmpmateriel.afficher());//refresh
        QMessageBox::warning(nullptr, QObject::tr("Attention"),
                             QObject::tr("Veuillez remplir tout les champs.\n"), QMessageBox::Ok);
    }
    else{
        mat=ui->lineEdit_7->text();
        model=ui->lineEdit_8->text();
        groupe=ui->lineEdit_9->text();



        if (ui->comboBox_2->currentIndex()==0)
            etat="marche";
        else {
            etat="en panne";
        }


        materiel m(mat,model,etat,groupe );
        bool test=m.ajouter();

        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("Ajouter un   materiel"),
                                     QObject::tr("  materiel ajouté.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView_2->setModel(tmpmateriel.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un  materiel"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString mat,model,etat,groupe;


    mat=ui->lineEdit_20->text();

    if (ui->comboBox_3->currentIndex()==0)
        etat="marche";
    else {
        etat="en panne";
    }



    materiel m(mat,model,etat,groupe);
    bool test= m.modifier(mat);

    if (test)
    {
        musicAdd.setMedia(QUrl("C:/Users/houssem/Desktop/Atelier_Connexion/Resources/modif succe.mp3"));
        musicAdd.play();
        QMessageBox::information(nullptr, QObject::tr("Modifier un   materiel"),
                                 QObject::tr("  materiel Modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_2->setModel(tmpmateriel.afficher());//refresh
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un materiel"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString mat = ui->lineEdit_12->text();
    materiel m;
    bool test=m.supprimer(mat);
    ui->tableView_2->setModel(tmpmateriel.afficher());//refresh
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Supprimer materiel"),
                                 QObject::tr("materiel supprimé.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_lineEdit_12_textChanged(const QString &arg1)
{
     ui->tableView_6->setModel(tmpmateriel.recherche(ui->lineEdit_12->text()));
}

void MainWindow::on_lineEdit_20_textChanged(const QString &arg1)
{
     ui->tableView_5->setModel(tmpmateriel.recherche(ui->lineEdit_20->text()));
}

void MainWindow::on_pushButton_7_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_2->model()->rowCount();
    const int columnCount = ui->tableView_2->model()->columnCount();

    out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"

           //     "<align='right'> " << datefich << "</align>"
           "<center> <H1>materiel </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_2->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_2->isColumnHidden(column)) {
                QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
           "</body>\n"
           "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

void MainWindow::on_pushButton_clicked()
{
    QString id,nomg,nbr,descr;




    if( ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()|| ui->lineEdit_3->text().isEmpty() )
    {
        ui->tableView->setModel(tmptravaille.afficher());//refresh
        QMessageBox::warning(nullptr, QObject::tr("Attention"),
                             QObject::tr("Veuillez remplir tout les champs.\n"), QMessageBox::Ok);
    }
    else{
        id=ui->lineEdit->text();
        nomg=ui->lineEdit_2->text();
        nbr=ui->lineEdit_3->text();
        descr=ui->lineEdit_4->text();







        travaille t(id,nomg,nbr,descr );
        bool test=t.ajouter();

        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("Ajouter un   travaille"),
                                     QObject::tr("  travaille ajouté.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(tmptravaille.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un  travaille"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString id,nomg,nbr,descr;


    id=ui->lineEdit_17->text();
    descr=ui->lineEdit_15->text();





    travaille t(id,nomg,nbr,descr);
    bool test= t.modifier(id);

    if (test)
    {
        musicAdd.setMedia(QUrl("C:/Users/houssem/Desktop/Atelier_Connexion/Resources/modif succe.mp3"));
        musicAdd.play();
        QMessageBox::information(nullptr, QObject::tr("Modifier un   travaille"),
                                 QObject::tr("  travaille Modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(tmptravaille.afficher());//refresh
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un travaille"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString id = ui->lineEdit_6->text();
    travaille t;
    bool test=t.supprimer(id);
    ui->tableView->setModel(tmptravaille.afficher());//refresh
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Supprimer travaille"),
                                 QObject::tr("travaille supprimé.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    ui->tableView_3->setModel(tmptravaille.recherche(ui->lineEdit_6->text()));
}

void MainWindow::on_lineEdit_17_textChanged(const QString &arg1)
{
    ui->tableView_4->setModel(tmptravaille.recherche(ui->lineEdit_17->text()));
}

void MainWindow::on_pushButton_8_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"

           //     "<align='right'> " << datefich << "</align>"
           "<center> <H1>travaille </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
           "</body>\n"
           "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

