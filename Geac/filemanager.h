#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QAbstractTableModel>
#include <QVariant>

class FileManager : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

signals:

public slots:

};

#endif // FILEMANAGER_H
