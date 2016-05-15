/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2014 - Emmanuel Nicolas

  GEAC is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  ---

  Emmanuel Nicolas - FileManager.cpp

    The class FileManager extends the QAbstractTableModel to fit it to
    to our model --> Array of Checkablefiles, with conversion states and
    "need to convert" state.

*/

#include "filemanager.h"
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QMimeData>

FileManager::FileManager(QObject *parent) : QAbstractTableModel(parent)
{
    header << "File Names"
           << " "
           << " "
           << " ";
}

void FileManager::addFile(CheckableFile *file)
{
    // We iterate over the fileList. If the file exists we return
    for (int i = 0; i < listOfFiles.count(); i++) {
        if (file->fileName() ==
            listOfFiles.at(i)
                ->fileName()) // meaning the file exists already in the list
        {
            emit eventToDisplay(
                tr("File %1 already exists").arg(file->displayName()));
            return; // TODO: Transform this properly
        }
    }
    // If we reached the end then the file is new, we save it.
    beginInsertRows(index(listOfFiles.count(), 0), listOfFiles.count(),
                    listOfFiles.count());
    listOfFiles.append(file);
    endInsertRows();
    emit eventToDisplay(tr("File %1 added").arg(file->displayName()));
}

void FileManager::clearFiles()
{
    if (!listOfFiles.isEmpty()) {
        beginRemoveRows(index(listOfFiles.count(), 0), 0,
                        listOfFiles.count() - 1);
        listOfFiles.clear();
        endRemoveRows();
        emit eventToDisplay(tr("List of files cleared"));
    }
}

int FileManager::rowCount(const QModelIndex & /* parent */) const
{
    return listOfFiles.count();
}

int FileManager::rowCount() const
{
    return listOfFiles.count();
}

bool FileManager::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count);
    for (int currentRow = row; currentRow < row + count; ++currentRow) {
        if (currentRow < listOfFiles.size()) {
            listOfFiles.removeAt(currentRow);
        } else {
            return false;
        }
    }
    endRemoveRows();
    return true;
}

bool FileManager::insertRows(int row, int count, const QModelIndex &parent)
{
    if (!parent.isValid()) {
        return false;
    }
    beginInsertRows(parent, row, row + count);
    for (int currentRow = row; currentRow < row + count; ++currentRow) {
        if (currentRow < listOfFiles.size()) {
            qDebug() << parent.data().type();
            listOfFiles.insert(currentRow,
                               qvariant_cast<CheckableFile *>(parent.data()));
        } else {
            return false;
        }
    }
    endInsertRows();
    return true;
}

int FileManager::columnCount(const QModelIndex & /* parent */) const
{
    return header.count();
}

QVariant FileManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    else if (role == Qt::TextAlignmentRole)
        return QVariant();
    else if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: {
            QString name = listOfFiles.at(index.row())->fileName();
            name.remove(0, name.lastIndexOf(QDir::separator()) +
                               1); // Returns name of file, without its path
            return name;
        }
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

QString FileManager::getFilePath(int row)
{
    return listOfFiles.at(row)->fileName();
}

QVariant FileManager::headerData(int section, Qt::Orientation orientation,
                                 int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return header[section];
    else
        return QVariant();
}

bool FileManager::setData(const QModelIndex &index,
                          const QVariant & /* value */, int /* role */)
{
    if (!index.isValid())
        return false;

    switch (index.column()) {
    case 1:
        listOfFiles.at(index.row())
            ->setConversionRequired(
                !listOfFiles.at(index.row())->getConversionRequired());
        break;
    case 3:
        beginRemoveRows(index.parent(), index.row(), index.row());
        listOfFiles.removeAt(index.row());
        endRemoveRows();
    }
    emit dataChanged(index, index);
    return true;
}

bool FileManager::getRequiredConversion(QModelIndex &index)
{
    // Returns true if, according to the model, the file needs to be converted.
    if (!index.isValid())
        return false;

    return listOfFiles.at(index.row())->getConversionRequired();
}

bool FileManager::getRequiredConversion(int i)
{
    // Returns true if the file on line i needs to be converted
    return listOfFiles.at(i)->getConversionRequired();
}

void FileManager::setConverted(int i)
{
    // set Conversion state of File
    listOfFiles.at(i)->setConversionState(true);
}

CheckableFile &FileManager::getFile(int i)
{
    return *listOfFiles.at(i);
}

Qt::DropActions FileManager::supportedDropActions() const
{
    return Qt::MoveAction;
}

bool FileManager::dropMimeData(const QMimeData *data, Qt::DropAction action,
                               int row, int /*column*/,
                               const QModelIndex &parent)
{
    if (!data->hasFormat("text/checkable-file"))
        return false;

    if (action != Qt::MoveAction) {
        return false;
    } else {
        QByteArray encodedData = data->data("text/checkable-file");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd()) {
            beginInsertRows(parent, row, row);
            CheckableFile *file = new CheckableFile();
            stream >> file;
            listOfFiles.insert(row, file);
            endInsertRows();
        }
        return true;
    }
}

QMimeData *FileManager::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            stream << listOfFiles.at(index.row());
        }
    }
    mimeData->setData("text/checkable-file", encodedData);
    qDebug() << listOfFiles.size();
    return mimeData;
}

QStringList FileManager::mimeTypes() const
{
    return QStringList("text/checkable-file");
}

Qt::ItemFlags FileManager::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}
