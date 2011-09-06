#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QFile>
#include <QList>
#include <esiextractor.h>
#include "checkablefile.h"

class FileProcessor
{

public:
    FileProcessor(CheckableFile &file);
    ~FileProcessor();
    convertFile();

signals:
    void fileProcessed();
    void logEvent(QString string);

private:
    // ESI Extraction related declarations
    CheckableFile *file;
    EsiExtractor *esiExtractor;
};

#endif // FILEPROCESSOR_H
