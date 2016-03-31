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

  Emmanuel Nicolas - FileManagerDelegate.h

    The class FileManagerDelegate extends QStyledItemDelegate to define
    a paint function.

*/

#ifndef FILEMANAGERDELEGATE_H
#define FILEMANAGERDELEGATE_H

#include <QSize>
#include <QStyledItemDelegate>

class FileManagerDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FileManagerDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

signals:

public slots:
};

#endif // FILEMANAGERDELEGATE_H
