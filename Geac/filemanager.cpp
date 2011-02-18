#include "filemanager.h"

FileManager::FileManager(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int FileManager::rowCount(const QModelIndex & /* parent */ ) const
{
    return 0;
}

int FileManager::columnCount(const QModelIndex & /* parent */ ) const
{
    return 0;
}

QVariant FileManager::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    // To check and modify. Advantage of this method : no compilation error or warning.
    if (role == Qt::TextAlignmentRole)
        return QVariant();

    else
        return QVariant();
}
