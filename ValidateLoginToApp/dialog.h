#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QString getUserID() const;
    QString getUserPIN() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    QString userID;
    QString userPIN;

};

#endif // DIALOG_H
