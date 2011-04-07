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
            renderer = new QSvgRenderer(QString(":/icons/images/icons/Check-Green.svg"));
        else
            renderer = new QSvgRenderer(QString(":/icons/images/icons/Process-Stop.svg"));
        renderer->render(painter,QRectF(option.rect));
        break;
    case 2: // Conversion done
        if (index.data().value<bool>())
            renderer = new QSvgRenderer(QString(":/icons/images/icons/Check-Green.svg"));
        else
            renderer = new QSvgRenderer(QString(":/icons/images/icons/Process-Stop.svg"));
        renderer->render(painter,QRectF(option.rect));
        break;
    case 3: // Cross to delete file
        renderer = new QSvgRenderer(QString(":/icons/images/icons/Delete-File.svg"));
        renderer->render(painter,QRectF(option.rect));
        break;
    default:
        QStyledItemDelegate::paint(painter, option, index);
        break;
    }
}
