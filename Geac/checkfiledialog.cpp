#include "checkfiledialog.h"
#include <QGridLayout>
#include <QDialogButtonBox>
#include <iostream>
#include <assert.h>

CheckFileDialog::CheckFileDialog() : QFileDialog()
{
    filters << tr("All Files (*.*)")
            << tr("All Gaussian Output Files (*.out *.log)")
            << tr("Gaussian out files (*.out)")
            << tr("Gaussian log files (*.log)");
    this->setNameFilters(filters);
}

void CheckFileDialog::setMultipleFilesMode()
{
    // Set Possibility of selecting multiple files
    this->setFileMode(QFileDialog::ExistingFiles);
}

void CheckFileDialog::setDirectoryMode()
{
    // Set directory mode
    this->setOption(QFileDialog::ShowDirsOnly, true);
    this->setFileMode(QFileDialog::Directory);

    //             ---------------------
    // Add Checkbox at the bottom to select recursivity
    //             ---------------------
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
        recursive = new QCheckBox(tr("Search Subfolders"),this);
        // Add checkbox to the layout
        hbl->addWidget(recursive);
        // Add QGridLayout at the bottom of the main layout
        int numRow = mainLayout->rowCount();
        mainLayout->addLayout(hbl,numRow, 0);
    }
}

bool CheckFileDialog::getRecursivity()
{
    return recursive->isChecked();
}
