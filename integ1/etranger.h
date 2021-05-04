#ifndef ETRANGER_H
#define ETRANGER_H

#include <QString>
#include<QSqlQueryModel>

class etranger
{
public:
    etranger();
    etranger(QString,QString,QString,QString,QString,int,QString,QString);

    QString getnumPass();
    QString getnom();
    QString getprenom();
    QString getnationalite();
    QString getsexe();
    int getage();
    QString getactivite();
    QString getadresse();

    bool ajouter3();
    QSqlQueryModel* afficher3();
    bool supprimer3(QString);
    bool modifier3(QString);

    void setnumPass(QString);
    void setnom(QString);
    void setprenom(QString);
    void setnationalite(QString);
    void setsexe(QString);
    void setage(int);
    void setactivite(QString);
    void setadresse(QString);

QSqlQueryModel * chercher3(QString);
QSqlQueryModel * tri3();

 private:
    int age;
    QString nom,prenom,nationalite,sexe,activite,numPass,adresse;
};



#endif // ETRANGER_H
