#ifndef CONNECTIONCHECKTHREAD_H
#define CONNECTIONCHECKTHREAD_H
#include<QtCore>
#include<QDebug>
#include "dbconnection.h"


class ConnectionCheckThread :public QThread
{
public:
    ConnectionCheckThread();  
    ~ConnectionCheckThread();
    void run() override;

    QString name;
    void CopyPtrToDb(DbConnection *pDb);

private:
    bool isPaused;
    DbConnection *db;


};

#endif // CONNECTIONCHECKTHREAD_H
