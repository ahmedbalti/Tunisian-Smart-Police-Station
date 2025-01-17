#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citoyen.h"
#include "recompense.h"
#include "QSqlDatabase"
#include <QMessageBox>
#include<QIntValidator>
#include<QValidator>
#include "QDebug"
#include<QDate>
#include <QComboBox>
#include <QMediaPlayer>
#include <QSound>
#include<QFileDialog>
#include <stat.h>
#include<QtPrintSupport/QPrinter>
#include <QSystemTrayIcon>

#include<QPdfWriter>

#include <QPainter>

#include<QFileDialog>

#include<QTextDocument>

#include <QTextEdit>

#include <QtSql/QSqlQueryModel>

#include<QtPrintSupport/QPrinter>

#include <QVector2D>

#include <QVector>

#include <QSqlQuery>

#include<QDesktopServices>

#include <QMessageBox>

#include<QUrl>

#include <QPixmap>

#include <QTabWidget>

#include <QValidator>

#include <QPrintDialog>

#include<QtSql/QSqlQuery>

#include<QVariant>

#include <QNetworkAccessManager>

#include <QUrlQuery>

#include <QNetworkReply>

#include <QJsonValue>

#include <QJsonValueRef>

#include <QJsonDocument>

#include <QJsonObject>

#include <QJsonArray>

#include <QString>

#include <QDebug>

#include <QtCore>

#include <QtGui>

#include <QDialog>

#include <QModelIndex>

#include <QGridLayout>

#include <QApplication>

#include <QIntValidator>

#include <QDateTime>

#include <QMediaPlayer>

#include <QRadioButton>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    mMediaPlayer=new QMediaPlayer(this);
    connect(mMediaPlayer,&QMediaPlayer::positionChanged,[&](qint64 pos){ui->progressBar->setValue(pos);});
    connect(mMediaPlayer,&QMediaPlayer::durationChanged,[&](qint64 dur){ui->progressBar->setMaximum(dur);});

    ui->tableCitoyen->setModel(tmpcitoyen.afficher());
    ui->tableRecompense->setModel(tmprecompense.afficher());
  //  ui->comboBox_2->setModel(tmpcitoyen.affecter_recompense());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    QString numCin=ui->numCin ->text();
   ui->numCin->setMaxLength(8);

     QString daten=ui->date->date().toString("yyyy/MM/dd");
   // QString daten=ui->date->text();

    QString nom=ui->nom->text();
     ui->nom->setMaxLength(15);
    QString prenom=ui->prenom->text();
    ui->prenom->setMaxLength(15);
    QString sexe=ui->comboBox->currentText();
    // ui->comboBox->setMaxLength(10);

     QString activite=ui->activite->text();
     ui->activite->setMaxLength(15);
     int nbrPts=ui->nbr_pts ->text().toInt();
     QString numRec=ui->lineEdit ->text();
        //QString numRec = ui->comboBox_2->currentText();

    Citoyen C(numCin,nom,prenom,daten,sexe,activite,nbrPts,numRec);

    if((prenom=="")&&(nom=="")&&(sexe=="")&&(numCin=="")&&(activite=="")&&(daten==""))
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Attention!! Les champs sont vides , Veuillez les remplir"), QMessageBox::Ok);
        }
//       else if(((numCin>=99999999) && (numCin<=9999999)) )
//          {
//              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
//                          QObject::tr("Attention ! Le numéro de Cin doit contenir 8 chiffres"), QMessageBox::Ok);

//          }
    else if(numCin =="")
     {
         QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                     QObject::tr("Veuillez remplir le numéro de CIN"), QMessageBox::Ok);

     }
    else if (numCin.size()!=8)
    {
       QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                   QObject::tr("le numéro de Cin doit se composer par 8 chiffres"), QMessageBox::Ok);

    }
       else if(prenom =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez remplir le prénom"), QMessageBox::Ok);

          }
       else if(nom =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez remplir le nom"), QMessageBox::Ok);

          }
       else if(sexe =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez choisir le sexe"), QMessageBox::Ok);

          }

       else if(activite =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez remplir l'activité"), QMessageBox::Ok);

          }
    else if(daten=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Veuillez remplir la date de naissance"), QMessageBox::Ok);

       }
