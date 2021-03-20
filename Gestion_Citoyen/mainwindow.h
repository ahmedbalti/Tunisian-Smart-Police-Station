#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "citoyen.h"
#include <QMainWindow>
#include <QtWidgets/QMessageBox>
#include"recompense.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_ajouterCitoyen_clicked();

    void on_Supprimer_clicked();

    void on_modiferCitoyen_clicked();

    void on_pushButton_rechercheCitoyen_clicked();

private:
    Ui::MainWindow *ui;
    Citoyen C;
};

#endif // MAINWINDOW_H
