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
        // Perform conversion of first file in List
        // - 1 - Setup ESI Extractor
        QFile file(fileList.takeFirst());
        esiExtractor.setInputFile(file);
        //  - 2 - Set Parameters in Esi Extractor
//        esiExtractor.setOutputFolder(folder); // depends on sameFolder//dedicatedFolder
//        esiExtractor.setRequiredFields(reqThermochemistry, reqHarmonicFrequencies, reqStandardCoordinates, reqHartreeFock);
//        esiExtractor.setExtension(extension);
        // - 3 - Create ESI
        esiExtractor.createEsi();
        // Emit Signals to update display
        emit logEvent(tr("File %1 successfully converted").arg(file.fileName())); // To move to Esi Extractor
        emit fileProcessed(100 * progress/totalNumberOfFiles);
//        emit fileNumber processed --> to update the view
        // Test if the thread has been aborted
        if (finished)
        {
            return;
//            emit processing done (triggers hiding of progrees bar and release of button)
        }
        msleep(10);
    }
}

void ProcessingThread::stop()
{
    // Executed when stopping the thread is required
    finished = true;
}
