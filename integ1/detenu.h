#ifndef DETENU_H
#define DETENU_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>

class Detenu
{
private:
    int id;
    QString cin;
    QString nom;
    QString prenom;
    QString date;
    QString sexe;
    QString activite;
    QString description;
    int id_cell;

public:
    Detenu();
    Detenu(int, QString, QString, QString, QString, QString, QString, QString, int);

    int getId() const;
    void setId(int value);
    QString getCin() const;
    void setCin(const QString &value);
    QString getNom() const;
    void setNom(const QString &value);
    QString getPrenom() const;
    void setPrenom(const QString &value);
    QString getDate() const;
    void setDate(const QString &value);
    QString getSexe() const;
    void setSexe(const QString &value);
    QString getActivite() const;
    void setActivite(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);

    bool ajouter();
    bool modifier();
    bool supprimer();

    QSqlQueryModel *afficher();
    QSqlQueryModel *sort(QString);
    QSqlQueryModel *search(QString);

    void fillComboBox(QComboBox *);
    void fillComboBox__(QComboBox *);
    int autoId();
    QString count();

    int getCellId(int);

    int getId_cell() const;
    void setId_cell(int value);
};

#endif // DETENU_H
