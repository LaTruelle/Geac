#ifndef CIFWRITER_H
#define CIFWRITER_H

#include <QObject>
#include <QList>
#include "checkablefile.h"

class CifWriter : public QObject
{
    Q_OBJECT
public:
    CifWriter();
    void addFiletoList(CheckableFile file);
    void addListofFiles(QList<CheckableFile*> list);
    void setOutputFile(QFile &file);
    void createCif();

signals:
    void fileProcessed(QString fileName);

private:
    QList<CheckableFile*> files;
    QFile outputFile;
};

#endif // CIFWRITER_H
