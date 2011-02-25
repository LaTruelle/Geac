#include "filemanagerdelegate.h"
#include <iostream>
#include <QPainter>
#include <QColor>

FileManagerDelegate::FileManagerDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void FileManagerDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 0: // File name
        QStyledItemDelegate::paint(painter, option, index);
        break;
    case 1: // Conversion required
        painter->fillRect(option.rect,QColor("green"));
        break;
    case 2: // Conversion done
        QStyledItemDelegate::paint(painter, option, index);
        break;
    case 3:
        QStyledItemDelegate::paint(painter, option, index);
        break;
    default:
        QStyledItemDelegate::paint(painter, option, index);
        break;
    }
}
