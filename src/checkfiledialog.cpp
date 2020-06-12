/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2020 - Emmanuel Nicolas

  GEAC is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  ---

  Emmanuel Nicolas - CheckFileDialog.cpp

    The class CheckFileDialog defines an extension of QFileDialog in
    order to add dilters to the default Qt file dialog.

*/

#include "checkfiledialog.h"
#include <QDialogButtonBox>
#include <QHBoxLayout>
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
    QGridLayout *mainLayout = dynamic_cast<QGridLayout *>(this->layout());
    if (!mainLayout) {
        assert(0);
    } else {
        // Create custom QGridLayout to add our own widgets
        QHBoxLayout *hbl = new QHBoxLayout();
        // Create checkboxes
        recursive = new QCheckBox(tr("Search Subfolders"), this);
        fileFilterBox = new QComboBox(this);
        fileFilterBox->addItem(tr("All Files"));
        fileFilterBox->addItem(tr("Out and Log Files"));
        fileFilterBox->addItem(tr("Out Files Only"));
        fileFilterBox->addItem(tr("Log Files Only"));
        // Add checkboxes to the layout
        hbl->addWidget(fileFilterBox);
        hbl->addWidget(recursive);
        // Add QGridLayout at the bottom of the main layout
        int numRow = mainLayout->rowCount();
        mainLayout->addLayout(hbl, numRow, 0);
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
