#ifndef CEL_H
#define CEL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>

class Cel
{
private:
    int id;
    QString name;
    int max;
    int current;
public:
    Cel();
    Cel(int, QString, int, int);
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);
    int getMax() const;
    void setMax(int value);
    int getCurrent() const;
    void setCurrent(int value);

    bool ajouter();
    bool modifier();
    bool supprimer();

    QSqlQueryModel* afficher();
    QSqlQueryModel* sort(QString);
    QSqlQueryModel* search(QString);

    void fillComboBox(QComboBox *);
    int autoId();
};

#endif // CEL_H
