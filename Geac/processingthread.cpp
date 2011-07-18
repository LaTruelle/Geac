#include "processingthread.h"

ProcessingThread::ProcessingThread(QObject *parent) : QThread(parent)
{
    finished = false;
}

ProcessingThread::~ProcessingThread()
{
    mutex.lock();
    finished = false;
    mutex.unlock();

    wait();
}

void ProcessingThread::setupThread(QList<QFile *> &list)
{
    // setup Thread
    totalNumberOfFiles = fileList.count();
    fileList.append(list);
    finished = false;
    // Start processing the files
    start();
}

void ProcessingThread::addToThread(QList<QFile *> &list)
{
    mutex.lock();
    totalNumberOfFiles += list.count();
    mutex.unlock();
    fileList.append(list);
    // Check if run or start is required
}

void ProcessingThread::addToThread(QFile &file)
{
    mutex.lock();
    totalNumberOfFiles += 1;
    mutex.unlock();
    fileList.append(new QFile(&file));
    // Check if run or start is required
}

void ProcessingThread::stopProcessing()
{
    // Stop Thread
    mutex.lock();
    finished = true;
    mutex.unlock();
}

void ProcessingThread::clearThread()
{
    // Clear Data in Thread
    fileList.clear();
}

void ProcessingThread::run()
{
    while (!fileList.isEmpty())
    {
        // Perform conversion of file currentFile

        // Emit Signals to update display
        emit logEvent(tr("File successfully converted")); // To move to Esi Extractor
        emit fileProcessed(100 * progress/totalNumberOfFiles);
        // Test if the thread has been aborted
        if (finished)
            return;
        msleep(10);
    }
}

void ProcessingThread::stop()
{
    // Executed when stopping the thread is required
    finished = true;
}
