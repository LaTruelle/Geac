#include "checkfiledialog.h"
#include <QGridLayout>
#include <QDialogButtonBox>
#include <iostream>
#include <assert.h>

CheckFileDialog::CheckFileDialog() : QFileDialog()
{
    this->setOptions(QFileDialog::DontUseNativeDialog);
    // Retrieve Layout of QFileDialog
    QGridLayout *mainLayout = dynamic_cast<QGridLayout*>(this->layout());
    if(!mainLayout){
        assert(0);
    }
    else{
        // Create custom QGridLayout to add our own widgets
        QGridLayout *hbl = new QGridLayout();
        // Create checkbox
        recursive = new QCheckBox("Checkbox",this);
        // Add checkbox to the layout
        hbl->addWidget(recursive);
        // Add QGridLayout at the bottom of the main layout
        int numRow = mainLayout->rowCount();
        mainLayout->addLayout(hbl,numRow, 0);
    }
 }
