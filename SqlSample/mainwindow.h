#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Insert_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Update_clicked();

private:
    Ui::MainWindow *ui;

    void DatabaseConnect();
    void DatabaseInit();

    QSqlDatabase db;

    QSqlTableModel *model;

};

#endif // MAINWINDOW_H
