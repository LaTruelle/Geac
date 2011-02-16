#include "geac.h"
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include "checkfiledialog.h"

Geac::Geac(QWidget *parent) :
    QMainWindow(parent){
    ui.setupUi(this);
}

void Geac::on_actionOpen_File_triggered()
{
    // Open File Dialog to select File --> With filters (or without)
    // TODO: Add Filters in QFileDialog
    // Create object QFile fileToConvert and open it.
    CheckFileDialog *dialog = new CheckFileDialog(this);
    dialog->addCheckBoxIn();
    dialog->setOption(QFileDialog::DontUseNativeDialog);
    QString fileToConvertName = dialog->getOpenFileName(this, tr("Open File"), QDir::homePath());

    fileToConvert.setFileName(fileToConvertName);
    fileToConvert.open(QIODevice::ReadOnly);

    // Create TextStream to parse the file
    QTextStream reader(&fileToConvert);
}

void Geac::on_actionOpen_Folder_triggered()
{
    // Open File Dialog to select Folder
    //    --> With tick for subfolders and recursively fetching all files or no
    //    --> Ticks for files to convert --> out / log / out&log
    baseFolder = QFileDialog::getExistingDirectory(this, tr("Open Folder"), QDir::homePath(), QFileDialog::ShowDirsOnly);
}
