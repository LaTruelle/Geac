#include "filemanagerdelegate.h"

FileManagerDelegate::FileManagerDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void FileManagerDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Switch case on columns : file name / images for options (ticks, crosses etc)
}

void FileManagerDelegate::setModelData(QWidget *editor,
                                       QAbstractItemModel *model,
                                       const QModelIndex &index) const
{
    // Modify data on clicking in cases --> delete rows, update "required" field, depending on column.
}

void FileManagerDelegate::updateEditorGeometry(QWidget *editor,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex &index) const
{
    editor->setGeometry(option.rect); // Switch case on index ? To test...
}

QSize FileManagerDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Gives sizeHint according to columns.
    switch(index.column())
    {
    case 0:
        return QSize(150,30);
    case 1:
        return QSize(30,30);
    case 2:
        return QSize(30,30);
    case 3:
        return QSize(30,30);
    default:
        return QSize();
    }
}
