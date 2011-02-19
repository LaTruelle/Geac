#include "geac.h"
#include <QFileDialog>
#include <iostream>
#include "checkfiledialog.h"
#include <QCheckBox>
#include <QGridLayout>

Geac::Geac(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    setupFileDisplayer();
}

void Geac::setupFileDisplayer()
{
    ui.fileDisplayer->setModel(&fileDisplayerModel);
    ui.fileDisplayer->verticalHeader()->hide();
    ui.fileDisplayer->setColumnWidth(0,ui.fileDisplayer->width()-2*ui.fileDisplayer->horizontalHeader()->height()-2);
    ui.fileDisplayer->setColumnWidth(1,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->setColumnWidth(2,ui.fileDisplayer->horizontalHeader()->height());
}

void Geac::display(QString string)
{
    ui.textDisplay->setText(string);;
}

void Geac::on_actionOpen_File_triggered()
{
    // Open File Dialog to select File --> With filters (or without)
    QFileDialog box;
    QCheckBox *recursive = new QCheckBox(&box);
    recursive->setChecked(true);
    QGridLayout *layout = (QGridLayout*)box.layout();
    layout->addWidget(recursive,0,0);
    QString fileToConvertName = box.getOpenFileName(this, tr("Open File"), QDir::homePath());
    CheckableFile *file = new CheckableFile(this);
    file->setFileName(fileToConvertName);
    fileDisplayerModel.addFile(file);
    display(fileToConvertName);
}

void Geac::on_actionOpen_Folder_triggered()
{
    // Open File Dialog to select Folder
    //    --> With tick for subfolders and recursively fetching all files or no
    //    --> Ticks for files to convert --> out / log / out&log
    baseFolder = QFileDialog::getExistingDirectory(this, tr("Open Folder"), QDir::homePath(), QFileDialog::ShowDirsOnly);
}
