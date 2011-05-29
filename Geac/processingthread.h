#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include <QThread>

class ProcessingThread : public QThread
{
    Q_OBJECT

public:
    ProcessingThread();

    void stop();

protected:
    void run();

private:
    volatile bool finished;
};

#endif // PROCESSINGTHREAD_H
