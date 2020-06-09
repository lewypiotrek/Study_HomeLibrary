#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QtDebug>
#include <QSqlQueryModel>

class DbConnection:public QSqlDatabase
{
public:

    DbConnection();

    // Database drivers
    bool ConnectToDb(QString databaseName, QString serverName, QString user, QString userPassword);
    bool GetStaus();
    void CheckStatus();

    // Quering
    QStringList ExecQuery(QString Query);
    QSqlQueryModel * ExecTableQuery(QString Query);

private:

    //  Database connections
    QString databaseName;
    QString serverName;
    QString user;
    QString userPassword;
    bool status;
    QSqlDatabase db;
    QString connectionString;

    // Database creation
    void CreateDatabase();  // Create empty database

    // Quering
    QSqlQueryModel *model;

};

#endif // DBCONNECTION_H