else {

    if(C.ajouter())
      {
           ui->tableCitoyen->setModel(tmpcitoyen.afficher());

           musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/ajout succe.mp3"));
                           musicAdd.play();

           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION citoyen","citoyen Ajouté",QSystemTrayIcon::Information,15000);

               QMessageBox::information(nullptr, QObject::tr("ajouter citoyen"),
                                     QObject::tr("citoyen ajouté./n"
                                        "click cancel to exit."),QMessageBox::Cancel);
               }

               else
                   QMessageBox::critical(nullptr, QObject::tr("ajouter citoyen"),
                                         QObject::tr("Erreur !./n"
                                            "click cancel to exit."),QMessageBox::Cancel);


           }
//         QMessageBox::information(nullptr, QObject::tr("BIEN"),
//                     QObject::tr("Ajout effectuer avec succés.\n" ), QMessageBox::Cancel);


//                 ui->numCin->setText("");
//                 ui->nom->setText("");
//                 ui->prenom->setText("");
//                 ui->lineEdit_3->setText("");
//            //  ui->sexe->setText("");
//                 ui->activite->setText("");
//                 ui->nbr_pts->setText("");
//                 ui->lineEdit->setText("");

//    }else{
//            QMessageBox::information(nullptr, QObject::tr("ECHEC!!!"),
//                        QObject::tr("Citoyen existe déja.\n"), QMessageBox::Cancel);
//        }
//}
}

void MainWindow::on_supp_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    Citoyen c1;
    // c1.setnumCin(ui->comboBox_2->currentText().toInt());
     c1.setnumCin(ui->lineEdit_3->text());
     if(c1.supprimer(c1.getnumCin()))
     {
         musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/supp succe.mp3"));
                         musicAdd.play();
          ui->tableCitoyen->setModel(tmpcitoyen.afficher());
         QMessageBox::information(nullptr, QObject::tr("Supprimer un citoyen"),
                     QObject::tr("Suppression avec succés.\n" ), QMessageBox::Cancel);
     }
     else
    {
         QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                             QObject::tr("pas de suppression.\n"
                                         ), QMessageBox::Cancel);

     }
}

void MainWindow::on_modifer_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();



    QString numCin=ui->lineEdit_2->text();
    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom_2->text();
  QString daten=ui->date_2->date().toString();
    QString sexe=ui->activite_2->text();
    QString activite=ui->activite_2->text();
    int nbrPts=ui->nbrPts->text().toInt();
     QString numRec=ui->lineEdit_10->text();
  // int numRec=ui->comboBox_3->currentText().toInt();

Citoyen C(numCin,nom,prenom,daten,sexe,activite,nbrPts,numRec);

if((prenom=="")&&(nom=="")&&(sexe=="")&&(numCin=="")&&(activite=="")&&(daten==""))
   {
       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                   QObject::tr("Attention!! Les champs sont vides , Veuillez les remplir"), QMessageBox::Ok);
    }
  else if(numCin =="")
   {
       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                   QObject::tr("Veuillez remplir le numéro de CIN"), QMessageBox::Ok);

   }
   else if(prenom =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez remplir le prénom"), QMessageBox::Ok);

      }
   else if(nom =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez remplir le nom"), QMessageBox::Ok);

      }
   else if(sexe =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez choisir le sexe"), QMessageBox::Ok);

      }

   else if(activite =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez remplir l'activité"), QMessageBox::Ok);

      }
else if(daten=="")
   {
       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                   QObject::tr("Veuillez remplir la date de naissance"), QMessageBox::Ok);

   }
else {

if(C.modifier(numCin))
{
    musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/modif succe.mp3"));
                    musicAdd.play();

    ui->tableCitoyen->setModel(tmpcitoyen.afficher());
         QMessageBox::information(nullptr, QObject::tr("Modifier un Citoyen"),
                     QObject::tr("citoyen modifié.\n"), QMessageBox::Cancel);

}
else
{
   QMessageBox::critical(nullptr, QObject::tr("Modifier un Citoyen"),

                         QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
}
}
}



void MainWindow::on_pushButton_recherche_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    QString recherche =ui->rechercheBTN->text();
    ui->tableCitoyen->setModel(tmpcitoyen.chercher(recherche));
}

void MainWindow::on_tri_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


     ui->tableCitoyen->setModel(tmpcitoyen.tri());
}

