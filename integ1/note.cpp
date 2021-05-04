#include "note.h"
#include "ui_note.h"

note::note(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::note)
{
    ui->setupUi(this);
}

note::~note()
{
    delete ui;
}
