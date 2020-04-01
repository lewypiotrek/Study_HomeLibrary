#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QMessageBox>


class DbConnection:public QSqlDatabase
{
public:
    DbConnection();
    bool ConnectToDb(QString databaseName, QString serverName, QString user, QString userPassword);
private:
    QString databaseName;
    QString serverName;
    QString user;
    QString userPassword;
    bool status;
    QSqlDatabase db;
    QString connectionString;


};

#endif // DBCONNECTION_H
