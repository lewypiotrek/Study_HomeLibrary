#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QtDebug>

class DbConnection:public QSqlDatabase
{
public:

    DbConnection();

    // Database drivers
    bool ConnectToDb(QString databaseName, QString serverName, QString user, QString userPassword);
    bool GetStaus();
    void CheckStatus();
    QStringList ExecQuery(QString Query);


private:

    //  Database connections
    QString databaseName;
    QString serverName;
    QString user;
    QString userPassword;
    bool status;
    QSqlDatabase db;
    QString connectionString;

    void CreateDatabase();  // Create empty database


};

#endif // DBCONNECTION_H
