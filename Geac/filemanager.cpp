#include "filemanager.h"
#include <iostream>

FileManager::FileManager(QObject *parent) :
    QAbstractTableModel(parent)
{
    header << "File Names" << " " << " " << " ";
}

void FileManager::addFile(CheckableFile *file)
{
    beginInsertRows(index(listOfFiles.count(),0),listOfFiles.count(),listOfFiles.count());
    listOfFiles.append(file);
    endInsertRows();
}

void FileManager::clearFiles()
{
    if(!listOfFiles.isEmpty())
    {
        beginRemoveRows(index(listOfFiles.count(),0),0,listOfFiles.count()-1);
        listOfFiles.clear();
        endRemoveRows();
    }
}

int FileManager::rowCount(const QModelIndex & /* parent */ ) const
{
    return listOfFiles.count();
}

int FileManager::rowCount()
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
    else if (role == Qt::TextAlignmentRole)
        return QVariant();
    else if (role == Qt::DisplayRole)
    {
        switch (index.column()){
        case 0:
            return listOfFiles.at(index.row())->fileName();
            // to modify according to http://www.qtcentre.org/threads/29550-How-do-I-display-a-picture-on-a-QTableView-cell
            // in order to display ticks or colors instead of "true" or "false"
        case 1:
            return listOfFiles.at(index.row())->getConversionRequired();
        case 2:
            return listOfFiles.at(index.row())->getConversionState();
        case 3:
            return "X";
        }
    }
    return QVariant();
}

QVariant FileManager::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role==Qt::DisplayRole && orientation==Qt::Horizontal)
        return header[section];
    else
        return QVariant();
}
