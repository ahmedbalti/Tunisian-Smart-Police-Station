#include "materiel.h"

materiel::materiel()
{

}
bool materiel::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO MATERIEL (MAT, MODEL, ETAT,GROUPE) " "VALUES (:mat, :model, :etat, :groupe )");
    query.bindValue(":mat", mat);
    query.bindValue(":model", model);
    query.bindValue(":etat", etat);
    query.bindValue(":groupe", groupe);

    return query.exec();
}
QSqlQueryModel * materiel::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from MATERIEL ");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MODEL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GROUPE"));

    model->setQuery("SELECT MAT, MODEL, ETAT,GROUPE FROM MATERIEL ORDER BY MODEL ");
    return model;

}
bool materiel::supprimer(QString mat)
{
    QSqlQuery query;
    query.prepare("Delete from MATERIEL where MAT = :mat ");
    query.bindValue(":mat",mat);
    return query.exec();
}
bool materiel::modifier(QString mat)
{

    QSqlQuery query;




    query.prepare("UPDATE MATERIEL SET   ETAT = :etat WHERE MAT = :mat " );

    query.bindValue(":mat", mat);
    query.bindValue(":model", model);
    query.bindValue(":etat", etat);
    query.bindValue(":groupe", groupe);

    return query.exec();




}
QSqlQueryModel * materiel::recherche(QString mat)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM MATERIEL WHERE MAT LIKE '%"+mat+"%'");
    model->query().bindValue(":mat",mat);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MODEL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GROUPE"));

    return model;
}


