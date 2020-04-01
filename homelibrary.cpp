#include "homelibrary.h"
#include "ui_homelibrary.h"
#include "databasesetting.h"

HomeLibrary::HomeLibrary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeLibrary)
{
    ui->setupUi(this);
    pDb = &db;
}

HomeLibrary::~HomeLibrary()
{
    delete ui;
}

void HomeLibrary::on_actionDatabase_Settings_triggered()
{
    DatabaseSetting SettingWindow;
    SettingWindow.CopyPtrToDb(pDb);
    SettingWindow.setModal(true);
    SettingWindow.exec();

}
