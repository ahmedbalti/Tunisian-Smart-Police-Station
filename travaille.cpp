#include "travaille.h"

travaille::travaille()
{

}
bool travaille::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO TRAVAILLE (ID, NOMG, NBR,DESCR) " "VALUES (:id, :nomg, :nbr, :descr )");
    query.bindValue(":id", id);
    query.bindValue(":nomg", nomg);
    query.bindValue(":nbr", nbr);
    query.bindValue(":descr", descr);

    return query.exec();
}
QSqlQueryModel * travaille::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from TRAVAILLE ");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMG"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCR"));

    model->setQuery("SELECT ID, NOMG, NBR,DESCR FROM TRAVAILLE ORDER BY NOMG ");
    return model;

}
bool travaille::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("Delete from TRAVAILLE where ID = :id ");
    query.bindValue(":id",id);
    return query.exec();
}
bool travaille::modifier(QString id)
{

    QSqlQuery query;




    query.prepare("UPDATE TRAVAILLE SET   DESCR = :descr WHERE ID = :id " );

    query.bindValue(":id", id);
    query.bindValue(":nomg", nomg);
    query.bindValue(":nbr", nbr);
    query.bindValue(":descr", descr);
    return query.exec();




}
QSqlQueryModel * travaille::recherche(QString id)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM TRAVAILLE WHERE ID LIKE '%"+id+"%'");
    model->query().bindValue(":id",id);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMG"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCR"));

    return model;
}


