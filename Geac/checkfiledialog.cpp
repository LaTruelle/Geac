#include "checkfiledialog.h"
#include <QDialogButtonBox>
#include <QBoxLayout>

CheckFileDialog::CheckFileDialog(QWidget *parent) : QFileDialog(parent),recursive(0)
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
