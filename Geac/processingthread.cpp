#include "processingthread.h"
#include <iostream>

ProcessingThread::ProcessingThread(QObject *parent) : QThread(parent)
{
    progress = 0;
    totalNumberOfFiles = 0;
    finished = false;
}

ProcessingThread::~ProcessingThread()
{
    mutex.lock();
    finished = false;
    mutex.unlock();

    wait();
}

void ProcessingThread::setupThread(QList<CheckableFile *> &list)
{
    // setup Thread
    totalNumberOfFiles = fileList.count();
    fileList.append(list);
    finished = false;
    // Start processing the files
    start();
}

void ProcessingThread::addToThread(QList<CheckableFile *> &list)
{
    mutex.lock();
    totalNumberOfFiles += list.count();
    mutex.unlock();
    fileList.append(list);
    // Check if run or start is required
}

void ProcessingThread::addToThread(CheckableFile *file)
{
    emit logEvent(tr("Added file %1 to processing Thread").arg(file->fileName()));
    mutex.lock();
    totalNumberOfFiles += 1;
    mutex.unlock();
    fileList.append(file);
    emit logEvent(tr("%1 files in processing thread").arg(totalNumberOfFiles));
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
    emit logEvent("Thread Started");

    while (!fileList.isEmpty())
    {

        // Perform conversion of first file in List
        // - 1 - Setup ESI Extractor
        CheckableFile file(this);
        file.setFileName(fileList.takeFirst()->fileName());
        esiExtractor.setInputFile(file);
        //  - 2 - Set Parameters in Esi Extractor
//        esiExtractor.setOutputFolder(folder); // depends on sameFolder//dedicatedFolder
//        esiExtractor.setRequiredFields(reqThermochemistry, reqHarmonicFrequencies, reqStandardCoordinates, reqHartreeFock);
//        esiExtractor.setExtension(extension);
        // - 3 - Create ESI
        // esiExtractor.createEsi();
        progress += 1;
        // Emit Signals to update display
        emit logEvent(tr("File %1 successfully converted").arg(file.fileName())); // To move to Esi Extractor
        emit fileProcessed(100 * progress/totalNumberOfFiles);
//        emit fileNumber processed --> to update the view
        // Test if the thread has been aborted
        if (finished)
        {
            return;
        }
        msleep(10);
    }
//    emit processing done (triggers hiding of progress bar and release of button)
}

void ProcessingThread::stop()
{
    // Executed when stopping the thread is required
    finished = true;
}
