#include "detenu.h"

int Detenu::getId() const
{
    return id;
}

void Detenu::setId(int value)
{
    id = value;
}

QString Detenu::getCin() const
{
    return cin;
}

void Detenu::setCin(const QString &value)
{
    cin = value;
}

QString Detenu::getNom() const
{
    return nom;
}

void Detenu::setNom(const QString &value)
{
    nom = value;
}

QString Detenu::getPrenom() const
{
    return prenom;
}

void Detenu::setPrenom(const QString &value)
{
    prenom = value;
}

QString Detenu::getDate() const
{
    return date;
}

void Detenu::setDate(const QString &value)
{
    date = value;
}

QString Detenu::getSexe() const
{
    return sexe;
}

void Detenu::setSexe(const QString &value)
{
    sexe = value;
}

QString Detenu::getActivite() const
{
    return activite;
}

void Detenu::setActivite(const QString &value)
{
    activite = value;
}

QString Detenu::getDescription() const
{
    return description;
}

void Detenu::setDescription(const QString &value)
{
    description = value;
}

bool Detenu::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into detenu (id, cin, nom, prenom, datee, sexe, activite, description, id_cell) values (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(this->id);
    query.addBindValue(this->cin);
    query.addBindValue(this->nom);
    query.addBindValue(this->prenom);
    query.addBindValue(this->date);
    query.addBindValue(this->sexe);
    query.addBindValue(this->activite);
    query.addBindValue(this->description);
    query.addBindValue(this->id_cell);


    if(query.exec()) {
        QSqlQuery query1;
        query1.prepare("update cell set currentt = currentt + 1 where id = ?");
        query1.addBindValue(this->id_cell);
        return query1.exec();
    }
    return false;
}

bool Detenu::modifier()
{
    int cell = getCellId(this->id);
    QSqlQuery query;
    query.prepare("update detenu set cin = ?, nom = ?, prenom = ?, datee = ?, sexe = ?, activite = ?, description = ?, id_cell = ? where id = ?");
    query.addBindValue(this->cin);
    query.addBindValue(this->nom);
    query.addBindValue(this->prenom);
    query.addBindValue(this->date);
    query.addBindValue(this->sexe);
    query.addBindValue(this->activite);
    query.addBindValue(this->description);
    query.addBindValue(this->id_cell);
    query.addBindValue(this->id);


    if(query.exec()) {
        QSqlQuery query1;
        query1.prepare("update cell set currentt = currentt + 1 where id = ?");
        query1.addBindValue(this->id_cell);
        query1.exec();

        query1.prepare("update cell set currentt = currentt - 1 where id = ?");
        query1.addBindValue(cell);
        query1.exec();

        return true;
    }
    return false;
}

bool Detenu::supprimer()
{
    int cell = getCellId(this->id);
    QSqlQuery query;
    query.prepare("delete from detenu where id = ?");
    query.addBindValue(this->id);

    if(query.exec()) {
        QSqlQuery query1;
        query1.prepare("update cell set currentt = currentt - 1 where id = ?");
        query1.addBindValue(cell);
        return query1.exec();
    }
    return false;
}

QSqlQueryModel *Detenu::afficher()
{
    QSqlQuery query;
    query.exec("select * from detenu");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

QSqlQueryModel *Detenu::sort(QString input)
{
    QSqlQuery query;
    query.exec("select * from detenu order by "+input+" asc");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

QSqlQueryModel *Detenu::search(QString input)
{
    QSqlQuery query;
    query.prepare("select * from detenu where cin like ? or nom like ? or prenom like ? or datee like ? or sexe like ? or activite like ? or description like ?");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

void Detenu::fillComboBox(QComboBox *c)
{
    c->clear();
    QSqlQuery query;
    query.exec("select id from detenu");
    while (query.next()) {
        c->addItem(query.value(0).toString());
    }
}

void Detenu::fillComboBox__(QComboBox *c)
{
    c->clear();
    QSqlQuery query;
    query.exec("select id from cell where currentt < max");
    while (query.next()) {
        c->addItem(query.value(0).toString());
    }
}

int Detenu::autoId()
{
    QSqlQuery query;
    int x = 0;
    query.exec("select id from detenu order by id asc");
    while (query.next()) {
        x = query.value(0).toInt();
    }
    x++;
    return x;
}

QString Detenu::count()
{
    QSqlQuery query;
    query.exec("select count(*) from detenu");
    while (query.next()) {
        return query.value(0).toString();
    }
    return "";
}

int Detenu::getCellId(int i)
{
    QSqlQuery query;
    query.exec("select id_cell from detenu where id = "+QString::number(i));
    while (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int Detenu::getId_cell() const
{
    return id_cell;
}

void Detenu::setId_cell(int value)
{
    id_cell = value;
}

Detenu::Detenu()
{

}

Detenu::Detenu(int i, QString c, QString n, QString p, QString d, QString s, QString a, QString ds, int cell)
{
    this->id = i;
    this->cin = c;
    this->nom = n;
    this->prenom = p;
    this->date = d;
    this->sexe = s;
    this->activite = a;
    this->description = ds;
    this->id_cell = cell;
}
