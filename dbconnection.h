#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QTableView>

class DbConnection:public QSqlDatabase
{
public:

    DbConnection();

    // Database drivers
    bool ConnectToDb(QString databaseName, QString serverName, QString user, QString userPassword);
    bool GetStaus();
    void CheckStatus();
    QString GetDatabaseName();

    // Quering
    QStringList ExecQuery(QString Query);
    QSqlQueryModel ExecTableQuery(QString Query);
    void ClearTableViewModel();

private:

    //  Database connections
    QString databaseName;
    QString serverName;
    QString user;
    QString userPassword;
    bool status;
    QSqlDatabase db;
    QString connectionString;


};

#endif // DBCONNECTION_H
