/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2012 - Emmanuel Nicolas

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

  Emmanuel Nicolas - FileManagerDelegate.cpp

    The class FileManagerDelegate extends QStyledItemDelegate to define
    a paint function.

*/

#include "filemanagerdelegate.h"
#include <iostream>
#include <QPainter>
#include <QTextOption>
#include <QColor>
#include <QSvgRenderer>

FileManagerDelegate::FileManagerDelegate(QObject *parent) :
        QStyledItemDelegate(parent)
{
}

void FileManagerDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QSvgRenderer *renderer;
    switch (index.column())
    {
    case 0: // File name
        painter->drawText(option.rect, index.data().value<QString>(), QTextOption(Qt::AlignVCenter | Qt::AlignLeft));
        break;
    case 1: // Conversion required
        if (index.data().value<bool>())
            renderer = new QSvgRenderer(QString(":/icons/Check-Green.svg"));
        else
            renderer = new QSvgRenderer(QString(":/icons/Process-Stop.svg"));
        renderer->render(painter,QRectF(option.rect));
        break;
    case 2: // Conversion done
        if (index.data().value<bool>())
            renderer = new QSvgRenderer(QString(":/icons/Check-Green.svg"));
        else
            renderer = new QSvgRenderer(QString(":/icons/Process-Stop.svg"));
        renderer->render(painter,QRectF(option.rect));
        break;
    case 3: // Cross to delete file
        renderer = new QSvgRenderer(QString(":/icons/Delete-File.svg"));
        renderer->render(painter,QRectF(option.rect));
        break;
    default:
        QStyledItemDelegate::paint(painter, option, index);
        break;
    }
}
