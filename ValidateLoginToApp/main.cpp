#include "dialog.h"
#include "mainwindow.h"
#include "simplecrypt.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString FreeTrialStartDate ;

    MainWindow w;

    Dialog dlg;
    int dialogCode ;
    // show modal window event loop and wait for button clicks

    while ((dialogCode = dlg.exec()))
    {
        // act on dialog return code
        if(dialogCode == QDialog::Accepted)
        {
            //Set The Encryption And Decryption Key
            SimpleCrypt processSimpleCrypt(89473829);

            //Encrypt
            // processSimpleCrypt.encryptToString("string");

            QFile file("pass.txt");
            if(!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(nullptr, "Error", file.errorString());
            }

            QTextStream in(&file);
            QStringList fields;
            while(!in.atEnd()) {
                QString line = in.readLine();
                fields = line.split(",");
            }
            file.close();
            //Decrypt
            QString decryptName = processSimpleCrypt.decryptToString(fields.at(0));
            QString decryptPass = processSimpleCrypt.decryptToString(fields.at(1));


            if(decryptName == dlg.getUserID() && decryptPass ==dlg.getUserPIN())
            {
                w.show();
                break;
            }
            else
            {
                QMessageBox::critical(nullptr, "Error", "Username and Password did not match");
            }
        }
        else if(dialogCode == QDialog::Rejected)
        {
            QMessageBox::warning(nullptr, "Warning", "Dialog Closed");
        }
    }


    return a.exec();
}
