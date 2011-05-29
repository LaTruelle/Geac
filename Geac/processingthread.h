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

};

#endif // PROCESSINGTHREAD_H
