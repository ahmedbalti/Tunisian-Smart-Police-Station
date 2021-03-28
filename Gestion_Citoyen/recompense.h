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

    QString nomRec,description;


public:
    recompense();
    recompense(int,QString,int,QString,int);

    int getnumRec();
    int getnbrPts();
    int getnbrEx();
    QString getnomRec();
    QString getdescription();

    void setnumRec(int);
    void setnbrPts(int);
    void setnbrEx(int);
    void setnomRec(QString);
    void setdescription(QString);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    bool modifier(int);
    QSqlQueryModel * chercher(QString);
    QSqlQueryModel * tri();
    bool mise_a_jour_nb_exp(int);
};

#endif // RECOMPENSE_H
