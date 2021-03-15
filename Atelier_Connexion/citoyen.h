#ifndef CITOYEN_H
#define CITOYEN_H
#include <QString>
#include<QSqlQueryModel>
class Citoyen
{
public:
    Citoyen();
    Citoyen(int,QString,QString,QString,QString,QString,int,int);

    int getnumCin();
    QString getnom();
    QString getprenom();
    QString getdate();
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
    void setdate(QString);
    void setsexe(QString);
    void setactivite(QString);
    void setnbrPts(int);
    void setnumRec(int);
QSqlQueryModel * chercher(QString);

QSqlQueryModel * tri();
 private:
    int nbrPts,numCin,numRec;
    QString nom,prenom,date,sexe,activite;
};

#endif // CITOYEN_H
