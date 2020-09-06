#include "Thread.h"
#include <QDebug>


WorkerThread::WorkerThread()
{

}

WorkerThread::~WorkerThread()
{

}

void WorkerThread::process()
{
    while (1)
    {
        randomValue = rand() % ((100 - 1) + 1) + 1;
    }
}

int WorkerThread::getRandomValue() const
{
    return randomValue;
}

void WorkerThread::stopWorkerThread()
{
    emit finished();
}

