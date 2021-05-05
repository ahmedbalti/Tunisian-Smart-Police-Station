#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "citoyen.h"
#include "recompense.h"
#include <QDialog>
#include <QApplication>
#include "login.h"
#include "smtp.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QSound>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include "cel.h"
#include "detenu.h"
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QMouseEvent>
#include <QtWidgets/QMessageBox>
#include<agent.h>
#include<conge.h>
#include"etranger.h"
#include"note.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void refrech();
public slots:
    void clockTimer();
private slots:
    void sendMail();
    void mailSent(QString);
    void browse();
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

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_tableCitoyen_activated(const QModelIndex &index);

    void on_tableRecompense_activated(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void replyFinished(QNetworkReply* reply);

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_le_search_2_textChanged(const QString &arg1);

    void on_le_search_textChanged(const QString &arg1);

    void on_cb_sort_2_currentTextChanged(const QString &arg1);

    void on_cb_sort_currentTextChanged(const QString &arg1);

    void on_pushButton_25_clicked();

    void on_pushButton_valider_3_clicked();

    void on_pushButton_quitter_3_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_valider_clicked();

    void on_pushButton_quitter_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_31_clicked();

    void on_ajouter_2_clicked();

    void on_ajouter_etranger_clicked();

    void on_pushButton_recherche_3_clicked();

    void on_tri_3_clicked();

    void on_modifer_3_clicked();

    void on_supp_3_clicked();

    void on_tableEtranger_activated(const QModelIndex &index);

    void on_pushButton_32_clicked();

    void on_pushButton_36_clicked();

private:
    Ui::MainWindow *ui;
    Citoyen tmpcitoyen;
    recompense tmprecompense;
    etranger tmpetranger;
    QStringList files;
    QSound *son;
    QMediaPlayer *mMediaPlayer;
    QMediaPlayer musicAdd;
    Cel C;
    Detenu D;
    QTimer timer;
    Agent tmpa;
    conge tmpb;
    note *notepad;

};
#endif // MAINWINDOW_H
