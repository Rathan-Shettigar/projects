#include "qdbinterface.h"
#include <QDebug>
#include <qmessagebox.h>

///
/// \brief QDbInterface::QDbInterface
/// \param parent
///
QDbInterface::QDbInterface(QObject *parent) :
    QObject(parent)
{
}

//! Connets to DB . returns false if failed.
bool QDbInterface::Connect(QString dbName, QString hostName, QString user, QString password, QString driver)
{
    db = QSqlDatabase::addDatabase(driver);
    db.lastError();
    db.setHostName(hostName);
    //db.setPort(3306); // Commented to take default port.
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);
    bool ok = db.open();

    if(ok)
    {
        return true;
    }
    else
    {
        QSqlError error =  db.lastError();
        qDebug() << error.text();
        return false;
    }
}

//! Closes the DB.
void QDbInterface::Close()
{
    db.close();
}

//! returns bool if DB is open or not.
bool QDbInterface::IsOpen()
{
    return db.isOpen();
}

//! Insert coordinates to DB.
//('%1','%2')")
bool QDbInterface::InsertImageCoordinates(QString imageName,QVector<QPoint> pointList)
{
    if(pointList.count()>0)
    {
        int count=0;
        QString query = "INSERT INTO CoordinatesTable (Dtime,ImageName,co1,co2,co3,co4,co5,co6,co7,co8,co9,co10)VALUES (CURRENT_TIMESTAMP,'";

        query+=imageName+"',";
        for(count=0;count<pointList.count();count++)
        {
            query+="'"+QString::number(pointList.at(count).x())+","+QString::number(pointList.at(count).y())+"'," ;
        }

        for(int i=count;i<=9;i++)
        {
            if(i==9)
                query+="'0'";
            else
                query+="'0',";
        }

        query+=")";
        qDebug()<<query;

        QSqlQuery result=db.exec(query);//excute
        db.commit();//commit
        if(result.lastError().text()==" ")// Checking for error
            return true;
        else
            return false;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("   No coordinates to save  ");
        msgBox.exec();
    }
}
