#include "checkfiledialog.h"
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <iostream>
#include <assert.h>

CheckFileDialog::CheckFileDialog() : QFileDialog()
{
    filters << tr("All Files (*.*)")
            << tr("All Gaussian Output Files (*.out *.log)")
            << tr("Gaussian out files (*.out)")
            << tr("Gaussian log files (*.log)");
}

void CheckFileDialog::setMultipleFilesMode()
{
    this->setNameFilters(filters);
    // Set Possibility of selecting multiple files
    this->setFileMode(QFileDialog::ExistingFiles);
}

void CheckFileDialog::setDirectoryMode()
{
    // Set directory mode
    this->setFileMode(QFileDialog::Directory);
    this->setOption(QFileDialog::ShowDirsOnly, true);
    //             ---------------------
    // Add Checkbox at the bottom to select recursivity and filter files
    //             ---------------------
    this->setOptions(QFileDialog::DontUseNativeDialog);
    // Retrieve Layout of QFileDialog
    QGridLayout *mainLayout = dynamic_cast<QGridLayout*>(this->layout());
    if(!mainLayout){
        assert(0);
    }
    else{
        // Create custom QGridLayout to add our own widgets
        QHBoxLayout *hbl = new QHBoxLayout();
        // Create checkboxes
        recursive = new QCheckBox(tr("Search Subfolders"),this);
        fileFilterBox = new QComboBox(this);
        fileFilterBox->addItem(tr("Out Files Only"));
        fileFilterBox->addItem(tr("Log Files Only"));
        fileFilterBox->addItem(tr("Out and Log Files"));
        fileFilterBox->addItem(tr("All Files"));
        // Add checkboxes to the layout
        hbl->addWidget(fileFilterBox);
        hbl->addWidget(recursive);
        // Add QGridLayout at the bottom of the main layout
        int numRow = mainLayout->rowCount();
        mainLayout->addLayout(hbl,numRow, 0);
    }
}

int CheckFileDialog::getFileFilter()
{
    return fileFilterBox->currentIndex();
}

bool CheckFileDialog::getRecursivity()
{
    return recursive->isChecked();
}
