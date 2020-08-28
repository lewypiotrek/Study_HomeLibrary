#include "homelibrary.h"
#include "ui_homelibrary.h"
#include "databasesetting.h"
#include "usersetting.h"

HomeLibrary::HomeLibrary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeLibrary)
{
    ui->setupUi(this);

    // Setting pointer to database driver object
    pDb = &db;

    // Creating Models for tables views
    bookTableModel = new QSqlTableModel;
    usersTableModel = new QSqlTableModel;
    bookLendingTableModel = new QSqlTableModel;
    notesTableModel = new QSqlTableModel;
    historyTableModel = new QSqlTableModel;

    ui->tableViewBooks->setModel(bookTableModel);
    ui->tableViewUsers->setModel(usersTableModel);
    ui->tableViewBookLending->setModel(bookLendingTableModel);
    ui->listView_Note->setModel(notesTableModel);
    ui->tableView_history->setModel(historyTableModel);


    // Set exapanding mode for last row in below tablesViews
    ui->tableViewBookLending->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewBooks->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewUsers->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_history->horizontalHeader()->setStretchLastSection(true);

    // Set select mode for listView widgets
    ui->listView_Note->setSelectionMode(QAbstractItemView::SingleSelection);
}

HomeLibrary::~HomeLibrary()
{
    delete bookTableModel;
    delete usersTableModel;
    delete bookLendingTableModel;
    delete notesTableModel;
    delete historyTableModel;
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

        // Refreshing models for all views
        usersTableModel->setQuery("EXEC ShowUsers @Name = '', @Address = '', @Info = '', @top = 200");
        bookTableModel->setQuery("EXEC ShowBooks @Barcode = '', @Title = '', @Author = '', @Publisher = '', @Top = '"+ QString::number(top) + "';");
        bookLendingTableModel->setQuery("EXEC ShowBooks @Barcode = '', @Title = '', @Author = '', @Publisher = '', @Top = '"+ QString::number(top) + "';");
        notesTableModel->setQuery("SELECT Title FROM Notes");
        historyTableModel->setQuery("EXEC ShowBorrowedBooks");
    }
    else
    {
        ui->status->setText("STATUS: DISCONNECTED");
    }
}

void HomeLibrary::on_Button_Search_clicked()
{
    // Home library - Books tab
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
    }
    catch (...)
    {
        qDebug() << "SQL Query error: " << db.lastError();
    }
}

void HomeLibrary::on_pushButton_LendingSearch_clicked()
{
    // Action relate to serach button on lending tab.
    // Executing right procedure and updating view

// If User field is empty serach book else search user
    if(ui->lineEdit_UserName->text() == "")
    {
        QString barcode, title, author;
        barcode = ui->lineEdit_Barcode_2->text();
        title = ui->lineEdit_Title_2->text();
        author = ui->lineEdit_Author_2->text();
        QString query = "EXEC ShowBooks @Barcode = '" + barcode + "', @Title = '" + title + "', @Author = '" + author + "', @Publisher = '""', @Top = '100'";
        bookLendingTableModel->setQuery(query);
    }
    else
    {
        QString name = ui->lineEdit_UserName->text();
        QString query = "EXEC ShowUsers @Name = '" + name + "', @Address = '', @Info = '', @top = 100";
        qDebug() << db.lastError();
        qDebug() << query;
        usersTableModel->setQuery(query);
    }
}

void HomeLibrary::on_pushButton_SaveNote_clicked()
{
    //NOTE TAB - Adding note to the database, if note is empty skip action.
    if ((!ui->textEdit_Note->toPlainText().isEmpty()) && (!ui->lineEdit_NoteTitle->text().isEmpty()))
    {
        QString note, title;
        note = ui->textEdit_Note->toPlainText();
        title = ui->lineEdit_NoteTitle->text();
        QString query = "EXEC dbo.AddNote @Title = '" + title + "', @Note ='" + note + "'";
        db.ExecQuery(query);
    }
    // Update views
    RefreshData();

}

void HomeLibrary::on_pushButton_DeleteNote_clicked()
{
    //NOTE TAB - Deleting selected in listView_Notes row
    QModelIndex index = ui->listView_Note->currentIndex();
    QString title = index.data(Qt::DisplayRole).toString();

    QString query = "EXEC DeleteNote @Title='" + title + "';";
    db.ExecQuery(query);

    // Update view
    RefreshData();
}

void HomeLibrary::on_listView_Note_clicked(const QModelIndex &index)
{
    //NOTE TAB - Show selected note in editable views
    QString title = index.data(Qt::DisplayRole).toString();
    QSqlQuery query;
    query.exec("SELECT Note FROM Notes WHERE title ='" + title + "';");
    query.next();   // we need use next because by default internal query pointer is located before first result
    QString note = query.value(0).toString();
    ui->textEdit_Note->setText(note);
    ui->lineEdit_NoteTitle->setText(title);
}

void HomeLibrary::on_tableViewBookLending_clicked(const QModelIndex &index)
{
    //LENDING TAB - selecting book to lending

    QString barcode = index.data(Qt::DisplayRole).toString();
    ui->lineEdit_LendinBarcode->setText(barcode);
}

void HomeLibrary::on_tableViewUsers_clicked(const QModelIndex &index)
{
   //LENDING TAB - selecting user to lending

    QString user = index.data(Qt::DisplayRole).toString();
    ui->lineEdit_LendingUser->setText(user);
}

