#ifndef QDBINTERFACE_H
#define QDBINTERFACE_H

#include <QObject>
#include <QtGui>
#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

class QDbInterface : public QObject
{
    Q_OBJECT
public:
    explicit QDbInterface(QObject *parent = 0);
    bool Connect(QString dbName, QString hostName, QString user, QString password, QString driver = "QMYSQL");
    void Close();
    bool IsOpen();
    bool InsertImageCoordinates(QString imageName,QVector<QPoint> pointList);

public:
    QSqlDatabase db;

};

#endif // QDBINTERFACE_H
