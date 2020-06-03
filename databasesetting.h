#ifndef DATABASESETTING_H
#define DATABASESETTING_H

#include <QDialog>
#include <QPixmap>
#include <dbconnection.h>
#include <fstream>
#include "connectioncheckthread.h"

extern DbConnection db;

namespace Ui {
class DatabaseSetting;
}

class DatabaseSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseSetting(QWidget *parent = nullptr);
    ~DatabaseSetting();

    void CopyPtrToDb(DbConnection *pDb);
    void SaveConnectionString();
    friend class ConnectionCheckThread;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::DatabaseSetting *ui;
    DbConnection *db;

};

#endif // DATABASESETTING_H
