#include "citoyen.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include"recompense.h"

Citoyen::Citoyen()
{
nbrPts=0;
numCin="";
numRec="";
nom=""; prenom=""; daten=""; sexe=""; activite="";
}

Citoyen::Citoyen(QString numCin, QString nom, QString prenom, QString daten, QString sexe,QString activite,int nbrPts,QString numRec)
{
this->numCin=numCin;
this->nom=nom;
this->prenom=prenom;
this->daten=daten;
this->sexe=sexe;
this->activite=activite;
this->nbrPts=nbrPts;
this->numRec=numRec;
}
QString Citoyen::getnumCin(){return numCin;}
QString Citoyen::getnom(){return nom;}
QString Citoyen::getprenom(){return prenom;}
QString Citoyen::getdaten(){return daten;}
QString Citoyen::getsexe(){return sexe;}
QString Citoyen::getactivite(){return activite;}
int Citoyen::getnbrPts(){return nbrPts;}
QString Citoyen::getnumRec(){return numRec;}

void Citoyen::setnumCin(QString numCin){this->numCin=numCin;}
void Citoyen::setnom(QString nom){this->nom=nom;}
void Citoyen::setprenom(QString prenom){this->prenom=prenom;}
void Citoyen::setdaten(QString daten){this->daten=daten;}
void Citoyen::setsexe(QString sexe){this->sexe=sexe;}
void Citoyen::setactivite(QString activite){this->activite=activite;}
void Citoyen::setnbrPts(int nbrPts){this->nbrPts=nbrPts;}
void Citoyen::setnumRec(QString numRec){this->numRec=numRec;}

bool Citoyen::ajouter(){
   // bool test=false;
    QSqlQuery query;
    QString nbrPts_string= QString::number(nbrPts);
   // QString numCin_string= QString::number(numCin);
   // QString numRec_string= QString::number(numRec);
         query.prepare("INSERT INTO Citoyen (numCin, nom, prenom, daten,sexe ,activite, nbrPts ,numRec) "
                       "VALUES (:numCin, :nom, :prenom, :daten, :sexe, :activite, :nbrPts, :numRec)");
         query.bindValue(":numCin", numCin);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":daten", daten);
         query.bindValue(":sexe", sexe);
         query.bindValue(":activite", activite);
         query.bindValue(":nbrPts", nbrPts_string);
         query.bindValue(":numRec",numRec);
         return query.exec();

}

bool Citoyen::supprimer(QString numCin)
{
    QSqlQuery query;
    query.prepare("Delete from Citoyen where numCin=:numCin ");
     query.bindValue(0, numCin);

     return query.exec();
}
QSqlQueryModel* Citoyen::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT * FROM Citoyen");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("numCin"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("daten"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("activite"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("nbrPts"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr("numRec"));
         return model;

}

bool Citoyen::modifier(QString numCin)
{
    QSqlQuery query;

    //QString nbrPts= QString::number(nbrPts);

    QString nbrPts_string= QString::number(nbrPts);
    //QString numRec_string= QString::number(numRec);
    // QString numCin_string= QString::number(numCin);

    query.prepare("UPDATE Citoyen set nom='"+nom+"',prenom='"+prenom+"',date='"+daten+"',sexe='"+sexe+"',activite='"+activite+"',nbrPts='"+nbrPts_string+"',numRec='"+numRec+"' WHERE numCin LIKE '"+numCin+"' ");




    query.bindValue(":numCin",numCin);
   query.bindValue(":nom",nom);
   query.bindValue(":prenom",prenom);
   query.bindValue(":daten",daten);
   query.bindValue(":sexe",sexe);
   query.bindValue(":activite",activite);
   query.bindValue(":nbrPts",nbrPts);
   query.bindValue(":numRec",numRec);

   return query.exec();
}

//bool Commande::modifier (int id_com,int num_l,QString nom_cat,QString nom_cl)
//{
//    QSqlQuery query;
//    query.prepare("UPDATE COMMANDES SET id_com= :id_com,num_l= :num_l,nom_cat= :nom_cat,nom_cl = :nom_cl  WHERE id_com= :id_com ");
//    query.bindValue(":id_com",id_com);
//    query.bindValue(":num_l",num_l);
//    query.bindValue(":nom_cat",nom_cat);
//    query.bindValue(":nom_cl",nom_cl);
//    return    query.exec();
//}

QSqlQueryModel *Citoyen::chercher(QString recherche)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Citoyen where numCin LIKE '"+recherche+"%' or nom LIKE '"+recherche+"%' or prenom LIKE '"+recherche+"%' ");
    return model;
}

QSqlQueryModel * Citoyen::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Citoyen ORDER BY nbrPts DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numCin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("daten"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("activite"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nbrPts"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("numRec"));

        return model;
}

QSqlQueryModel * Citoyen::affecter_recompense()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select numRec from recompense");

        return model;
}




