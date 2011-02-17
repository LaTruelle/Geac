#include "checkfiledialog.h"
#include <QDialogButtonBox>
#include <QBoxLayout>
// http://www.qtforum.org/article/20841/how-to-add-a-qwidget-in-qfiledialog.html
//CheckFileDialog::CheckFileDialog(QWidget *parent) : QFileDialog(parent),recursive(0)
CheckFileDialog::CheckFileDialog(QWidget *parent) : QFileDialog(parent)
{
}

void CheckFileDialog::addCheckBoxIn()
{
    QDialogButtonBox *box = qFindChild<QDialogButtonBox*>(this);
    Q_ASSERT(box);
    QBoxLayout *l = qFindChild<QBoxLayout*>(box);
    Q_ASSERT(l);
    QCheckBox *toProj = new QCheckBox("To Project:", box);
    toProj->setChecked(true);
    l->insertWidget(0, toProj);
}
