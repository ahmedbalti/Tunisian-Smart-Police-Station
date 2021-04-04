#ifndef CITOYEN_H
#define CITOYEN_H
#include <QString>
#include<QSqlQueryModel>
#include<QDate>
class Citoyen
{
public:
    Citoyen();
    Citoyen(int,QString,QString,QString,QString,QString,int,int);

    int getnumCin();
    QString getnom();
    QString getprenom();
    QString getdaten();
    QString getsexe();
    QString getactivite();
    int getnbrPts();
    int getnumRec();

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);

    void setnumCin(int);
    void setnom(QString);
    void setprenom(QString);
    void setdaten(QString);
    void setsexe(QString);
    void setactivite(QString);
    void setnbrPts(int);
    void setnumRec(int);
    int test(int);
QSqlQueryModel * chercher(QString);
QSqlQueryModel * affecter_recompense();
QSqlQueryModel * tri();

bool affecter(QString);
 private:
    int nbrPts,numCin,numRec;
    QString nom,prenom,daten,sexe,activite;
};

#endif // CITOYEN_H