void MainWindow::on_ajouterRecomp_clicked()
{

QMediaPlayer *player = new QMediaPlayer;
          player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
          player->setVolume(3000);
          player->play();


//   int numRec=ui->numRec->text().toInt();
       QString   numRec=ui->numRec->text();
//    QString nomRec=ui->nomRec_2->text();
//    ui->nomRec_2->setMaxLength(20);
       QString nomRec=ui->comboBox_3->currentText();
    int nbrEx=ui->nbrEx->text().toInt();
    QString description=ui->lineEdit_5->text();
    ui->lineEdit_5->setMaxLength(20);
    int nbrPts=ui->lineEdit_4->text().toInt();



       recompense r(numRec,nomRec,nbrEx,description,nbrPts);
       if(numRec =="")
             {
                 QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Veuillez taper un numéro différent de chaine vide"), QMessageBox::Ok);

             }
       else if(nomRec =="" )
             {
                 QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Veuillez remplir le nom de la récompense (soit cinéma soit resto soit bande d'achat)"), QMessageBox::Ok);

             }
       else if(nbrEx <1 )
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez donnez un nombre d'exemplaires supérieur ou égal à 1"), QMessageBox::Ok);

          }
          else if(nbrPts <50)
             {
                 QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Le nombre de points est insuffisant pour avoir une récompense"), QMessageBox::Ok);

             }
       else {

       if(r.ajouter()) {
           musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/ajout succe.mp3"));
                           musicAdd.play();
            ui->tableRecompense->setModel(tmprecompense.afficher());
           QMessageBox::information(nullptr, QObject::tr("BIEN"),
                       QObject::tr("Ajout effectuer avec succés.\n" ), QMessageBox::Cancel);

           ui->numRec->setText("");
           //ui->comboBox_3->setText("");
               ui->nbrEx->setText("");
                   ui->lineEdit_5->setText("");
                   ui->lineEdit_4->setText("");


   }else{
           QMessageBox::information(nullptr, QObject::tr("ECHEC!!!"),
                       QObject::tr("recompense existe déja.\n"), QMessageBox::Cancel);
       }
}
}


void MainWindow::on_pushButton_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();

    recompense r1;
   //r1.setnumRec(ui->suppRec->currentText().toInt());
          //  r1.setnumRec(ui->lineEdit_11->text().toInt());
    r1.setnumRec(ui->lineEdit_11->text());
    if(r1.supprimer(r1.getnumRec()))
    {
        musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/supp succe.mp3"));
                        musicAdd.play();
        ui->tableRecompense->setModel(tmprecompense.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer une récompense"),
                    QObject::tr("Suppression avec succés.\n" ), QMessageBox::Cancel);
    }
    else
   {
        QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                            QObject::tr("pas de suppression.\n"
                                        ), QMessageBox::Cancel);

    }
}

void MainWindow::on_modifierRecompense_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
              player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
              player->setVolume(3000);
              player->play();


       //int numRec=ui->numRec_2->currentText().toInt();lineEdit_8
      //  int numRec=ui->lineEdit_8->text().toInt();
        QString numRec=ui->lineEdit_8->text();
       // int numRec=ui->modifierRec->text().toInt();
        QString nomRec=ui->nomRec->text();
        ui->nomRec->setMaxLength(20);
        int nbrEx=ui->nbrEx_2->text().toInt();
        QString description=ui->lineEdit_6->text();
         ui->lineEdit_6->setMaxLength(20);
        int nbrPts=ui->nbrPts_2->text().toInt();

        recompense r(numRec,nomRec,nbrEx,description,nbrPts);

        if(numRec =="")
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez taper un numéro différent de chaine vide"), QMessageBox::Ok);

              }
        else if(nomRec =="" )
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez remplir le nom de la récompense (soit cinéma soit resto soit bande d'achat)"), QMessageBox::Ok);

              }
        else if(nbrEx <1 )
           {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                           QObject::tr("Veuillez donnez un nombre d'exemplaires supérieur ou égal à 1"), QMessageBox::Ok);

           }
//           else if(nbrPts <50)
//              {
//                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
//                              QObject::tr("Le nombre de points est insuffisant pour avoir une récompense"), QMessageBox::Ok);

//              }
        else {


        if(r.modifier(numRec))
        {
            musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/modif succe.mp3"));
                            musicAdd.play();
            ui->tableRecompense->setModel(tmprecompense.afficher());
                  QMessageBox::information(nullptr, QObject::tr("Modifier une Récompense"),
                              QObject::tr("Récompense modifie.\n"), QMessageBox::Cancel);

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Modifier une Récompense"),
                              QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
        }
        }
}

