#include <QObject>

#if defined MAKE_THREAD_LIB
#define THREAD_LIB_EXPORT Q_DECL_EXPORT
#else
#define THREAD_LIB_EXPORT Q_DECL_IMPORT
#endif

class THREAD_LIB_EXPORT WorkerThread : public QObject
{
    Q_OBJECT
public:
    WorkerThread();
    ~WorkerThread();

    void stopWorkerThread();
    int getRandomValue() const;

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
private:
    int randomValue;
};
