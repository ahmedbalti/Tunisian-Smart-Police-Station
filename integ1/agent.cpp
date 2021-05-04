#include "agent.h"

Agent::Agent()
{

}
Agent::Agent(int id,QString nom,QString prenom,float salaire,QString datenais,QString poste)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->salaire=salaire;
    this->datenais=datenais;
    this->poste=poste;
}


bool Agent::ajouter()
{
    QSqlQuery q;
    QString sal_str=QString::number(salaire);
    q.prepare("insert into agent values(:id,:nom,:prenom,:salaire,:datenais,:poste)");
    q.bindValue(":id",id);//injection SQL (securité)
    q.bindValue(":nom",nom);
    q.bindValue(":prenom",prenom);
    q.bindValue(":salaire",sal_str);
    q.bindValue(":datenais",datenais);
    q.bindValue(":poste",poste);
    return q.exec();

}

QSqlQueryModel * Agent::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from agent");
    return model;
}
bool Agent::supprimer(int id)
{
    QSqlQuery q;
    q.prepare("delete from agent where id=:id");
    q.bindValue(":id",id);
    return q.exec();
}
bool Agent::modifier(int id)
{
    QSqlQuery q;
    QString sal_str=QString::number(salaire);
    q.prepare("update agent set nom=:nom,prenom=:prenom,salaire=:salaire,datenais=:datenais,poste=:poste where id=:id");
    q.bindValue(":id",id);//injection SQL (securité)
    q.bindValue(":nom",nom);
    q.bindValue(":prenom",prenom);
    q.bindValue(":salaire",sal_str);
    q.bindValue(":datenais",datenais);
    q.bindValue(":poste",poste);
    return q.exec();

}
QSqlQueryModel * Agent::trier(QString critere)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from agent order by "+critere+"");
    return model;
}
QSqlQueryModel * Agent::afficherRech(QString critere,QString rech)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from agent where "+critere+" like '"+rech+"%'");
    return model;
}
