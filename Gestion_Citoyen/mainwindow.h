#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets/QMessageBox>
#include"recompense.h"
#include <QMediaPlayer>
#include <QSound>
#include"citoyen.h"

namespace Ui {
class MainWindow;
}
class QMediaPlayer;
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

    void on_triCitoyen_clicked();

    void on_ajouterRec_2_clicked();

    void on_modiferRecompense_clicked();

    void on_pushButton_rechercheRecompense_clicked();

    void on_triRecompense_clicked();

    void on_Supprimer_2_clicked();

private:
    Ui::MainWindow *ui;
QSound *son;
    Citoyen tmpcitoyen;
    recompense tmprecompense;
    QMediaPlayer *mMediaPlayer;

};

#endif // MAINWINDOW_H
