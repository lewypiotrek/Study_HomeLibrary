#ifndef HOMELIBRARY_H
#define HOMELIBRARY_H

#include <QMainWindow>
#include <dbconnection.h>
#include "filedriver.h"

namespace Ui {
class HomeLibrary;
}

class HomeLibrary : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeLibrary(QWidget *parent = nullptr);
    ~HomeLibrary();

private:
    Ui::HomeLibrary *ui;
    DbConnection db,*pDb;
    QSqlQueryModel *bookTableModel;
    QSqlQueryModel *usersTableModel;
    QSqlQueryModel *bookLendingTableModel;
    QSqlQueryModel *notesTableModel;


public:
    void RefreshData();

private slots:
    void on_actionDatabase_Settings_triggered();
    void on_actionAbout_triggered();
    void on_actionCheck_connection_triggered();
    void on_actionRefresh_Data_triggered();
    void on_comboBox_currentIndexChanged(int index);
    void on_Button_Search_clicked();
    void on_pushButton_LendingSearch_clicked();
    void on_pushButton_SaveNote_clicked();
    void on_pushButton_DeleteNote_clicked();

    void on_listView_Note_clicked(const QModelIndex &index);
};

#endif // HOMELIBRARY_H
