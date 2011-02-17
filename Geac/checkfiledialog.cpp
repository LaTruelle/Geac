#include "checkfiledialog.h"
#include <QDialogButtonBox>
#include <QBoxLayout>
#include <iostream>

// http://www.qtforum.org/article/20841/how-to-add-a-qwidget-in-qfiledialog.html

CheckFileDialog::CheckFileDialog(QWidget *parent) : QFileDialog(parent), recursive(0)
{
    QGridLayout *mainLayout = dynamic_cast<QGridLayout*>(layout());

    if(!mainLayout){
        assert(0);
    }
    else{
        QHBoxLayout *hbl = new QHBoxLayout();
        recursive = new QCheckBox(parent);
        hbl->addWidget(recursive);
        int numRow = mainLayout->rowCount();
        mainLayout->addLayout(hbl, numRow, 0, 1, -1);
    }
}

/*
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
*/
