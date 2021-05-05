#ifndef AGENT_H
#define AGENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Agent
{
public:
    Agent();
    Agent(int id,QString nom,QString prenom,float salaire,QString datenais,QString poste);
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * trier(QString);
    QSqlQueryModel * afficherRech(QString,QString);
    bool supprimer(int);
    bool modifier(int);
private:
    int id;
    QString nom,prenom,datenais,poste;
    float salaire;

};

#endif // AGENT_H
