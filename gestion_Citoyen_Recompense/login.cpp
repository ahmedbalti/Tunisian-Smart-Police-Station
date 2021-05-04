#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include<QDebug>
#include "connection.h"


login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
    QString utilisateur=ui->lineEdit->text();
    QString mdp=ui->lineEdit_2->text();
    MainWindow w;
    if ((utilisateur=="ahmed")&&(mdp=="ahmed"))
    {

        w.show();
        hide();
    }
    else QMessageBox::critical(nullptr, QObject::tr("Problème de connexion"),
                                      QObject::tr("Veuillez revérifier vos informations"), QMessageBox::Cancel);


}


