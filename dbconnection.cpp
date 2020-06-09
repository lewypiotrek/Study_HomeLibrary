#include "dbconnection.h"

DbConnection::DbConnection()
{
    this->databaseName = "";
    this->serverName = "";
    this->user="";
    this->userPassword = "";
    status = false;

    // Setting driver and timeouts
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions("SQL_ATTR_CONNECTION_TIMEOUT=1;SQL_ATTR_LOGIN_TIMEOUT=1");

}


// Connect to database databaseName,serverName,user,userPassword
bool DbConnection::ConnectToDb(QString databaseName,
                               QString serverName,
                               QString user,
                               QString userPassword)
{
    this->databaseName = databaseName;  //CRM
    this->serverName = serverName;      //LOCALHOST\\SQLEXPRESS
    this->user = user;                  //SA
    this->userPassword = userPassword;  //S*#rrQl*mA

    connectionString = "DRIVER={SQL SERVER};SERVER="+ serverName +";DATABASE=" + databaseName + ";UID=" + user +";PWD=" + userPassword + ";Trusted_Connection=Yes";
    try {
        db.setDatabaseName(connectionString);
        status = db.open();
        if(!status)
        {
            QString error = "Unable to connect \nDatabse:" + databaseName + "\nServer: " + serverName;
            throw error;
        }
        else
        {
            QMessageBox msg;
            msg.setText("Connected!");
            msg.setIcon(QMessageBox::Information);
            msg.exec();
        }
    }
    catch (QString & error)
    {
        QMessageBox msg;
        msg.setText(error);
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }

    if(status)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Connection status
bool DbConnection::GetStaus()
{
    status = db.open();
    return status;
}

void DbConnection::CreateDatabase()
{

}

QStringList DbConnection::ExecQuery(QString Query)
{
    QSqlQuery QueryHandler(db);
    QStringList List;

    try
    {
        if(!QueryHandler.prepare(Query))
        {
            QString error = QueryHandler.lastError().text();
            throw error;
        }
        else
        {
            QueryHandler.exec(Query);
            int i = 0;
            while(QueryHandler.next())
            {
                List << QueryHandler.value(i).toString();
                i++;
            }
        }

    }
    catch (QString & Error)
    {
        QMessageBox msg;
        msg.setText("Error(while quering): " + Error);
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }


    return List;
}

void DbConnection::CheckStatus()
{

    status = db.open();
    if(!status)
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Database connection lost!");
        msg.exec();
    }
}

QSqlQueryModel * DbConnection::ExecTableQuery(QString Query)
{
    if(model != nullptr)
    {
        delete model;
    }

    model = new QSqlQueryModel;
    model->setQuery(Query);

    return model;
}

