#include "filemanagerdelegate.h"
#include <iostream>
#include <QPainter>
#include <QTextOption>
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
        painter->drawText(option.rect, index.data().value<QString>(), QTextOption(Qt::AlignVCenter | Qt::AlignLeft));
        break;
    case 1: // Conversion required
        if (index.data().value<bool>())
            painter->fillRect(option.rect,QColor("green"));
        else
            painter->fillRect(option.rect,QColor("red"));
        break;
    case 2: // Conversion done
        if (index.data().value<bool>())
            painter->fillRect(option.rect,QColor("green"));
        else
            painter->fillRect(option.rect,QColor("red"));
        break;
    case 3: // Cross to delete file
        QStyledItemDelegate::paint(painter, option, index);
        break;
    default:
        QStyledItemDelegate::paint(painter, option, index);
        break;
    }
}
