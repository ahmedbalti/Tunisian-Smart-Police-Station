#include "cel.h"

int Cel::getId() const
{
    return id;
}

void Cel::setId(int value)
{
    id = value;
}

QString Cel::getName() const
{
    return name;
}

void Cel::setName(const QString &value)
{
    name = value;
}

int Cel::getMax() const
{
    return max;
}

void Cel::setMax(int value)
{
    max = value;
}

int Cel::getCurrent() const
{
    return current;
}

void Cel::setCurrent(int value)
{
    current = value;
}

bool Cel::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into cell (id, name, max, currentt) values (?, ?, ?, ?)");
    query.addBindValue(this->id);
    query.addBindValue(this->name);
    query.addBindValue(this->max);
    query.addBindValue(this->current);
    return query.exec();
}

bool Cel::modifier()
{
    QSqlQuery query;
    query.prepare("update cell set name = ?, max = ?, currentt = ? where id = ?");
    query.addBindValue(this->name);
    query.addBindValue(this->max);
    query.addBindValue(this->current);
    query.addBindValue(this->id);
    return query.exec();
}

bool Cel::supprimer()
{
    QSqlQuery query;
    query.prepare("delete from cell where id = ?");
    query.addBindValue(this->id);
    return query.exec();
}

QSqlQueryModel *Cel::afficher()
{
    QSqlQuery query;
    query.exec("select * from cell");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

QSqlQueryModel *Cel::sort(QString input)
{
    QSqlQuery query;
    query.exec("select * from cell order by "+input+" asc");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

QSqlQueryModel *Cel::search(QString input)
{
    QSqlQuery query;
    query.prepare("select * from cell where name like ? or max like ? or currentt like ?");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.addBindValue("%"+input+"%");
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

void Cel::fillComboBox(QComboBox *c)
{
    c->clear();
    QSqlQuery query;
    query.exec("select id from cell");
    while (query.next()) {
        c->addItem(query.value(0).toString());
    }
}

int Cel::autoId()
{
    QSqlQuery query;
    int x = 0;
    query.exec("select id from cell order by id asc");
    while (query.next()) {
        x = query.value(0).toInt();
    }
    x++;
    return x;
}

Cel::Cel()
{

}

Cel::Cel(int i, QString n, int m, int c)
{
    this->id = i;
    this->name = n;
    this->max = m;
    this->current = c;
}
