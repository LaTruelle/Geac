#include "processingthread.h"

ProcessingThread::ProcessingThread() : QThread()
{
    finished = false;
}

void ProcessingThread::run()
{
    // Executed at the beginning of the thread
    while (!finished)
    {
        // Perform conversions
    }
}

void ProcessingThread::stop()
{
    // Executed when stopping the thread is required
    finished = true;
}
