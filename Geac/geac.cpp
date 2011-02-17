#include "geac.h"
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include "checkfiledialog.h"
#include <QCheckBox>
#include <QGridLayout>

Geac::Geac(QWidget *parent) :
    QMainWindow(parent){
    ui.setupUi(this);
}

void Geac::on_actionOpen_File_triggered()
{
    // Open File Dialog to select File --> With filters (or without)
//    CheckFileDialog *dialog = new CheckFileDialog(this);
//    QString fileToConvertName = dialog->getOpenFileName(this, tr("Open File"), QDir::homePath());

    QFileDialog box;
    QCheckBox *recursive = new QCheckBox(&box);
    recursive->setChecked(true);
    QGridLayout *layout = (QGridLayout*)box.layout();
    layout->addWidget(recursive,0,0);
    QString fileToConvertName = box.getOpenFileName(this, tr("Open File"), QDir::homePath());


    //    fileToConvert.setFileName(fileToConvertName);
//    fileToConvert.open(QIODevice::ReadOnly);

    // Create TextStream to parse the file
    // QTextStream reader(&fileToConvert);
}

void Geac::on_actionOpen_Folder_triggered()
{
    // Open File Dialog to select Folder
    //    --> With tick for subfolders and recursively fetching all files or no
    //    --> Ticks for files to convert --> out / log / out&log
    baseFolder = QFileDialog::getExistingDirectory(this, tr("Open Folder"), QDir::homePath(), QFileDialog::ShowDirsOnly);
}
