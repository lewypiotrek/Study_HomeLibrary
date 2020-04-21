#include "filedriver.h"

FileDriver::FileDriver()
{
    QString fileName("Config.txt");
    QFile file(fileName);

    if(!QFileInfo::exists(fileName))
    {
        try {
            Handler.open("Config.txt",ios::out);
            Handler << "## CONFIGURATION DATABASE CONNECTIONS ##\nDATABASENAME: 0\nDATABSESERVER: 0\nUSERNAME: 0\nPASSWORD: 0\n#########################################";
            Handler.close();
        } catch (...) {
            QMessageBox test;
            test.setText("Unhandled exception - Unable to create object FileDriver");
            test.exec();
        }
    }


    databaseName = "0";
    serverName = "0";
    user = "0";
    userPassword = "0";
}

void FileDriver::ReadSettings()
{
    Handler.open("Config.txt", ios::in);
    string stream = "0";

    try
    {
       if(!Handler.good())
       {
           QString error = "Error: Cannot open Config file";
           throw error;
       }
       else
       {
          Handler.seekg(56);        // Database name
          getline(Handler,stream);
          databaseName = QString::fromStdString(stream);

          Handler.seekg(15, ios::cur); // Server name
          getline(Handler,stream);
          serverName = QString::fromStdString(stream);

          Handler.seekg(9, ios::cur);   // User name
          getline(Handler,stream);
          user = QString::fromStdString(stream);

          Handler.seekg(9, ios::cur);   // User name
          getline(Handler,stream);
          userPassword = QString::fromStdString(stream);

       }

       QMessageBox test;
       test.setText(databaseName +"\n" + serverName + "\n" + user + "\n" + userPassword);
       test.exec();

    }
    catch (QString & error)
    {
       QMessageBox msg;
       msg.setText(error);
       msg.setWindowTitle("Error !");
       msg.setIcon(QMessageBox::Warning);
       msg.exec();
    }
    catch(...)
    {
        Handler.close();
        QMessageBox msg;
        msg.setText("Unhandled Error while trying to handle Config.txt file.");
        msg.setWindowTitle("Error !");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }

    Handler.close();
}

void FileDriver::SaveSettings(QString databasename, QString servername, QString user, QString userpassword)
{
    Handler.open("Config.txt", ios::in);
    string stream = "0";

    try
    {
       if(!Handler.good())
       {
           QString error = "Error: Cannot open Config file";
           throw error;
       }
       else
       {
          Handler.seekg(56);        // Database name
          getline(Handler,stream);
          databaseName = QString::fromStdString(stream);

          Handler.seekg(15, ios::cur); // Server name
          getline(Handler,stream);
          serverName = QString::fromStdString(stream);

          Handler.seekg(9, ios::cur);   // User name
          getline(Handler,stream);
          user = QString::fromStdString(stream);

          Handler.seekg(9, ios::cur);   // User name
          getline(Handler,stream);
          userPassword = QString::fromStdString(stream);

       }

    }
    catch (QString & error)
    {
       QMessageBox msg;
       msg.setText(error);
       msg.setWindowTitle("Error !");
       msg.setIcon(QMessageBox::Warning);
       msg.exec();
    }
    catch(...)
    {
        Handler.close();
        QMessageBox msg;
        msg.setText("Unhandled Error while trying to handle Config.txt file.");
        msg.setWindowTitle("Error !");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
}
