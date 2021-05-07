#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include<QtTextToSpeech/QTextToSpeech>
#include <QMediaPlayer>
#include <QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    QSound *son;
    QMediaPlayer *mMediaPlayer;
    QMediaPlayer musicAdd;
    bool test=c.createconnect();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        w.show();
        QTextToSpeech *l_speech=new QTextToSpeech();
        l_speech->say("welcome to police station ");
        QMediaPlayer *player = new QMediaPlayer();
        player->setMedia(QUrl("url:/afterinfinity-science-medicine-royalty-free-music.mp3"));
        player->setVolume(50);
        player->play();
        musicAdd.setMedia(QUrl("C:/Users/houssem/Desktop/Atelier_Connexion/Resources/afterinfinity-science-medicine-royalty-free-music.mp3"));
        musicAdd.play();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
