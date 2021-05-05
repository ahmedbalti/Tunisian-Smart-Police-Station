#include "note.h"
#include "ui_note.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
note::note(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::note)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

note::~note()
{
    delete ui;
}

void note::on_actionNew_triggered()
{
    file_path_="";
    ui->textEdit->setPlainText("");

}

void note::on_actionOpen_triggered()
{
QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
QFile file (file_name);
file_path_ =file_name;
if (!file.open(QFile::ReadOnly| QFile::Text)){
    QMessageBox::warning(this,"..","file not open");
    return;
}
QTextStream  in (&file);
QString text=in.readAll();
ui->textEdit->setPlainText(text);
file.close();
}

void note::on_actionSave_triggered()
{
    QFile file (file_path_);
    if (!file.open(QFile::WriteOnly| QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream  out (&file);
    QString text= ui->textEdit->toPlainText();
    out<< text;
    file.flush();
    file.close();
}
void note::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open the file");
    QFile file (file_name);
    file_path_=file_name;
    if (!file.open(QFile::WriteOnly| QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream  out (&file);
    QString text= ui->textEdit->toPlainText();
    out<< text;
    file.flush();
    file.close();
}
void note::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}
void note::on_actionCut_triggered()
{
    ui->textEdit->cut();
}
void note::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void note::on_actionUndo_triggered()
{
  ui->textEdit->undo();
}

void note::on_actionRedo_triggered()
{
   ui->textEdit->redo();
}
