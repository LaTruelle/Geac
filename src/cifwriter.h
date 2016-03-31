#ifndef CIFWRITER_H
#define CIFWRITER_H

#include "checkablefile.h"
#include <QList>
#include <QObject>

class CifWriter : public QObject
{
    Q_OBJECT
public:
    CifWriter();
    void addFiletoList(CheckableFile file);
    void addListofFiles(QList<CheckableFile *> list);
    void setOutputFile(QFile &file);
    void createCif();

signals:
    void fileProcessed(QString fileName);

private:
    QList<CheckableFile *> files;
    QFile outputFile;
};

#endif // CIFWRITER_H
