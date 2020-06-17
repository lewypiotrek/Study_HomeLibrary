#ifndef HOMELIBRARY_H
#define HOMELIBRARY_H

#include <QMainWindow>
#include <dbconnection.h>
#include "filedriver.h"
#include "connectioncheckthread.h"


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
    ConnectionCheckThread StatusThread;

private slots:
    void on_actionDatabase_Settings_triggered();
    void on_actionAbout_triggered();
    void on_actionCheck_connection_triggered();
    void on_actionRefresh_Data_triggered();
    void on_comboBox_currentIndexChanged(int index);
};

#endif // HOMELIBRARY_H
