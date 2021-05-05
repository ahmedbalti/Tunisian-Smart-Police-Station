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
#include"etranger.h"

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
    //nour
    QTimer *timer= new QTimer (this);
    connect (timer ,SIGNAL(timeout()),this,SLOT (clockTimer()));
    timer ->start();
    refrech();

    ui->le_max->setValidator( new QIntValidator(0, 10000, this) );
    ui->le_max_2->setValidator( new QIntValidator(0, 10000, this) );
    ui->le_nbr_2->setValidator( new QIntValidator(0, 10000, this) );
    ui->cb_sort->addItem("name");
    ui->cb_sort->addItem("max");
    ui->cb_sort->addItem("currentt");
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
void MainWindow::clockTimer()
{
    QTime time=QTime::currentTime();
  QString time_text =time.toString ("hh : mm :ss ");
  ui->clock->setText(time_text);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::refrech()
{
    ui->tableView->setModel(C.afficher());
    C.fillComboBox(ui->cb_id);
    C.fillComboBox(ui->cb_id_2);

    ui->tableView_2->setModel(D.afficher());
    D.fillComboBox(ui->cb_id_d_2);
    D.fillComboBox(ui->cb_id_3);
    D.fillComboBox__(ui->cb_cell);
    D.fillComboBox__(ui->cb_cell_2);
    ui->l_total->setText(D.count());
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


        //if(r.modifier(numRec))
            if(r.modifier())
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
                       // "<body bgcolor=#99d6ff link=#5000A0>\n"
                            "<body bgcolor=#ccebff link=#5000A1>\n"


                     "<center>"
               "<img src='C:/Users/DELL/Desktop/balti2/logo.png'></img>"
                    "</center>"


                      //  "<align='center'> " << datefich << "</align>"
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
       QUrl url("https://ACc00e6b7adc58b96ec57beadf4007a3c9:d354dfcbc0dd38e7385b10c6e8650756@api.twilio.com/2010-04-01/Accounts/ACc00e6b7adc58b96ec57beadf4007a3c9/Messages.json");
       QNetworkRequest request(url);

       request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


       QUrlQuery params;
      // params.addQueryItem("From", "+12056512887");
      params.addQueryItem("From", "+18186006846");
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
    Detenu d(D.autoId(), ui->le_cin->text(), ui->le_noom->text(), ui->le_prenom->text(), ui->de_->text(), ui->cb_sexe->currentText(), ui->le_activite->text(), ui->te_->toPlainText(), ui->cb_cell->currentText().toInt());
    if(d.ajouter()) {
        refrech();
        QMessageBox::information(nullptr, QObject::tr("Ajouter detenu"),
                                 QObject::tr("ajout succeful. \n" "Click ok to exit"),QMessageBox::Ok);

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter cellule"),
                                 QObject::tr("ajout failed. \n" "Click Cancel to exit"),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_20_clicked()
{
    Detenu d(ui->cb_id_3->currentText().toInt(), ui->le_cin_2->text(), ui->le_noom_2->text(), ui->le_prenom_2->text(), ui->de_1->text(), ui->cb_sexe_2->currentText(), ui->le_activite_2->text(), ui->te_1->toPlainText(), ui->cb_cell_2->currentText().toInt());
    if(d.modifier()) {
        refrech();
        QMessageBox::information(nullptr, QObject::tr("Modifier detenu"),
                                 QObject::tr("Succes modifier. \n" "Click ok to exit"),QMessageBox::Ok);

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Modifier detenu"),
                                 QObject::tr("Erreur modification. \n" "Click Cancel to exit"),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_21_clicked()
{
    Detenu c;
    c.setId(ui->cb_id_d_2->currentText().toInt());
    if(c.supprimer()) {
        refrech();
        QMessageBox::information(nullptr, QObject::tr("Supprimer detenu"),
                                 QObject::tr("supprim succeful. \n" "Click ok to exit"),QMessageBox::Ok);

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter cellule"),
                                 QObject::tr("supprim failed. \n" "Click Cancel to exit"),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_22_clicked()
{
    Cel c(C.autoId(), ui->le_nom->text(), ui->le_max->text().toInt(), 0);
    if(c.ajouter()) {
        refrech();
        QMessageBox::information(nullptr, QObject::tr("Ajouter cellule"),
                                 QObject::tr("ajout succeful. \n" "Click ok to exit"),QMessageBox::Ok);

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter cellule"),
                                 QObject::tr("ajout failed. \n" "Click Cancel to exit"),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_23_clicked()
{
    Cel c(ui->cb_id->currentText().toInt(), ui->le_nom_2->text(), ui->le_max_2->text().toInt(), ui->le_nbr_2->text().toInt());
    if(c.modifier()) {
        refrech();
        QMessageBox::information(nullptr, QObject::tr("Modifier cellule"),
                                 QObject::tr("modif succeful. \n" "Click ok to exit"),QMessageBox::Ok);

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter cellule"),
                                 QObject::tr("modif failed. \n" "Click Cancel to exit"),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_24_clicked()
{
    Cel c;
    c.setId(ui->cb_id_2->currentText().toInt());
    if(c.supprimer()) {
        refrech();
        QMessageBox::information(nullptr, QObject::tr("Supprimer cellule"),
                                 QObject::tr("supprim succeful. \n" "Click ok to exit"),QMessageBox::Ok);

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter cellule"),
                                 QObject::tr("supprim failed. \n" "Click Cancel to exit"),QMessageBox::Cancel);

    }
}

void MainWindow::on_le_search_2_textChanged(const QString &arg1)
{
    ui->tableView_2->setModel(D.search(arg1));

}

void MainWindow::on_le_search_textChanged(const QString &arg1)
{
    ui->tableView->setModel(C.search(arg1));

}

void MainWindow::on_cb_sort_2_currentTextChanged(const QString &arg1)
{
    ui->tableView_2->setModel(D.sort(arg1));

}

void MainWindow::on_cb_sort_currentTextChanged(const QString &arg1)
{
    ui->tableView->setModel(C.sort(arg1));

}

void MainWindow::on_pushButton_15_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_valider_3_clicked()
{
    int id=ui->id100->text().toInt();
    QString duree=ui->lineEdit_duree_4->text();
    QString datedem=ui->dateEdit_3->text();
    QString poste=ui->lineEdit_poste_3->text();
    QString type=ui->comboBox_5->currentText();
    conge a(id,duree,datedem,poste,type);
   bool test= a.ajouter();
   if(test)
   { ui->tableView_4->setModel(tmpb.afficher());
       QMessageBox::information(nullptr, QObject::tr("Conge ajouté"),
                   QObject::tr(" successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}
   else
       QMessageBox::critical(nullptr, QObject::tr("Conge non ajouté"),
                   QObject::tr(" failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pushButton_quitter_3_clicked()
{
    int id=ui->id100->text().toInt();
    QString duree=ui->lineEdit_duree_4->text();
    QString datedem=ui->dateEdit_3->text();
    QString poste=ui->lineEdit_poste_3->text();
    QString type=ui->comboBox_5->currentText();
     conge a(id,duree,datedem,poste,type);
   bool test= a.modifier(id);
   if(test)
   { ui->tableView_4->setModel(tmpb.afficher());
       QMessageBox::information(nullptr, QObject::tr("Conge modifié"),
                   QObject::tr(" successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}
   else
       QMessageBox::critical(nullptr, QObject::tr("Conge non modifié"),
                   QObject::tr(" failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pushButton_29_clicked()
{
    int row=ui->tableView_4->selectionModel()->currentIndex().row();
    int id=ui->tableView_4->model()->index(0,row).data().toInt();
    ui->tabWidget_6->setCurrentIndex(0);
    QString id_str=QString::number(id);
    ui->id100->setText(id_str);
}

void MainWindow::on_pushButton_30_clicked()
{
    int row=ui->tableView_4->selectionModel()->currentIndex().row();
    int id=ui->tableView_4->model()->index(0,row).data().toInt();
    bool test= tmpb.supprimer(id);
    if(test)
    { ui->tableView_4->setModel(tmpb.afficher());
        QMessageBox::information(nullptr, QObject::tr("Conge supprimé"),
                    QObject::tr(" successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 }
    else
        QMessageBox::critical(nullptr, QObject::tr("Conge non supprimé"),
                    QObject::tr(" failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_valider_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    float salaire=ui->lineEdit_salaire->text().toFloat();
    QString datenais=ui->dateEdit->text();
    QString poste=ui->lineEdit_poste->text();
    Agent a(id,nom,prenom,salaire,datenais,poste);
   bool test= a.ajouter();
   if(test)
   { ui->tableView_3->setModel(tmpa.afficher());
       QMessageBox::information(nullptr, QObject::tr("Agent ajouté"),
                   QObject::tr(" successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}
   else
       QMessageBox::critical(nullptr, QObject::tr("Agent non ajouté"),
                   QObject::tr(" failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_quitter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    float salaire=ui->lineEdit_salaire->text().toFloat();
    QString datenais=ui->dateEdit->text();
    QString poste=ui->lineEdit_poste->text();
    Agent a(id,nom,prenom,salaire,datenais,poste);
   bool test= a.modifier(id);
   if(test)
   { ui->tableView_3->setModel(tmpa.afficher());
       QMessageBox::information(nullptr, QObject::tr("Agent modifié"),
                   QObject::tr(" successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}
   else
       QMessageBox::critical(nullptr, QObject::tr("Agent non modifié"),
                   QObject::tr(" failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_28_clicked()
{
    QString critere=ui->comboBox_2->currentText();
     ui->tableView_3->setModel(tmpa.trier(critere));
}

void MainWindow::on_pushButton_27_clicked()
{
    int row=ui->tableView_3->selectionModel()->currentIndex().row();
    int id=ui->tableView_3->model()->index(0,row).data().toInt();
    ui->tabWidget_5->setCurrentIndex(0);
    QString id_str=QString::number(id);
    ui->lineEdit_id->setText(id_str);
}

void MainWindow::on_pushButton_26_clicked()
{
    int row=ui->tableView_3->selectionModel()->currentIndex().row();
    int id=ui->tableView_3->model()->index(0,row).data().toInt();
    bool test= tmpa.supprimer(id);
    if(test)
    { ui->tableView_3->setModel(tmpa.afficher());
        QMessageBox::information(nullptr, QObject::tr("Agent supprimé"),
                    QObject::tr(" successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 }
    else
        QMessageBox::critical(nullptr, QObject::tr("Agent non supprimé"),
                    QObject::tr(" failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_33_clicked()
{
    QString critere=ui->comboBox_4->currentText();
    QString rech=ui->lineEdit_7->text();
    ui->tableView_3->setModel(tmpa.afficherRech(critere,rech));
}

void MainWindow::on_pushButton_34_clicked()
{
     ui->tableView_3->setModel(tmpa.afficher());
}

void MainWindow::on_pushButton_14_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_35_clicked()
{
    Smtp* smtp = new Smtp("hedi.benmustapha@esprit.tn", "191JMT3541", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        smtp->sendMail("hedi.benmustapha@esprit.tn",ui->lineEdit_15->text(),ui->lineEdit_16->text(),ui->textEdit_2->toPlainText());
}

void MainWindow::on_pushButton_31_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_ajouter_etranger_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    QString numpass=ui->numPass->text();
   ui->numPass->setMaxLength(8);

    QString nom=ui->nom_3->text();
     ui->nom_3->setMaxLength(15);
    QString prenom=ui->prenom_3->text();
    ui->prenom_3->setMaxLength(15);
    QString nationalite=ui->nationalite->text();
    QString sexe=ui->comboBox_6->currentText();
    int age=ui->age->text().toInt();

     QString activite=ui->activite_3->text();
     ui->activite_3->setMaxLength(15);

     QString adresse=ui->lineEdit_17->text();

    etranger e(numpass,nom,prenom,nationalite,sexe,age,activite,adresse);

    if((prenom=="")&&(nom=="")&&(sexe=="")&&(numpass=="")&&(activite=="")&&(adresse==""))
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Attention!! Les champs sont vides , Veuillez les remplir"), QMessageBox::Ok);
        }

    else if(numpass =="")
     {
         QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                     QObject::tr("Veuillez remplir le numéro de Passeport"), QMessageBox::Ok);

     }
    else if (numpass.size()!=8)
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
    else if(adresse=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Veuillez remplir l adresse"), QMessageBox::Ok);

       }
else {

    if(e.ajouter3())
      {
           ui->tableEtranger->setModel(tmpetranger.afficher3());

           musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/ajout succe.mp3"));
                           musicAdd.play();

                           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                   notifyIcon->show();
                                   notifyIcon->setIcon(QIcon("icone.png"));

                                   notifyIcon->showMessage("GESTION ETRANGER","étranger Ajouté",QSystemTrayIcon::Information,15000);

                               QMessageBox::information(nullptr, QObject::tr("ajouter étranger"),
                                                     QObject::tr("étranger ajouté./n"
                                                        "click cancel to exit."),QMessageBox::Cancel);
                               }

                               else
                                   QMessageBox::critical(nullptr, QObject::tr("ajouter étranger"),
                                                         QObject::tr("Erreur !./n"
                                                            "click cancel to exit."),QMessageBox::Cancel);


}}

void MainWindow::on_pushButton_recherche_3_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    QString recherche1 =ui->rechercheBTN_3->text();
    ui->tableEtranger->setModel(tmpetranger.chercher3(recherche1));
}

void MainWindow::on_tri_3_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


     ui->tableEtranger->setModel(tmpetranger.tri3());
}

void MainWindow::on_modifer_3_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();



    QString numpass=ui->lineEdit_22->text();
    QString nom=ui->nom_5->text();
    QString prenom=ui->prenom_5->text();
    QString sexe=ui->sexe->text();
    QString activite=ui->lineEdit_23->text();
    int age=ui->age_2->text().toInt();
    QString adresse=ui->lineEdit_24->text();
    QString nationalite=ui->nationalite_2->text();

    etranger e (numpass,nom,prenom,nationalite,sexe,age,activite,adresse);

    if((prenom=="")&&(nom=="")&&(sexe=="")&&(numpass=="")&&(activite=="")&&(adresse==""))
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Attention!! Les champs sont vides , Veuillez les remplir"), QMessageBox::Ok);
        }

    else if(numpass =="")
     {
         QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                     QObject::tr("Veuillez remplir le numéro de Passeport"), QMessageBox::Ok);

     }
    else if (numpass.size()!=8)
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
    else if(adresse=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Veuillez remplir l adresse"), QMessageBox::Ok);

       }
else {

if(e.modifier3(numpass))
{
    musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/modif succe.mp3"));
                    musicAdd.play();

    ui->tableEtranger->setModel(tmpetranger.afficher3());
         QMessageBox::information(nullptr, QObject::tr("Modifier un Etranger"),
                     QObject::tr("étranger modifié.\n"), QMessageBox::Cancel);

}
else
{
   QMessageBox::critical(nullptr, QObject::tr("Modifier un Etranger"),

                         QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
}
}
}

void MainWindow::on_supp_3_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/Users/DELL/Desktop/nc.mp3"));
           player->setVolume(3000);
           player->play();


    etranger e1;

     e1.setnumpass(ui->lineEdit_25->text());
     if(e1.supprimer3(e1.getnumpass()))
     {
         musicAdd.setMedia(QUrl("C:/Users/DELL/Desktop/Tunisian Smart Police Station/gestion_Citoyen_Recompense/supp succe.mp3"));
                         musicAdd.play();
          ui->tableEtranger->setModel(tmpetranger.afficher3());
         QMessageBox::information(nullptr, QObject::tr("Supprimer un étranger"),
                     QObject::tr("Suppression avec succés.\n" ), QMessageBox::Cancel);
     }
     else
    {
         QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                             QObject::tr("pas de suppression.\n"
                                         ), QMessageBox::Cancel);

     }
}

void MainWindow::on_tableEtranger_activated(const QModelIndex &index)
{
    int selected_row=ui->tableEtranger->currentIndex().row();


    QString selected_numPass=ui->tableEtranger->model()->data(index.sibling(selected_row,0)).toString();
     ui->lineEdit_22->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,0)).toString());

    ui->lineEdit_22->setText(selected_numPass);
    ui->nom_5->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,1)).toString());
    ui->prenom_5->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,2)).toString());
    ui->nationalite_2->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,3)).toString());
    ui->sexe->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,4)).toString());
    ui->age_2->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,5)).toString());
    ui->lineEdit_23->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,6)).toString());
    ui->lineEdit_24->setText(ui->tableEtranger->model()->data(index.sibling(selected_row,7)).toString());

}

void MainWindow::on_pushButton_32_clicked()
{
    QString link="http://www.google.com";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_36_clicked()
{
    notepad=new note(this);
        notepad->show();
}
