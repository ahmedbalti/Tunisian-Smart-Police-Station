#ifndef RECOMPENSE_H
#define RECOMPENSE_H
#include<QString>
#include<QSqlQueryModel>

class recompense
{
private:
    int numRec;
    int nbrPts;
    int nbrEx;

    QString nomRec,desc;


public:
    recompense();
    recompense(int,QString,int,QString,int);

    int getnumRec();
    int getnbrPts();
    int getnbrEx();
    QString getnomRec();
    QString getdesc();

    void setnumRec(int);
    void setnbrPts(int);
    void setnbrEx(int);
    void setnomRec(QString);
    void setdesc(QString);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    bool modifier(int);
    QSqlQueryModel * chercher(QString);
    QSqlQueryModel * tri();
};

#endif // RECOMPENSE_H
