#ifndef FILEMANAGERDELEGATE_H
#define FILEMANAGERDELEGATE_H

#include <QStyledItemDelegate>
#include <QSize>

class FileManagerDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FileManagerDelegate(QObject *parent = 0);
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // FILEMANAGERDELEGATE_H
