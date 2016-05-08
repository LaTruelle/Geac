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

  Emmanuel Nicolas - FileManager.h

    The class FileManager extends the QAbstractTableModel to fit it to
    to our model --> Array of Checkablefiles, with conversion states and
    "need to convert" state.

*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "checkablefile.h"
#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include <QVariant>

class FileManager : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileManager(QObject *parent = 0);
    int rowCount() const;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const Q_DECL_OVERRIDE;

    void addFile(CheckableFile *file);
    QString getFilePath(int row);
    CheckableFile &getFile(int i);
    void clearFiles();
    bool removeRows(int row, int count,
                    const QModelIndex &parent) Q_DECL_OVERRIDE;
    bool insertRows(int row, int count,
                    const QModelIndex &parent) Q_DECL_OVERRIDE;
    QMimeData *mimeData(const QModelIndexList &indexes) const Q_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                      int column, const QModelIndex &parent) Q_DECL_OVERRIDE;
    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    bool getRequiredConversion(QModelIndex &index);
    bool getRequiredConversion(int i);
    void setConverted(int i);

    Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QList<CheckableFile *> listOfFiles;
    QStringList header;

signals:
    void eventToDisplay(QString string);

public slots:
};

#endif // FILEMANAGER_H
