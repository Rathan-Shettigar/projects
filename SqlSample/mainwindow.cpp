#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // -- DATABASE INIT --
    DatabaseConnect();
    DatabaseInit();
}

MainWindow::~MainWindow()
{
    on_pushButton_Clear_clicked();
    delete ui;
}

void MainWindow::DatabaseConnect()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName("memory.txt");

        model = new QSqlTableModel;
        model->setTable("people");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("id"));
        model->setHeaderData(1, Qt::Horizontal, tr("name"));
        ui->tableView->setModel(model);
        if(!db.open())
        {
            ui->statusBar->showMessage("MainWindow::DatabaseConnect - ERROR: " + db.lastError().text());
        }
    }
    else
        ui->statusBar->showMessage("MainWindow::DatabaseConnect - ERROR: no driver " + DRIVER + " available");
}

void MainWindow::DatabaseInit()
{
    QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");

    if(!query.isActive())
        qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();
}

void MainWindow::on_pushButton_Insert_clicked()
{
    QString peopleName = ui->lineEdit_InsertName->text();
    QString peopleID = ui->lineEdit_InsertID->text();
    QSqlQuery query;

    query.prepare("INSERT INTO people (id, name)"
                  "VALUES (:id, :name)");
    query.bindValue(":id", peopleID);
    query.bindValue(":name",peopleName);

    if(!query.exec())
    {
        ui->statusBar->showMessage("MainWindow::DatabasePopulate - ERROR: " + query.lastError().text());
    }
    else {
        ui->statusBar->showMessage("");
    }
    model->select();
}

void MainWindow::on_pushButton_Clear_clicked()
{
    QSqlQuery query;

    query.prepare("DELETE FROM people");

    if(!query.exec())
    {
        ui->statusBar->showMessage("MainWindow::DatabasePopulate - ERROR: " + query.lastError().text());
    }
    else {
        ui->statusBar->showMessage("");
    }
    model->select();
}

void MainWindow::on_pushButton_Delete_clicked()
{
    QString peopleName = ui->lineEdit_DeleteName->text();
    QString peopleID = ui->lineEdit_DeleteID->text();
    QSqlQuery query;

    if(ui->checkBox_DeleteIDSelect->isChecked() && ui->checkBox_DeleteNameSelect->isChecked())
    {
        query.prepare("DELETE FROM people WHERE id =:id and name =:name") ;
        query.bindValue(":id", peopleID);
        query.bindValue(":name", peopleName);
    }
    else if(ui->checkBox_DeleteIDSelect->isChecked())
    {
        query.prepare("DELETE FROM people WHERE id ==" + peopleID) ;
    }
    else if (ui->checkBox_DeleteNameSelect->isChecked())
    {
        query.prepare("DELETE FROM people WHERE name ==" + peopleName) ;
    }

    if(!query.exec())
    {
        ui->statusBar->showMessage("MainWindow::DatabasePopulate - ERROR: " + query.lastError().text());
    }
    else {
        ui->statusBar->showMessage("");
    }
    model->select();
}

void MainWindow::on_pushButton_Update_clicked()
{
    QString peopleName = ui->lineEdit_UpdateName->text();
    QString peopleID = ui->lineEdit_UpdateID->text();
    QSqlQuery query;

    query.prepare("UPDATE people SET name = :name WHERE id =:id") ;
    query.bindValue(":name", peopleName);
    query.bindValue(":id", peopleID);

    if(!query.exec())
    {
        ui->statusBar->showMessage("MainWindow::Update_clicked - ERROR: " + query.lastError().text());
    }
    else {
        ui->statusBar->showMessage("");
    }
    model->select();
}
