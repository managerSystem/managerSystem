#ifndef CONNECT_DATABASE
#define CONNECT_DATABASE

#include <QSqlDatabase>
#include <QSqlQuery>

bool connect_mysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("123");
    db.setDatabaseName("managerSystem");

    return db.open();
}

#endif // CONNECT_DATABASE

