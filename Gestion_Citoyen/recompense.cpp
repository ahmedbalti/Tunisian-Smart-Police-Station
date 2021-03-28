#include "recompense.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

recompense::recompense()
{
numRec=0; nbrPts=0; nbrEx=0;
nomRec=""; description="";
}

recompense::recompense(int numRec,QString nomRec,int nbrEx,QString description,int nbrPts)
{
    this->numRec=numRec;
    this->nomRec=nomRec;
    this->nbrEx=nbrEx;
    this->description=description;
    this->nbrPts=nbrPts;
}

int recompense::getnumRec(){return numRec;}
int recompense::getnbrPts(){return nbrPts;}
int recompense::getnbrEx(){return nbrEx;}
QString recompense::getnomRec(){return nomRec;}
QString recompense::getdescription(){return description;}


void recompense::setnumRec(int numRec)
{
    this->numRec=numRec;
}
void recompense::setnbrPts(int nbrPts)
{
    this->nbrPts=nbrPts;
}
void recompense::setnbrEx(int nbrEx)
{
    this->nbrEx=nbrEx;
}
void recompense::setnomRec(QString nomRec)
{
    this->nomRec=nomRec;
}
void recompense::setdescription(QString description)
{
    this->description=description;
}

bool recompense::ajouter()
{
    QSqlQuery query;
    QString nbrPts_string= QString::number(nbrPts);
    QString numRec_string= QString::number(numRec);
    QString nbrEx_string= QString::number(nbrEx);

    query.prepare("INSERT INTO recompense (numRec, nomRec, nbrEx, description, nbrPts ) "
                  "VALUES (:numRec, :nomRec, :nbrEx, :description, :nbrPts)");
    query.bindValue(":numRec", numRec_string);
    query.bindValue(":nomRec", nomRec);
    query.bindValue(":nbrEx", nbrEx_string);
    query.bindValue(":description", description);
    query.bindValue(":nbrPts", nbrPts_string);
    return query.exec();
}

bool recompense::supprimer(int numRec)
{
    QSqlQuery query;
    query.prepare("Delete from recompense where numRec=:numRec ");
     query.bindValue(0, numRec);

     return query.exec();
}

QSqlQueryModel* recompense::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT * FROM recompense");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("numRec"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomRec"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrEx"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbrPts"));
         return model;

}

bool recompense::modifier(int numRec)
{
    QSqlQuery query;

    QString nbrPts_string= QString::number(nbrPts);
    QString numRec_string= QString::number(numRec);
    QString nbrEx_string= QString::number(nbrEx);


    query.prepare("UPDATE recompense set nomRec='"+nomRec+"',nbrEx='"+nbrEx_string+"',description='"+description+"',nbrPts='"+nbrPts_string+"' WHERE numRec LIKE '"+numRec_string+"' ");

    return query.exec();

}

QSqlQueryModel *recompense::chercher(QString recherche)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from recompense where numRec LIKE '"+recherche+"%' or nomRec LIKE '"+recherche+"%' ");
    return model;
}

QSqlQueryModel * recompense::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from recompense ORDER BY nbrEx DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numRec"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomRec"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrEx"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbrPts"));

        return model;
}

bool recompense::mise_a_jour_nb_exp(int numRec )
{
    QSqlQuery query;
    query.prepare("UPDATE recompense SET nbrEx=(select (nbrEx-1) from cadeau WHERE numRec=:numRec ) WHERE numRec=:numRec");


      query.bindValue(":numRec",numRec);


    return    query.exec();
}
