#ifndef FILEDRIVER_H
#define FILEDRIVER_H
#include <fstream>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>

using namespace std;

class FileDriver
{
public:
    FileDriver();
    void ReadSettings();
    void SaveSettings(QString databasename, QString servername, QString user, QString userpassword);

    QString GetDatabaseName();
    QString GetServerName();
    QString GetUser();
    QString GetUserPassword();
private:
    fstream Handler;

    QString databaseName;
    QString serverName;
    QString user;
    QString userPassword;
};

#endif // FILEDRIVER_H
