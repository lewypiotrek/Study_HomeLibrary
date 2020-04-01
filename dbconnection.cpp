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

