#include "databasesetting.h"
#include "ui_databasesetting.h"


DatabaseSetting::DatabaseSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSetting)
{
    ui->setupUi(this);
    ui->label_5->hide();


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
    // After click button "Try to connect" the connection attempt will be begin
    QString databaseName = ui->DatabaseName->text();
    QString servername = ui->ServerName->text();
    QString user = ui->User->text();
    QString password = ui->password->text();

    db->ConnectToDb(databaseName,servername,user,password);
    //db->GetStaus();
}

void DatabaseSetting::on_pushButton_3_clicked()
{
    this->close();
}

void DatabaseSetting::on_checkBox_stateChanged(int arg1)
{
        if(ui->password->echoMode() == QLineEdit::Password)
        {
            ui->password->setEchoMode(QLineEdit::Normal);
        }
        else
        {
            ui->password->setEchoMode(QLineEdit::Password);
        }
}


void DatabaseSetting::on_pushButton_2_clicked()
{
    // Save connection string to the Config.txt

    FileDriver File;
    QString databaseName = ui->DatabaseName->text();
    QString serverName = ui->ServerName->text();
    QString user = ui->User->text();
    QString password = ui->password->text();

    File.SaveSettings(databaseName,serverName,user,password);
    ui->label_5->setHidden(false);
}
