#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>

#include <QThread>
#include <QDebug>
#include <QTimer>

#include <C:/Users/rathanshettigar/Documents/QThreadLib/Thread.h>


class mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    mainwindow();

private slots:
    void getValues();
private:
    QPushButton *button;
    QThread* thread1;
    QThread* thread2;
    QThread* thread3;

    WorkerThread* worker1;
    WorkerThread* worker2;
    WorkerThread* worker3;

    QTimer *timer;
};

#endif // MAINWINDOW_H
