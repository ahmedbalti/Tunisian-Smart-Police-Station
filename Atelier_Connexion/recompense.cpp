#include "recompense.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

recompense::recompense()
{
numRec=0; nbrPts=0; nbrEx=0;
nomRec=""; desc="";
}

recompense::recompense(int numRec,QString nomRec,int nbrEx,QString desc,int nbrPts)
{
    this->numRec=numRec;
    this->nomRec=nomRec;
    this->nbrEx=nbrEx;
    this->desc=desc;
    this->nbrPts=nbrPts;
}

int recompense::getnumRec(){return numRec;}
int recompense::getnbrPts(){return nbrPts;}
int recompense::getnbrEx(){return nbrEx;}
QString recompense::getnomRec(){return nomRec;}
QString recompense::getdesc(){return desc;}


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
void recompense::setdesc(QString desc)
{
    this->desc=desc;
}

bool recompense::ajouter()
{
    QSqlQuery query;
    QString nbrPts_string= QString::number(nbrPts);
    QString numRec_string= QString::number(numRec);
    QString nbrEx_string= QString::number(nbrEx);

    query.prepare("INSERT INTO recompense (numRec, nomRec, nbrEx, desc, nbrPts ) "
                  "VALUES (:numRec, :nomRec, :nbrEx, :desc, :nbrPts)");
    query.bindValue(":numRec", numRec_string);
    query.bindValue(":nomRec", nomRec);
    query.bindValue(":nbrEx", nbrEx_string);
    query.bindValue(":desc", desc);
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
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("desc"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbrPts"));
         return model;

}

bool recompense::modifier(int numRec)
{
    QSqlQuery query;

    QString nbrPts_string= QString::number(nbrPts);
    QString numRec_string= QString::number(numRec);
    QString nbrEx_string= QString::number(nbrEx);


    query.prepare("UPDATE recompense set nomRec='"+nomRec+"',nbrEx='"+nbrEx_string+"',desc='"+desc+"',nbrPts='"+nbrPts_string+"' WHERE numRec LIKE '"+numRec_string+"' ");

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
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("desc"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbrPts"));

        return model;
}
