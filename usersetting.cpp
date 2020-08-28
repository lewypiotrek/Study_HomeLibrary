#include "usersetting.h"
#include "ui_usersetting.h"

UserSetting::UserSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSetting)
{
    ui->setupUi(this);
}

UserSetting::~UserSetting()
{
    delete ui;
}


void UserSetting::CopyPtrToDb(DbConnection *pDb)
{
    // Copy constructor - coping pointer to database driver object
    db = pDb;
}


void UserSetting::on_lineEdit_Username_textChanged(const QString &arg1)
{
    // Setting buttons enabled
    if (ui->lineEdit_Username->text() != "")
    {
        ui->pushButton_Add->setEnabled(true);
        ui->pushButton_Delete->setEnabled(true);
    }
    else
    {
        ui->pushButton_Add->setEnabled(false);
        ui->pushButton_Delete->setEnabled(false);
    }
}

void UserSetting::on_pushButton_Add_clicked()
{
    // After ADD button click
    QString username, address,info;
    username = ui->lineEdit_Username->text();
    address = ui->lineEdit_Address->text();
    info = ui->lineEdit_Info->text();

    QString query = "EXEC AddUser @username = '" + username + "', @address = '" + address + "', @info = '" + info + "';";
    db->ExecQuery(query);
    ui->label_status->setText("The user has been added");
}

void UserSetting::on_pushButton_Delete_clicked()
{
    // After Delete button click
    QString username;
    username = ui->lineEdit_Username->text();

    QString query = "EXEC DeleteUser @username = '" + username + "';";
    db->ExecQuery(query);
    ui->label_status->setText("The user has been deleted");

}
