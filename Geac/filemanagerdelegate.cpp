#include "filemanagerdelegate.h"
#include <iostream>

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

