#ifndef USERSETTING_H
#define USERSETTING_H

#include <QDialog>
#include <dbconnection.h>

namespace Ui {
class UserSetting;
}

class UserSetting : public QDialog
{
    Q_OBJECT

public:
    void CopyPtrToDb(DbConnection *pDb);

public:
    explicit UserSetting(QWidget *parent = nullptr);
    ~UserSetting();

private slots:
    void on_lineEdit_Username_textChanged(const QString &arg1);

    void on_pushButton_Add_clicked();

    void on_pushButton_Delete_clicked();

private:
    Ui::UserSetting *ui;
    DbConnection *db;
};

#endif // USERSETTING_H
