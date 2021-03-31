#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "QSqlDatabase"
#include <QMessageBox>
#include<QIntValidator>
#include<QValidator>
#include"citoyen.h"
#include "QDebug"
#include<QDate>
#include <QMediaPlayer>
#include <QSound>
#include<QFileDialog>
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(ui->send, SIGNAL(clicked()),this, SLOT(sendMail()));
       connect(ui->exit, SIGNAL(clicked()),this, SLOT(close()));
       connect(ui->browse, SIGNAL(clicked()), this, SLOT(browse()));
       setFixedSize(990,600);  //fixe la taille de la fenêtre

    ui->tableCitoyen->setModel(tmpcitoyen.afficher());
     ui->tableRecompense->setModel(tmprecompense.afficher());
    ui->setupUi(this);
    mMediaPlayer=new QMediaPlayer(this);
    connect(mMediaPlayer,&QMediaPlayer::positionChanged,[&](qint64 pos){ui->progressBar->setValue(pos);});
    connect(mMediaPlayer,&QMediaPlayer::durationChanged,[&](qint64 dur){ui->progressBar->setMaximum(dur);});

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
    Smtp* smtp = new Smtp(ui->uname->text(), ui->pass->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->recipant->text() , ui->subject->text(),ui->msg->text(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->recipant->text() , ui->subject->text(),ui->msg->text());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}




MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ajouterCitoyen_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    int numCin=ui->numCin ->text().toInt();
   ui->numCin->setMaxLength(8);

    // QString daten=ui->datedate->date().toString("yyyy/MM/dd");;
    QString daten=ui->lineEdit_3->text();

    QString nom=ui->nom->text();
     ui->nom->setMaxLength(15);
    QString prenom=ui->prenom->text();
    ui->prenom->setMaxLength(15);

    QString sexe=ui->sexe->text();
     ui->sexe->setMaxLength(10);

     QString activite=ui->activite->text();
      ui->activite->setMaxLength(15);
      int nbrPts=ui->nbrPts ->text().toInt();
      int numRec=ui->numRec ->text().toInt();



    Citoyen C(numCin,nom,prenom,daten,sexe,activite,nbrPts,numRec);



    if(C.ajouter())
      {
           ui->tableCitoyen->setModel(tmpcitoyen.afficher());
         QMessageBox::information(nullptr, QObject::tr("BIEN"),
                     QObject::tr("Ajout effectuer avec succés.\n" ), QMessageBox::Cancel);

                 ui->numCin->setText("");
                 ui->nom->setText("");
                 ui->prenom->setText("");
                 ui->lineEdit_3->setText("");
                 ui->sexe->setText("");
                 ui->activite->setText("");
                 ui->nbrPts->setText("");
                 ui->numRec->setText("");

    }else{
            QMessageBox::information(nullptr, QObject::tr("ECHEC!!!"),
                        QObject::tr("Citoyen existe déja.\n"), QMessageBox::Cancel);
        }

    }





void MainWindow::on_Supprimer_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    Citoyen c1;
    // c1.setnumCin(ui->comboBox_2->currentText().toInt());
     c1.setnumCin(ui->lineEdit_2->text().toInt());
     if(c1.supprimer(c1.getnumCin()))
     {
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



void MainWindow::on_modiferCitoyen_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

     int numCin=ui->lineEdit->text().toInt();
     QString nom=ui->nom_2->text();
     QString prenom=ui->prenom->text();
     QString daten=ui->dateEdit_2->date().toString();
     QString sexe=ui->comboBox->currentText();
     QString activite=ui->activite_2->text();
     int nbrPts=ui->nbrPts_2->text().toInt();
    int numRec=ui->comboBox_4->currentText().toInt();

Citoyen C(numCin,nom,prenom,daten,sexe,activite,nbrPts,numRec);

if(C.modifier(numCin))
{
          QMessageBox::information(nullptr, QObject::tr("Modifier un Citoyen"),
                      QObject::tr("citoyen modifié.\n"), QMessageBox::Cancel);

}
else
{
    QMessageBox::critical(nullptr, QObject::tr("Modifier un Citoyen"),
                      QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
}
}

void MainWindow::on_pushButton_rechercheCitoyen_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    QString recherche =ui->rechercheButton->text();
    ui->tableCitoyen->setModel(tmpcitoyen.chercher(recherche));
}


void MainWindow::on_triCitoyen_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

     ui->tableCitoyen->setModel(tmpcitoyen.tri());
}

void MainWindow::on_ajouterRec_2_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    int numRec=ui->numRec_3->text().toInt();
     QString nomRec=ui->type->text();
     ui->type->setMaxLength(15);
     int nbrEx=ui->nbrEx->text().toInt();
     QString description=ui->description->text();
     ui->description->setMaxLength(15);
     int nbrPts=ui->nbrPts_3->text().toInt();



        recompense r(numRec,nomRec,nbrEx,description,nbrPts);
        if(r.ajouter()) {
             ui->tableRecompense->setModel(tmprecompense.afficher());
            QMessageBox::information(nullptr, QObject::tr("BIEN"),
                        QObject::tr("Ajout effectuer avec succés.\n" ), QMessageBox::Cancel);

            ui->numRec->setText("");
            ui->type->setText("");
                ui->nbrEx->setText("");
                    ui->description->setText("");
                    ui->nbrPts->setText("");


    }else{
            QMessageBox::information(nullptr, QObject::tr("ECHEC!!!"),
                        QObject::tr("recompense existe déja.\n"), QMessageBox::Cancel);
        }

}

void MainWindow::on_modiferRecompense_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    int numRec=ui->num_rec->currentText().toInt();
    // int numRec=ui->modifierRec->text().toInt();
     QString nomRec=ui->nom_3->text();
     int nbrEx=ui->nombre_exemplaire->text().toInt();
     QString description=ui->desc->text();
     int nbrPts=ui->nombre_points->text().toInt();

     recompense r(numRec,nomRec,nbrEx,description,nbrPts);
     if(r.modifier(numRec))
     {
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

void MainWindow::on_pushButton_rechercheRecompense_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    QString recherche =ui->rechercheButton_2->text();
    ui->tableRecompense->setModel(tmprecompense.chercher(recherche));
 ui->tableRecompense->setModel(tmprecompense.afficher());

}


void MainWindow::on_triRecompense_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

      ui->tableRecompense->setModel(tmprecompense.tri());
}

void MainWindow::on_Supprimer_2_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    recompense r1;
   r1.setnumRec(ui->comboBoxempsup_2->currentText().toInt());
           // r1.setnumRec(ui->supp->text().toInt());
    if(r1.supprimer(r1.getnumRec()))
    {
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

void MainWindow::on_send_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,"ouvrir");
        if (filename.isEmpty()){return;}
        mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
      on_pushButton_2_clicked();

}

void MainWindow::on_pushButton_2_clicked()
{
     mMediaPlayer->play();
}

void MainWindow::on_pushButton_3_clicked()
{
    mMediaPlayer->pause();
}

void MainWindow::on_pushButton_4_clicked()
{
    mMediaPlayer->stop();
}



void MainWindow::on_pushButton_5_clicked()
{
    if(ui->pushButton_5->text()=="Muet"){
        mMediaPlayer->setMuted(true);
       ui->pushButton_5->setText("Unmuet");}
       else{ mMediaPlayer->setMuted(false);
           ui->pushButton_5->setText("Muet");}
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //ui->progressBar->setValue(value);
    mMediaPlayer->setVolume(value);
}
