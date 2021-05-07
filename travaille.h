#ifndef TRAVAILLE_H
#define TRAVAILLE_H


#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QPainter>
#include <QGraphicsItem>



class travaille
{
private:
    QString id,nomg,nbr,descr;


public:
    travaille();
    travaille(QString id,QString nomg ,QString nbr ,QString descr){
        this->id = id ;
        this->nomg = nomg;
        this->nbr=nbr;
        this->descr=descr;



    }
    void setid(QString id){this->id=id;}
    QString getid(){return this->id;}
    void setnomg(QString nomg){this->nomg=nomg;}
    QString getnomg(){return this->nomg;}
    void setnbr(QString nbr){this->nbr=nbr;}
    QString getnbr(){return this->nbr;}
    void setdescr(QString descr){this->descr=descr;}
    QString getdescr(){return this->descr;}

    bool ajouter();
    bool modifier(QString id);
    bool supprimer(QString id);

    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString id);
};
#endif // TRAVAILLE_H
