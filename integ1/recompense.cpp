#include "recompense.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

recompense::recompense()
{
numRec=""; nbrPts=0; nbrEx=0;
nomRec=""; description="";
}

recompense::recompense(QString numRec,QString nomRec,int nbrEx,QString description,int nbrPts)
{
    this->numRec=numRec;
    this->nomRec=nomRec;
    this->nbrEx=nbrEx;
    this->description=description;
    this->nbrPts=nbrPts;
}

QString recompense::getnumRec(){return numRec;}
int recompense::getnbrPts(){return nbrPts;}
int recompense::getnbrEx(){return nbrEx;}
QString recompense::getnomRec(){return nomRec;}
QString recompense::getdescription(){return description;}


void recompense::setnumRec(QString numRec)
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
    //QString numRec_string= QString::number(numRec);
    QString nbrEx_string= QString::number(nbrEx);

    query.prepare("INSERT INTO recompense (numRec, nomRec, nbrEx, description, nbrPts ) "
                  "VALUES (:numRec, :nomRec, :nbrEx, :description, :nbrPts)");
    query.bindValue(":numRec", numRec);
    query.bindValue(":nomRec", nomRec);
    query.bindValue(":nbrEx", nbrEx_string);
    query.bindValue(":description", description);
    query.bindValue(":nbrPts", nbrPts_string);
    return query.exec();
}

bool recompense::supprimer(QString numRec)
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

//bool recompense::modifier(QString numRec)
//{
//    QSqlQuery query;

//    QString nbrPts_string= QString::number(nbrPts);
//   // QString numRec_string= QString::number(numRec);
//    QString nbrEx_string= QString::number(nbrEx);


//    query.prepare("UPDATE recompense set nomRec='"+nomRec+"',nbrEx='"+nbrEx_string+"',description='"+description+"',nbrPts='"+nbrPts_string+"' WHERE numRec LIKE '"+numRec+"' ");

//    return query.exec();

//}

bool recompense::modifier()
{
    QSqlQuery query;
    query.prepare("update recompense set nomRec = ?, nbrEx = ?, nbrPts = ? , description = ? where numRec = ?");
    query.addBindValue(this->numRec);
    query.addBindValue(this->nomRec);
    query.addBindValue(this->nbrEx);
    query.addBindValue(this->nbrPts);
    query.addBindValue(this->description);

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

int recompense::calculer(QString type) {
      QSqlQuery query;
      //query.prepare("select *  from recompense r  join Citoyen ci on(r.numRec=ci.numRec) where(r.nomRec = :type)");
      query.prepare("select *  from recompense  where ( nomRec = :type)");
      query.bindValue(":type", type);

   query.exec();
      int total = 0;
      while (query.next()) {
        total++;
      }
return total;

      }

QSqlQueryModel * recompense::rechercheDynamic(QString SearchName)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * from recompense where numRec LIKE '"+SearchName+"%'OR nomRec like '"+SearchName+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numRec"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomRec"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrEx"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbrPts"));

        return model;
}


