#include "checkfiledialog.h"
#include <QGridLayout>
#include <QDialogButtonBox>
#include <iostream>

// http://www.qtforum.org/article/20841/how-to-add-a-qwidget-in-qfiledialog.html

CheckFileDialog::CheckFileDialog() : QFileDialog()
{
    std::cout << "Constructing Checkfiledialog" << std::endl;
    QGridLayout *mainLayout = dynamic_cast<QGridLayout*>(this->layout());
    std::cout << "mainLayout item number : " << mainLayout->count() << std::endl;

    if(!mainLayout){
        assert(0);
    }
    else{
        std::cout << "lastRow Height: " << mainLayout->rowMinimumHeight(mainLayout->rowCount()) << std::endl;
        std::cout << "Entered layout creation" << std::endl;
        QGridLayout *hbl = new QGridLayout();
        hbl->setRowMinimumHeight(1,50);
        std::cout << "QHBoxLayout created" << std::endl;
        recursive = new QCheckBox("Checkbox",this);
        std::cout << "QCheckbox created" << std::endl;
        hbl->addWidget(recursive);
        std::cout << "Added Checkbox to HBoxLayout" << std::endl;
        int numRow = mainLayout->rowCount();
        std::cout << "numRow counted: " << numRow << std::endl;
        mainLayout->addLayout(hbl,numRow, 0, 50, 50);
        std::cout << "mainLayout item number : " << mainLayout->count() << std::endl;
        std::cout << "hbl added to mainLayout : " << mainLayout->rowCount() << std::endl;
        std::cout << "lastRow Height : " << mainLayout->rowMinimumHeight(mainLayout->rowCount()) << std::endl;
    }
 }
