#include "filemanager.h"
#include <iostream>

FileManager::FileManager(QObject *parent) :
    QAbstractTableModel(parent)
{
    header << "File Names" << "a" << "h";
}

void FileManager::addFile(CheckableFile *file)
{
    listOfFiles.append(file);
    QModelIndex index = createIndex(listOfFiles.count(file),listOfFiles.count(file));
    emit dataChanged(index,index);
//    std::cout << "Added File : " << file->fileName().toStdString() << " at index : "
//              << listOfFiles.count(file) << std::endl;
}

int FileManager::rowCount(const QModelIndex & /* parent */ ) const
{
    return listOfFiles.count();
}

int FileManager::columnCount(const QModelIndex & /* parent */ ) const
{
    return header.count();
}

QVariant FileManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    // To check and modify. Advantage of this method : no compilation error or warning.
    if (role == Qt::TextAlignmentRole)
        return QVariant();
    else
        return QVariant();
}

QVariant FileManager::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    if (role==Qt::DisplayRole)
        return header[section];
    else
        return QVariant();
}
