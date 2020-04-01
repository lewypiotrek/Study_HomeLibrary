#ifndef DATABASESETTING_H
#define DATABASESETTING_H

#include <QDialog>
#include <QPixmap>
#include <dbconnection.h>

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


private slots:
    void on_pushButton_clicked();

private:
    Ui::DatabaseSetting *ui;
    DbConnection *db;

};

#endif // DATABASESETTING_H
