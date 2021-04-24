#ifndef RECOMPENSE_H
#define RECOMPENSE_H
#include<QString>
#include<QSqlQueryModel>

class recompense
{
private:
    QString numRec;
    int nbrPts;
    int nbrEx;

    QString nomRec,description;


public:
    recompense();
    recompense(QString,QString,int,QString,int);

    QString getnumRec();
    int getnbrPts();
    int getnbrEx();
    QString getnomRec();
    QString getdescription();

    void setnumRec(QString);
    void setnbrPts(int);
    void setnbrEx(int);
    void setnomRec(QString);
    void setdescription(QString);
    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel* afficher();
    bool modifier(QString);
    QSqlQueryModel * chercher(QString);
    QSqlQueryModel * tri();
    QSqlQueryModel * affecter_recompense();

    int  calculer(QString);


};

#endif // RECOMPENSE_H
