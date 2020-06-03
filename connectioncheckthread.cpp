#include "connectioncheckthread.h"

ConnectionCheckThread::ConnectionCheckThread()
{
    name = "DatabaseConnectionStatus";
    isPaused = false;
}


ConnectionCheckThread::~ConnectionCheckThread()
{
    exit();
    quit();
}


void ConnectionCheckThread::run()
{
    while (!isPaused)
    {
        if(db->GetStaus())
        {
            qDebug() << "elo 3 2 0";
        }
        else
        {
            qDebug() << "nope";
        }

        QThread::sleep(2);
    }


}

void ConnectionCheckThread::CopyPtrToDb(DbConnection *pDb)
{
    db = pDb;
}