void MainWindow::on_rechercheRecompense_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
              player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
              player->setVolume(3000);
              player->play();



       QString recherche =ui->edit_recherche->text();
       ui->tableRecompense->setModel(tmprecompense.chercher(recherche));
 //   ui->tableRecompense->setModel(tmprecompense.afficher());

}

void MainWindow::on_triRecomp_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();

      ui->tableRecompense->setModel(tmprecompense.tri());
}
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_pushButton_2_clicked()
{
//    QMediaPlayer * bulletsound = new QMediaPlayer();
//           bulletsound->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
//          if (bulletsound->state() == QMediaPlayer::PlayingState){
//               bulletsound->setPosition(0);
//           }
//           else if (bulletsound->state() == QMediaPlayer::StoppedState){
//               bulletsound->play();
//           }

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();

    ui->stackedWidget->setCurrentIndex(2);
    QString utilisateur=ui->lineEdit_12->text();
    QString mdp=ui->lineEdit_13->text();
    MainWindow w;
    if ((utilisateur=="ahmed")&&(mdp=="ahmed"))
    {

        //w.show();

    }

    else{ QMessageBox::critical(nullptr, QObject::tr("Problème de connexion"),
                                      QObject::tr("Veuillez revérifier vos informations"), QMessageBox::Cancel);

        hide();
    }

}

void MainWindow::on_pushButton_3_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    QString filename=QFileDialog::getOpenFileName(this,"ouvrir");
        if (filename.isEmpty()){return;}
        mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
      on_pushButton_4_clicked();

}

void MainWindow::on_pushButton_4_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


           if(ui->pushButton_4->text()=="Play"){
               mMediaPlayer->play();
              ui->pushButton_4->setText("Pause");}
              else{ mMediaPlayer->pause();
                  ui->pushButton_4->setText("Play");}

}


void MainWindow::on_pushButton_6_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


   mMediaPlayer->stop();
}

void MainWindow::on_pushButton_7_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    if(ui->pushButton_7->text()=="Muet"){
        mMediaPlayer->setMuted(true);
       ui->pushButton_7->setText("Unmuet");}
       else{ mMediaPlayer->setMuted(false);
           ui->pushButton_7->setText("Muet");}
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{

//    QMediaPlayer *player = new QMediaPlayer;
//           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
//           player->setVolume(3000);
//           player->play();


      mMediaPlayer->setVolume(value);
}

void MainWindow::on_tableCitoyen_activated(const QModelIndex &index)
{
    int selected_row=ui->tableCitoyen->currentIndex().row();


    QString selected_numCin=ui->tableCitoyen->model()->data(index.sibling(selected_row,0)).toString();
     ui->lineEdit_3->setText(ui->tableCitoyen->model()->data(index.sibling(selected_row,0)).toString());

    ui->lineEdit_2->setText(selected_numCin);
    ui->nom_2->setText(ui->tableCitoyen->model()->data(index.sibling(selected_row,1)).toString());
    ui->prenom_2->setText(ui->tableCitoyen->model()->data(index.sibling(selected_row,2)).toString());
    ui->date_2->setDate(ui->tableCitoyen->model()->data(index.sibling(selected_row,3)).toDate());
    ui->activite_2->setText(ui->tableCitoyen->model()->data(index.sibling(selected_row,4)).toString());
    ui->nbrPts->setText(ui->tableCitoyen->model()->data(index.sibling(selected_row,5)).toString());
    ui->lineEdit_9->setText(ui->tableCitoyen->model()->data(index.sibling(selected_row,6)).toString());
    ui->lineEdit_10->setText(ui->tableCitoyen->model()->data(index.sibling(selected_row,7)).toString());

}

void MainWindow::on_tableRecompense_activated(const QModelIndex &index)
{
    int selected_row=ui->tableRecompense->currentIndex().row();


    QString selected_numRec=ui->tableRecompense->model()->data(index.sibling(selected_row,0)).toString();
     ui->lineEdit_11->setText(ui->tableRecompense->model()->data(index.sibling(selected_row,0)).toString());

    ui->lineEdit_8->setText(selected_numRec);
    ui->nomRec->setText(ui->tableRecompense->model()->data(index.sibling(selected_row,1)).toString());
    ui->nbrEx_2->setText(ui->tableRecompense->model()->data(index.sibling(selected_row,2)).toString());
    ui->nbrPts_2->setText(ui->tableRecompense->model()->data(index.sibling(selected_row,3)).toString());
    ui->lineEdit_6->setText(ui->tableRecompense->model()->data(index.sibling(selected_row,4)).toString());

}



