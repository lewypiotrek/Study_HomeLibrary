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
    QSqlQueryModel *historyTableModel;

    void UnlockBookAdding();
    void UnlockBookDeleting();
    void UnlockLendingButton();


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
    void on_tableViewBookLending_clicked(const QModelIndex &index);
    void on_tableViewUsers_clicked(const QModelIndex &index);
    void on_Button_Update_clicked();
    void on_lineEdit_Barcode_textChanged(const QString &arg1);
    void on_lineEdit_Author_textChanged(const QString &arg1);
    void on_lineEdit_Title_textChanged(const QString &arg1);
    void on_Button_Delete_clicked();
    void on_lineEdit_LendinBarcode_textChanged(const QString &arg1);
    void on_lineEdit_LendingUser_textChanged(const QString &arg1);
    void on_pushButton_Lend_clicked();
    void on_tableView_history_clicked(const QModelIndex &index);
    void on_pushButton_HistoryComplete_clicked();
    void on_pushButton_HistoryCheck_clicked();
};

#endif // HOMELIBRARY_H
