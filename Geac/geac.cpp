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
    dialog->setMultipleFilesMode();
    dialog->setDirectory(QDir::homePath());
    dialog->exec();
    QFileInfoList fileList;
    for(int i=0; i<dialog->selectedFiles().count(); i++)
    {
        fileList.append(QFileInfo(dialog->selectedFiles().at(i)));
    }
    addFilesFromList(fileList);
    delete dialog;
}

void Geac::on_actionOpen_Folder_triggered()
{
    // Open File Dialog to select Folder
    //    --> With tick for subfolders and recursively fetching all files or no
    //    --> Ticks for files to convert --> out / log / out&log
    CheckFileDialog *dialog = new CheckFileDialog();
    dialog->setDirectoryMode();
    dialog->setDirectory(QDir::homePath());
    dialog->exec();
    baseFolder = dialog->selectedFiles().first();
    if (dialog->getRecursivity())
    {
        addFilesFromList(baseFolder.entryInfoList(QDir::Files,QDir::Name));
        std::cout
                << "first file added : "
                << baseFolder.entryInfoList(QDir::Files,QDir::Name).first().absoluteFilePath().toStdString()
                << std::endl;
        QFileInfoList list(baseFolder.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));
        for(int i=0; i<list.count(); i++)
        {
            std::cout << dirList.join(" // ").toStdString() << std::endl;
            dirList.append(list.at(i).absolutePath()); // Problem : adds n times the current folder, not its subfolders
        }
        std::cout << dirList.join(" | ").toStdString() << std::endl;
        list.clear();
        /*
        while (!dirList.isEmpty())
        {
            std::cout << dirList.join(" | ").toStdString() << std::endl;
            QDir *dir = new QDir(dirList.takeFirst());
            std::cout << "directory used : " << dir->absolutePath().toStdString() << std::endl;
            addFilesFromList(dir->entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));
            list.append(dir->entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));
            for(int i=0; i<list.count(); i++)
            {
                std::cout << "directory added : " << list.at(i).absolutePath().toStdString() << std::endl;
                dirList.append(list.at(i).absolutePath()); // To change here as well
            }
            list.clear();
        }
        */
    }
    else
    {
        addFilesFromList(baseFolder.entryInfoList(QDir::Files,QDir::Name));
    }
    delete dialog;
}

void::Geac::addFilesFromList(QFileInfoList fileNames)
{
    // Retrieve files in the list and add them to model
    int limit = fileNames.count();
    for (int i=0; i<limit; i++)
    {
        CheckableFile *file = new CheckableFile(this);
        file->setFileName(fileNames.takeFirst().absoluteFilePath());
        fileDisplayerModel.addFile(file);
        display(file->fileName());
    }
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
