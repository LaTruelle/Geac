#include "geac.h"
#include <QFileDialog>
#include <iostream>
#include "checkfiledialog.h"

Geac::Geac(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.fileDisplayer->setModel(&fileDisplayerModel);
    ui.fileDisplayer->setItemDelegate(&fileDisplayerDelegate);
    setupFileDisplayer();
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
    ui.fileDisplayer->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);        // As big as possible
    ui.fileDisplayer->setColumnWidth(1,ui.fileDisplayer->horizontalHeader()->height()); // Squares at the end of the table
    ui.fileDisplayer->horizontalHeader()->setResizeMode(1,QHeaderView::Fixed);
    ui.fileDisplayer->setColumnWidth(2,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->horizontalHeader()->setResizeMode(2,QHeaderView::Fixed);
    ui.fileDisplayer->setColumnWidth(3,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->horizontalHeader()->setResizeMode(3,QHeaderView::Fixed);

    ui.fileDisplayer->horizontalHeader()->setClickable(false);
    ui.fileDisplayer->setShowGrid(false);
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
    CheckFileDialog *dialog = new CheckFileDialog();
    dialog->setDirectory(QDir::homePath());
    dialog->setOption(QFileDialog::ShowDirsOnly, true);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->exec();
    baseFolder = dialog->selectedFiles().first();
    if (dialog->getRecursivity())
    {
        // add All files in all subfolders of baseFolder
    }
    else
    {
        QStringList *filesNames = new QStringList(baseFolder.entryList(QDir::Files,QDir::Name));
        int limit = filesNames->count();
        for (int i=0; i<limit; i++)
        {
            CheckableFile *file = new CheckableFile(this);
            file->setFileName(filesNames->takeFirst());
            fileDisplayerModel.addFile(file);
            display(file->fileName());
        }
    }
    delete dialog;
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
