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
    int rowCount() const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QString getFilePath(int row);
    CheckableFile& getFile(int i);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addFile(CheckableFile *file);
    void clearFiles();
    bool getRequiredConversion(QModelIndex &index);
    bool getRequiredConversion(int i);
    void setConverted(int i);

private:
    QList<CheckableFile *> listOfFiles;
    QStringList header;

signals:
    void eventToDisplay(QString string);

public slots:

};

#endif // FILEMANAGER_H