void MainWindow::on_pushButton_5_clicked()
{
    int res;
            statistiques w(this);
            w.setWindowTitle("Statistiques des Recompenses");

            res = w.exec();
            qDebug() << res;
            if (res == QDialog::Rejected)
              return;
}

void MainWindow::on_pushButton_8_clicked()
{
    QString strStream;
                    QTextStream out(&strStream);

                    const int rowCount = ui->tableCitoyen->model()->rowCount();
                    const int columnCount = ui->tableCitoyen->model()->columnCount();


                    out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("strTitle")
                        <<  "</head>\n"
                        "<body bgcolor=#ffffff link=#5000A0>\n"


                             "<img src='C:/Users\DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense'></img>"

                       //     "<align='right'> " << datefich << "</align>"
                        "<center> <H1>Liste des Citoyens </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";



                    // headers
                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableCitoyen->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableCitoyen->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    // data table
                    for (int row = 0; row < rowCount; row++) {
                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                        for (int column = 0; column < columnCount; column++) {
                            if (!ui->tableCitoyen->isColumnHidden(column)) {
                                QString data = ui->tableCitoyen->model()->data(ui->tableCitoyen->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pushButton_9_clicked()
{
    //imprimer

       QPrinter printer;

       printer.setPrinterName("desiered printer name");

     QPrintDialog dialog(&printer,this);

       if(dialog.exec()== QDialog::Rejected)

           return;
}





void MainWindow::on_pushButton_10_clicked()
{
    //SMS

    musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/sms.mp3"));
                    musicAdd.play();

    QNetworkAccessManager * manager = new QNetworkAccessManager(this);

   //    QUrl url("https://AC8b263dd209c062a0d924254c7377c4a5:176d3c29991a42bfaf6b2617172c85c3@api.twilio.com/2010-04-01/Accounts/AC8b263dd209c062a0d924254c7377c4a5/Messages.json");
       QUrl url("https://AC2575f7c0523d5276ea916860e718aa64:44eb88472f8cd9cdc7e4900a5c05a756@api.twilio.com/2010-04-01/Accounts/AC2575f7c0523d5276ea916860e718aa64/Messages.json");
       QNetworkRequest request(url);

       request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


       QUrlQuery params;
      // params.addQueryItem("From", "+12056512887");
      params.addQueryItem("From", "+19726354313");
       params.addQueryItem("To",ui->lineEdit_14->text() );//"+21628554027"
       params.addQueryItem("Body", ui->textEdit->toPlainText());
      // params.addQueryItem("Body", "test");

       // etc

       connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply*)));

       manager->post(request, params.query().toUtf8());
       //son sms


   }
   void MainWindow::replyFinished(QNetworkReply* reply)
   {
       //QByteArray bts = rep->readAll();


       QByteArray buffer = reply->readAll();
       qDebug() << buffer;
       QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
       QJsonObject jsonReply = jsonDoc.object();

       QJsonObject response = jsonReply["response"].toObject();
       QJsonArray  data     = jsonReply["data"].toArray();
       qDebug() << data;
       qDebug() << response;


   }

void MainWindow::on_pushButton_11_clicked()
{
    QTableView *table;
                       table = ui->tableCitoyen;
                       QString filters("CSV files (*.csv);;All files (*.*)");
                       QString defaultFilter("CSV files (*.csv)");
                       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                          filters, &defaultFilter);
                       QFile file(fileName);
                       QAbstractItemModel *model =  table->model();
                       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                           QTextStream data(&file);
                           QStringList strList;
                           for (int i = 0; i < model->columnCount(); i++) {
                               if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                                   strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") << "\n";
                           for (int i = 0; i < model->rowCount(); i++) {
                               strList.clear();
                               for (int j = 0; j < model->columnCount(); j++) {
                                   if (model->data(model->index(i, j)).toString().length() > 0)
                                       strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                                   else
                                       strList.append("");
                               }
                               data << strList.join(";") + "\n";
                           }
                           file.close();
                           //QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");


                       }
}

void MainWindow::on_pushButton_12_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_19_clicked()
{
    QString link="http://www.google.com";
        QDesktopServices::openUrl(QUrl(link));
}
