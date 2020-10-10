#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    userID = "";
    userPIN = "";
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    userID = ui->lineEdit_UserID->text();
    userPIN = ui->lineEdit_UserPIN->text();
}

QString Dialog::getUserPIN() const
{
    return userPIN;
}

QString Dialog::getUserID() const
{
    return userID;
}

