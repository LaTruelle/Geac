#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QDir>
#include <esiextractor.h>
#include "checkablefile.h"

class FileProcessor : public QObject
{
    Q_OBJECT

public:
    FileProcessor(QString fileName);
    ~FileProcessor();
    void convertFile();
    void setFileName(QString &string);
    void setupProcessor(bool &thermoChem,
                        bool &harmFreq,
                        bool &stdCoord,
                        bool &hfEnergy,
                        QDir &outFolder,
                        QString &fileExt
                        );

signals:
    void fileProcessed(int id);
    void logEvent(QString string);

private:
    // ESI Extraction related declarations
    QFile file;
    EsiExtractor esiExtractor;
    int id;
};

#endif // FILEPROCESSOR_H
