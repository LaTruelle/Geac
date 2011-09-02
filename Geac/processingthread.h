#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include <QThread>
#include <QFile>
#include <QList>
#include <QMutex>
#include <esiextractor.h>
#include "checkablefile.h"

class ProcessingThread : public QThread
{
    Q_OBJECT

public:
    ProcessingThread(QObject *parent = 0);
    ~ProcessingThread();

    void setupThread(QList<CheckableFile *> &list);
    void addToThread(QList<CheckableFile *> &list);
    void addToThread(CheckableFile *file);
    void clearThread();
    void stop();

signals:
    void fileProcessed(int integer);
    void logEvent(QString string);

public slots:
    void stopProcessing();

protected:
    void run();

private:
    // Thread Related declarations
    QMutex mutex;
    bool finished;
    // ESI Extraction related declarations
    int totalNumberOfFiles;
    int progress;
    EsiExtractor esiExtractor;
    QList<CheckableFile *> fileList;
};

#endif // PROCESSINGTHREAD_H
