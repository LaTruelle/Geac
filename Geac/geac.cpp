#include "geac.h"
#include <QFileDialog>
#include <iostream>
#include "checkfiledialog.h"

Geac::Geac(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    setupFileDisplayer();
}

void Geac::setupFileDisplayer()
{
    ui.fileDisplayer->setModel(&fileDisplayerModel);
    ui.fileDisplayer->verticalHeader()->hide();
    ui.fileDisplayer->setAlternatingRowColors(true);
    ui.fileDisplayer->horizontalHeader()->setFixedHeight(30);
    ui.fileDisplayer->setColumnWidth(0,ui.fileDisplayer->width()-2*ui.fileDisplayer->horizontalHeader()->height()-2);
    ui.fileDisplayer->setColumnWidth(1,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->setColumnWidth(2,ui.fileDisplayer->horizontalHeader()->height());
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
    baseFolder = QFileDialog::getExistingDirectory(this, tr("Open Folder"), QDir::homePath(), QFileDialog::ShowDirsOnly);
}
