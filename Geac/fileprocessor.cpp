#include "fileprocessor.h"
#include <iostream>

FileProcessor::FileProcessor(QString fileName)
{
    file.setFileName(fileName);
}

FileProcessor::~FileProcessor()
{
}

void FileProcessor::setupProcessor(bool &thermoChem,
                                   bool &harmFreq,
                                   bool &stdCoord,
                                   bool &hfEnergy,
                                   QDir &outFolder,
                                   QString &fileExt
                                   )
{
    // transmit necessary data directly to the extractor
    esiExtractor.setRequiredFields(thermoChem, harmFreq, stdCoord, hfEnergy);
    esiExtractor.setOutputFolder(outFolder);
    esiExtractor.setExtension(fileExt);
}

void FileProcessor::convertFile()
{
    // convert File
}
