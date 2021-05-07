#include "etranger.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>


etranger::etranger()
{
age=0;
numpass="";
nationalite="";
nom=""; prenom=""; activite=""; sexe=""; adresse="";
}

etranger::etranger(QString numpass, QString nom, QString prenom, QString nationalite, QString sexe,int age,QString activite,QString adresse)
{
this->numpass=numpass;
this->nom=nom;
this->prenom=prenom;
this->nationalite=nationalite;
this->sexe=sexe;
this->age=age;
this->activite=activite;
this->adresse=adresse;
}
QString etranger::getnumpass(){return numpass;}
QString etranger::getnom(){return nom;}
QString etranger::getprenom(){return prenom;}
QString etranger::getnationalite(){return nationalite;}
QString etranger::getsexe(){return sexe;}
int     etranger::getage(){return age;}
QString etranger::getactivite(){return activite;}
QString etranger::getadresse(){return adresse;}

void etranger::setnumpass(QString numpass){this->numpass=numpass;}
void etranger::setnom(QString nom){this->nom=nom;}
void etranger::setprenom(QString prenom){this->prenom=prenom;}
void etranger::setnationalite(QString nationalite){this->nationalite=nationalite;}
void etranger::setsexe(QString sexe){this->sexe=sexe;}
void etranger::setage(int age){this->age=age;}
void etranger::setactivite(QString activite){this->activite=activite;}
void etranger::setadresse(QString adresse){this->adresse=adresse;}


bool etranger::ajouter3(){

    QSqlQuery query;
    QString age_string= QString::number(age);

         query.prepare("INSERT INTO etranger (numpass, nom, prenom, nationalite,sexe ,age, activite ,adresse) "
                       "VALUES (:numpass, :nom, :prenom, :nationalite, :sexe, :age ,:activite, :adresse)");
         query.bindValue(":numpass", numpass);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":nationalite", nationalite);
         query.bindValue(":sexe", sexe);
         query.bindValue(":age", age_string);
         query.bindValue(":activite", activite);
         query.bindValue(":adresse",adresse);
         return query.exec();

}

bool etranger::supprimer3(QString numpass)
{
    QSqlQuery query;
    query.prepare("Delete from etranger where numpass=:numpass ");
     query.bindValue(0, numpass);

     return query.exec();
}
QSqlQueryModel* etranger::afficher3()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT * FROM etranger");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("numpass"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("nationalite"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("age"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr("activite"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));
         return model;

}

bool etranger::modifier3(QString numpass)
{
    QSqlQuery query;

    QString age_string= QString::number(age);

    query.prepare("UPDATE etranger set nom='"+nom+"',prenom='"+prenom+"',nationalite='"+nationalite+"',sexe='"+sexe+"',age='"+age_string+"',activite='"+activite+"',adresse='"+adresse+"' WHERE numpass LIKE '"+numpass+"' ");


    query.bindValue(":numCin",numpass);
   query.bindValue(":nom",nom);
   query.bindValue(":prenom",prenom);
   query.bindValue(":nationalite",nationalite);
   query.bindValue(":sexe",sexe);
   query.bindValue(":age",age_string);
   query.bindValue(":activite",activite);
   query.bindValue(":adresse",adresse);

   return query.exec();
}



QSqlQueryModel *etranger::chercher3(QString recherche1)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from etranger where numPass LIKE '"+recherche1+"%' or nom LIKE '"+recherche1+"%' or prenom LIKE '"+recherche1+"%' ");
    return model;
}

QSqlQueryModel * etranger::tri3()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from etranger ORDER BY age DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numpass"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nationalite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("activite"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("adresse"));

        return model;
}

QSqlQueryModel * etranger::rechercheDynamic(QString SearchName)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * from etranger where numPass LIKE '"+SearchName+"%'OR nom like '"+SearchName+"%' OR prenom like '"+SearchName+"%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numpass"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nationalite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("activite"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("adresse"));
    return  model;
    }

