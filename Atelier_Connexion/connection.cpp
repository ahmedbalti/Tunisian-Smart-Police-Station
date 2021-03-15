#include "connection.h"
#include "QSqlDatabase"
Connection::Connection()
{

}
bool Connection::createConnection(){
    bool test=false;
    QSqlDatabase db =QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Projet2A_21");
    db.setUserName("AhmedBalti");
    db.setPassword("Esprit21");

    if(db.open())
        test=true;
    return test;
}
