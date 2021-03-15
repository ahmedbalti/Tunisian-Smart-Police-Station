#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citoyen.h"
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->numCin->setValidator( new QIntValidator(0, 99999999, this));
    ui->nbrPts->setValidator( new QIntValidator(0, 99999, this));
    ui->table_citoyen->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    int nbrPts=ui->nbrPts->text().toInt();
    int numCin=ui->numCin->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString date=ui->date->text();
    QString sexe=ui->sexe->text();
    QString activite=ui->activite->text();
    Citoyen c(numCin,nom,prenom,date,sexe,activite,nbrPts);
}

void MainWindow::on_supprimer_clicked()
{
    Citoyen C1; C1.setnumCin(ui->numCin_supp->text().toInt());
    bool test=C1.supprimer(C1.getnumCin());

}
