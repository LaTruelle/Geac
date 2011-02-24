#include "geac.h"
#include <QFileDialog>
#include <iostream>
#include "checkfiledialog.h"

Geac::Geac(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.fileDisplayer->setModel(&fileDisplayerModel);
    ui.fileDisplayer->setItemDelegate(&fileDisplayerDelegate);
    ui.fileDisplayer->horizontalHeader()->resizeSections(QHeaderView::Custom);
    reqHarmonicFrequencies = false;     // Default for the moment. To be updated, according to stored preferences.
    reqHartreeFock = false;
    reqStandardCoordinates = false;
    reqThermochemistry = false;
}

void Geac::setupFileDisplayer()
{
    ui.fileDisplayer->verticalHeader()->hide();
    ui.fileDisplayer->setAlternatingRowColors(true);
    ui.fileDisplayer->horizontalHeader()->setFixedHeight(30);
//    ui.fileDisplayer->setColumnWidth(0,ui.fileDisplayer->width()-3*ui.fileDisplayer->horizontalHeader()->height()-3);
//    ui.fileDisplayer->setColumnWidth(1,ui.fileDisplayer->horizontalHeader()->height());
//    ui.fileDisplayer->setColumnWidth(2,ui.fileDisplayer->horizontalHeader()->height());
//    ui.fileDisplayer->setColumnWidth(3,ui.fileDisplayer->horizontalHeader()->height());
}

void Geac::display(QString string)
{
    ui.textDisplay->setPlainText(string);
}

void Geac::on_actionOpen_File_triggered()
{
    // Open File Dialog to select File --> With filters (or without)
    // Create CheckFileDialog to retrieve files wanted, with checkboxes to get options
    //      -> recursive
    //      ->
    CheckFileDialog *dialog = new CheckFileDialog();
    dialog->setDirectory(QDir::homePath());
    dialog->exec();
    QString fileToConvertName = dialog->selectedFiles().first();
    CheckableFile *file = new CheckableFile(this);
    file->setFileName(fileToConvertName);
    fileDisplayerModel.addFile(file);
    display(fileToConvertName);
    delete dialog;
}

void Geac::on_actionOpen_Folder_triggered()
{
    // Open File Dialog to select Folder
    //    --> With tick for subfolders and recursively fetching all files or no
    //    --> Ticks for files to convert --> out / log / out&log
    baseFolder = QFileDialog::getExistingDirectory(this, tr("Open Folder"),
                                                   QDir::homePath(), QFileDialog::ShowDirsOnly);
}

void Geac::on_harmonicFrequencies_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqHarmonicFrequencies = false;
    else
        reqHarmonicFrequencies = true;
}

void Geac::on_thermochemistry_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqThermochemistry = false;
    else
        reqThermochemistry = true;
}


void Geac::on_hartreeFock_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqHartreeFock = false;
    else
        reqHartreeFock = true;
}

void Geac::on_standardCoordinates_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqStandardCoordinates = false;
    else
        reqStandardCoordinates = true;
}

void Geac::on_toolButton_clicked()
{
    esiFolder.setPath(QFileDialog::getExistingDirectory(this, tr("Store ESI in this directory"),
                                                        QDir::homePath(), QFileDialog::ShowDirsOnly)
                      );
    ui.folderToSave->setText(esiFolder.dirName());
}

void Geac::on_clearFiles_clicked()
{
    this->fileDisplayerModel.clearFiles();
}
