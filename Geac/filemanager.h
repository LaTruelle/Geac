#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QList>
#include <QStringList>
#include "checkablefile.h"

class FileManager : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileManager(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addFile(CheckableFile *file);
    void clearFiles();

private:
    QList<CheckableFile *> listOfFiles;
    QStringList header;

signals:

public slots:

};

#endif // FILEMANAGER_H
