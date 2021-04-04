#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "citoyen.h"
#include "recompense.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_supp_clicked();

    void on_modifer_clicked();

    void on_pushButton_recherche_clicked();

    void on_tri_clicked();



    void on_pushButton_modifierconges_clicked();

    void on_modifierRecompense_clicked();

    void on_ajouterRecomp_clicked();

    void on_pushButton_clicked();

    void on_rechercheRecompense_clicked();

    void on_triRecomp_clicked();

private:
    Ui::MainWindow *ui;
    Citoyen tmpcitoyen;
    recompense tmprecompense;
};
#endif // MAINWINDOW_H
