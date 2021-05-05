#include "conge.h"

conge::conge()
{

}
conge::conge(int id,QString duree,QString datedem,QString poste,QString typecon)
{
    this->id=id;
    this->duree=duree;
    this->datedem=datedem;
    this->poste=poste;
    this->typecon=typecon;
}
bool conge::ajouter()
{
    QSqlQuery q;

    q.prepare("insert into conge values(:id,:duree,:datedem,:poste,:typeconge)");
    q.bindValue(":id",id);//injection SQL (securité)
    q.bindValue(":duree",duree);
    q.bindValue(":datedem",datedem);
    q.bindValue(":poste",poste);
    q.bindValue(":typeconge",typecon);
    return q.exec();

}
QSqlQueryModel * conge::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from conge");
    return model;
}
bool conge::supprimer(int id)
{
    QSqlQuery q;
    q.prepare("delete from conge where id=:id");
    q.bindValue(":id",id);
    return q.exec();
}
bool conge::modifier(int id)
{
    QSqlQuery q;

    q.prepare("update conge set duree=:duree,datededemande=:datedem,poste=:poste,typedeconge=:typecon where id=:id");
    q.bindValue(":id",id);//injection SQL (securité)
    q.bindValue(":duree",duree);
    q.bindValue(":datedem",datedem);
    q.bindValue(":poste",poste);
    q.bindValue(":typecon",typecon);
    return q.exec();

}
