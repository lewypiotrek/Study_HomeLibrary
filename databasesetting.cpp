#include "databasesetting.h"
#include "ui_databasesetting.h"

DatabaseSetting::DatabaseSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSetting)
{
    ui->setupUi(this);
}


DatabaseSetting::~DatabaseSetting()
{
    delete ui;
}

void DatabaseSetting::CopyPtrToDb(DbConnection *pDb)
{
    db = pDb;
}

void DatabaseSetting::on_pushButton_clicked()
{
    QString databaseName = ui->DatabaseName->text();
    QString servername = ui->ServerName->text();
    QString user = ui->User->text();
    QString password = ui->password->text();


   // bool test = db->ConnectToDb("CRM","LOCALHOST\\SQLEXPRESS","sa","S*#rrQl*mA");

    //bool test = db->ConnectToDb("CRM","127.0.0.1,1435","sa","S*#rrQl*mA");
    bool test = db->ConnectToDb(databaseName,servername,user,password);

    if (test)
    {

    }
}