void HomeLibrary::on_Button_Update_clicked()
{
    //LENDING TAB - Adding book to the database, from has to contain required field barcode,title,author

    try
    {
        QString barcode, title, author, year, publisher;
        barcode = ui->lineEdit_Barcode->text();
        title = ui->lineEdit_Title->text();
        author = ui->lineEdit_Author->text();
        publisher = ui->lineEdit_Year->text();
        year = ui->lineEdit_Year->text();
        QString query = "EXEC dbo.AddBook @Barcode = '" + barcode + "', @Title = '" + title + "', @author='" + author + "', @publisher='" + publisher + "', @publicationDate='" + year + "';";
        db.ExecQuery(query);
    }
    catch (...)
    {
       qDebug() << db.lastError();
    }
    // Update views
    RefreshData();
}

void HomeLibrary::UnlockBookAdding()
{
    // BOOK TAB - If all 3 required field are filled, then unlock add button

    if(ui->lineEdit_Barcode->text() != "" && ui->lineEdit_Title->text() !="" && ui->lineEdit_Author->text() != "")
        ui->Button_Update->setEnabled(true);
    else
        ui->Button_Update->setEnabled(false);
}

void HomeLibrary::UnlockBookDeleting()
{
    // BOOK TAB - If all 3 required field are filled, then unlock 'Delete' button

    if(ui->lineEdit_Barcode->text() != "")
        ui->Button_Delete->setEnabled(true);
    else
        ui->Button_Delete->setEnabled(false);
}

//related to unlocking buttons
void HomeLibrary::on_lineEdit_Barcode_textChanged(const QString &arg1)
{
    UnlockBookAdding();
    UnlockBookDeleting();
}

//related to unlocking buttons
void HomeLibrary::on_lineEdit_Author_textChanged(const QString &arg1)
{
   UnlockBookAdding();
}

//related to unlocking buttons
void HomeLibrary::on_lineEdit_Title_textChanged(const QString &arg1)
{
    UnlockBookAdding();
}

void HomeLibrary::UnlockLendingButton()
{
    // LENDING TAB - Unlock button 'Lending a book' if all required fields are filled.

    if(ui->lineEdit_LendinBarcode->text() != "" && ui->lineEdit_LendingUser->text() != "")
        ui->pushButton_Lend->setEnabled(true);
    else
        ui->pushButton_Lend->setEnabled(false);
}

void HomeLibrary::on_lineEdit_LendinBarcode_textChanged(const QString &arg1)
{
    //  Related to unlocking 'Lending a book' button
    UnlockLendingButton();
}

void HomeLibrary::on_lineEdit_LendingUser_textChanged(const QString &arg1)
{
    //  Related to unlocking 'Lending a book' button
    UnlockLendingButton();
}

void HomeLibrary::on_Button_Delete_clicked()
{
    // BOOKS TAB - action after click Delete button - executing stored procedure DeleteBook
    // Barcode field has to be filled to unlock this option. Deleting depends on unique barcode in database

    try
    {
        QString barcode;
        barcode = ui->lineEdit_Barcode->text();
        QString query = "EXEC dbo.DeleteBook @Barcode = '" + barcode + "';";
        db.ExecQuery(query);
    }
    catch (...)
    {
       qDebug() << db.lastError();
    }

    // Update views
    RefreshData();
}

void HomeLibrary::on_pushButton_Lend_clicked()
{
    try
    {
        QString barcode, user;
        barcode = ui->lineEdit_LendinBarcode->text();
        user = ui->lineEdit_LendingUser->text();
        QString query = "EXEC dbo.LendBook @Barcode = '" + barcode + "', @user = '" + user + "';";
        db.ExecQuery(query);
    }
    catch (...)
    {
       qDebug() << db.lastError();
    }

    // Update views
    RefreshData();
}

void HomeLibrary::on_tableView_history_clicked(const QModelIndex &index)
{
    // HISTORY TAB - selecting book's Barcode to check
    QString barcode = index.data(Qt::DisplayRole).toString();
    ui->lineEdit_HistoryBarcode->setText(barcode);
}

void HomeLibrary::on_pushButton_HistoryComplete_clicked()
{
    // HISTORY TAB - Action after click button "Mark as Completed". Executing the right procedure to complete book lending.
    try
    {
        QString barcode;
        barcode = ui->lineEdit_HistoryBarcode->text();

        QString query = "EXEC dbo.CompleteLending @Barcode = '" + barcode + "';";
        db.ExecQuery(query);
    }
    catch (...)
    {
       qDebug() << db.lastError();
    }

    // Update views
    RefreshData();
}

void HomeLibrary::on_pushButton_HistoryCheck_clicked()
{
    // HISTORY TAB - Action after click button "Mark as Completed". Executing the right procedure to complete book lending.
    try
    {
        QString barcode;
        barcode = ui->lineEdit_HistoryBarcode->text();

        QString query = "EXEC dbo.ShowHistoryByFilter @Barcode = '" + barcode + "';";
        historyTableModel->setQuery(query);
    }
    catch (...)
    {
       qDebug() << db.lastError();
    }
}

void HomeLibrary::on_actionAdd_User_triggered()
{
    // ADD USER - open window user settings after click in option

    UserSetting userWindow;
    userWindow.CopyPtrToDb(&db);
    userWindow.setModal(true);
    userWindow.exec();
}
