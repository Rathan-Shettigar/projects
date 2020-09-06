#include "mainwindow.h"

mainwindow::mainwindow()
{
    thread1 = new QThread;
    worker1 = new WorkerThread();
    worker1->moveToThread(thread1);
    connect(thread1, SIGNAL (started()), worker1, SLOT (process()));
    connect(worker1, SIGNAL (finished()), thread1, SLOT (quit()));
    connect(worker1, SIGNAL (finished()), worker1, SLOT (deleteLater()));
    connect(thread1, SIGNAL (finished()), thread1, SLOT (deleteLater()));
    thread1->start();
    qDebug() << "Thread 1 Value" <<worker1->getRandomValue();


    thread2 = new QThread;
    worker2 = new WorkerThread();
    worker2->moveToThread(thread2);
    connect(thread2, SIGNAL (started()), worker2, SLOT (process()));
    connect(worker2, SIGNAL (finished()), thread2, SLOT (quit()));
    connect(worker2, SIGNAL (finished()), worker2, SLOT (deleteLater()));
    connect(thread2, SIGNAL (finished()), thread2, SLOT (deleteLater()));
    thread2->start();
    qDebug() << "Thread 2 Value" <<worker2->getRandomValue();

    thread3 = new QThread;
    worker3 = new WorkerThread();
    worker3->moveToThread(thread3);
    connect(thread3, SIGNAL (started()), worker3, SLOT (process()));
    connect(worker3, SIGNAL (finished()), thread3, SLOT (quit()));
    connect(worker3, SIGNAL (finished()), worker3, SLOT (deleteLater()));
    connect(thread3, SIGNAL (finished()), thread3, SLOT (deleteLater()));
    thread3->start();
    qDebug() << "Thread 2 Value" <<worker3->getRandomValue();


    button = new  QPushButton(this) ;
    connect(button, &QPushButton::clicked, this, &mainwindow::getValues);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mainwindow::getValues);
    timer->start(1000);

}


void mainwindow::getValues()
{
    qDebug() << "Thread 1 Value" <<worker1->getRandomValue();
    qDebug() << "Thread 2 Value" <<worker2->getRandomValue();
    qDebug() << "Thread 3 Value" <<worker3->getRandomValue();

}
