#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include "materiel.h"
#include "travaille.h"

#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMediaPlayer>
#include <QSound>


#include "ui_mainwindow.h"
#include <QPrintDialog>




#include <iostream>

#include <QMessageBox>

#include  <QDebug>

#include <QRadioButton>

#include<QtPrintSupport/QPrinter>

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


#include<QtSql/QSqlQuery>




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
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_lineEdit_12_textChanged(const QString &arg1);

    void on_lineEdit_20_textChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_lineEdit_17_textChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_page2_windowIconChanged(const QIcon &icon);



    void on_tab_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_valider_3_clicked();

private:
    Ui::MainWindow *ui;
    materiel tmpmateriel;
    travaille tmptravaille;

     QSound *son;
     QMediaPlayer *mMediaPlayer;
     QMediaPlayer musicAdd;
};

#endif // MAINWINDOW_H
