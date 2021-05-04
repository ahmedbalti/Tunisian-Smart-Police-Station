#ifndef conge_H
#define conge_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class conge
{
public:
    conge();
    conge(int id,QString duree,QString datedem,QString poste,QString typecon);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
private:
    int id;
    QString duree,datedem,poste,typecon;


};

#endif // CONGE_H
