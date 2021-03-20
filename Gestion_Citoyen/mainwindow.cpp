#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "QSqlDatabase"
#include <QMessageBox>
#include<QIntValidator>
#include<QValidator>
#include"citoyen.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ajouterCitoyen_clicked()
{
        int numCin=ui->numCin ->text().toInt();
       // ui->numCin->setMaxLength(8);
        //QString congeemp="";
        QString date=ui->date->text();

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






        Citoyen C(numCin,nom,prenom,date,sexe,activite,nbrPts,numRec);
        if(C.ajouter()) {
            QMessageBox::information(nullptr, QObject::tr("BIEN"),
                        QObject::tr("Ajout effectuer avec succés.\n" ), QMessageBox::Cancel);

                    ui->numCin->setText("");


                    ui->date->setText("");
                    ui->nom->setText("");
                    ui->prenom->setText("");
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
    Citoyen c1;
    c1.setnumCin(ui->comboBox_2->currentText().toInt());
    if(c1.supprimer(c1.getnumCin()))
    {
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
     int numCin=ui->comboBox_3->currentText().toInt();
     QString nom=ui->nom_2->text();
     QString prenom=ui->prenom->text();
     QString date=ui->date_2->text();
     QString sexe=ui->comboBox->currentText();
     QString activite=ui->activite_2->text();
     int nbrPts=ui->nbrPts_2->text().toInt();
    int numRec=ui->comboBox_4->currentText().toInt();

Citoyen C(numCin,nom,prenom,date,sexe,activite,nbrPts,numRec);

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
    QString recherche =ui->pushButton_rechercheCitoyen->text();
    ui->tableCitoyen->setModel(tmpcitoyen.afficher());
 // ui->tableCitoyen->setModel(tmp.chercher(recherche));
}

