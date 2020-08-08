#include "homelibrary.h"
#include "ui_homelibrary.h"
#include "databasesetting.h"

HomeLibrary::HomeLibrary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeLibrary)
{
    ui->setupUi(this);

    // Setting pointer to database driver sobject
    pDb = &db;
    // Creating Modes for tables views
    bookTableModel = new QSqlTableModel;
    usersTableModel = new QSqlTableModel;
    bookLendingTableModel = new QSqlTableModel;
}

HomeLibrary::~HomeLibrary()
{
    delete bookTableModel;
    delete usersTableModel;
    delete bookLendingTableModel;
    delete ui; 
}

void HomeLibrary::on_actionDatabase_Settings_triggered()
{
    DatabaseSetting SettingWindow;
    SettingWindow.CopyPtrToDb(pDb);
    SettingWindow.setModal(true);
    SettingWindow.exec();
}

void HomeLibrary::on_actionAbout_triggered()
{
    QMessageBox About;
    About.setIcon(QMessageBox::Information);
    About.setText("Home Library \tVersion:1.0 \n\nCopyright ® All rights reserved Piotr Lewandowski");
    About.exec();
}

void HomeLibrary::on_actionCheck_connection_triggered()
{
    // If you're connected to the database you'll receive message.
    // Otherwise connection string will be readed from Config.txt and the connection will be attempted

    QMessageBox msg;

    if(db.GetStaus())
    {
        msg.setIcon(QMessageBox::Information);
        msg.setText("You are connected to the database: " + db.GetDatabaseName());
        msg.exec();
    }
    else
    {
        FileDriver File;
        File.ReadSettings();
        db.ConnectToDb(File.GetDatabaseName(),File.GetServerName(),File.GetUser(),File.GetUserPassword());
    }
    // RefreshData will fill all empty fields
    RefreshData();
}


void HomeLibrary::on_actionRefresh_Data_triggered()
{
    RefreshData();
}

void HomeLibrary::on_comboBox_currentIndexChanged(int index)
{
    if(index != 6)
        index = (ui->comboBox->currentIndex() +1) * 10;
    else
        index = 1000;

    bookTableModel->setQuery("EXEC ShowBooks @Barcode = '', @Title = '', @Author = '', @Publisher = '', @Top = '"+ QString::number(index) + "';");
}


void HomeLibrary::RefreshData()
{
    if(db.GetStaus())
    {
        ui->status->setText("STATUS: CONNECTED");

        int top =ui->comboBox->currentIndex();
        if(top != 6)
            top = (ui->comboBox->currentIndex() +1) * 10;
        else
            top = 1000;

        // Setting query to specific query to model
        usersTableModel->setQuery("EXEC ShowBooks @Barcode = '', @Title = '', @Author = '', @Publisher = '', @Top = 50;");
        bookTableModel->setQuery("EXEC ShowBooks @Barcode = '', @Title = '', @Author = '', @Publisher = '', @Top = '"+ QString::number(top) + "';");

        // Putting model into View
        ui->tableViewBooks->setModel(bookTableModel);
        ui->tableViewUsers->setModel(usersTableModel);
        ui->tableViewBookLending->setModel(bookTableModel);

    }
    else
    {
        ui->status->setText("STATUS: DISCONNECTED");
    }
}

void HomeLibrary::on_Button_Search_clicked()
{
    // First we're getting information about row on page, then serach filters
    QString barcode, title, publisher, year, author;

    int top = ui->comboBox->currentIndex();
    if(top != 6)
        top = (ui->comboBox->currentIndex() +1) * 10;
    else
        top = 1000;

    barcode = ui->lineEdit_Barcode->text();
    title = ui->lineEdit_Title->text();
    publisher = ui->lineEdit_Publisher->text();
    year = ui->lineEdit_Year->text();
    author = ui->lineEdit_Author->text();

    // Exec procedure that will show specific books
    try
    {
        // setting query and put model into view
        QString query = "EXEC ShowBooks @Barcode = '" + barcode + "', @Title = '" + title + "', @Author = '" + author + "', @Publisher = '" + publisher + "', @Top = '"+ QString::number(top) + "'"; 
        bookTableModel->setQuery(query);
        ui->tableViewBooks->setModel(bookTableModel);
    }
    catch (...)
    {
        qDebug() << "SQL Query error: " << db.lastError();
    }
}
