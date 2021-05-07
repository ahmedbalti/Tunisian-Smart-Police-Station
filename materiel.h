#ifndef MATERIEL_H
#define MATERIEL_H


#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QPainter>
#include <QGraphicsItem>



class materiel
{
private:
    QString mat,model,etat,groupe;


public:
    materiel();
    materiel(QString mat,QString model ,QString etat ,QString groupe){
        this->mat = mat ;
        this->model = model;
        this->etat=etat;
        this->groupe=groupe;



    }
    void setmat(QString mat){this->mat=mat;}
    QString getmat(){return this->mat;}
    void setmodel(QString model){this->model=model;}
    QString getmodel(){return this->model;}
    void setetat(QString etat){this->etat=etat;}
    QString getetat(){return this->etat;}
    void setgroupe(QString groupe){this->groupe=groupe;}
    QString getgroupe(){return this->groupe;}

    bool ajouter();
    bool modifier(QString mat);
    bool supprimer(QString mat);

    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString mat);
};

#endif // MATERIEL_H
