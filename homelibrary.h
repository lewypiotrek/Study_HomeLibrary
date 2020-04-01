#ifndef HOMELIBRARY_H
#define HOMELIBRARY_H

#include <QMainWindow>
#include <dbconnection.h>

namespace Ui {
class HomeLibrary;
}

class HomeLibrary : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeLibrary(QWidget *parent = nullptr);
    ~HomeLibrary();

private slots:
    void on_actionDatabase_Settings_triggered();

private:
    Ui::HomeLibrary *ui;
    DbConnection db,*pDb;
};

#endif // HOMELIBRARY_H
