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
    if (dialog->exec())
    {
        baseFolder = dialog->selectedFiles().first();
        // Set filters
        QStringList filters;
        switch (dialog->getFileFilter())
        {
        case CheckFileDialog::out:
            filters << "*.out";
            break;
        case CheckFileDialog::log:
            filters << "*.log";
            break;
        case CheckFileDialog::outAndLog:
            filters << "*.out" << "*.log";
            break;
        default:
            filters << "*.*";
            break;
        }
        // If recursive Checked
        if (dialog->getRecursivity())
        {
            // Add contents of baseFolder
            if (!baseFolder.entryList(QDir::Files).isEmpty())
            {
                addFilesFromList(baseFolder.entryInfoList(filters, QDir::Files,QDir::Name));
            }
            // Add all directories in baseFolder, initiating a list of folder to search
            QFileInfoList list(baseFolder.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));
            for(int i=0; i<list.count(); i++)
            {
                dirList.append(list.at(i).absoluteFilePath());
            }
            list.clear();
            // Iterate on the list, adding files in first folder, and appending included folders to the list
            while (!dirList.isEmpty())
            {
                QDir *dir = new QDir(dirList.takeFirst());
                if (!dir->entryList(QDir::Files).isEmpty())
                {
                    addFilesFromList(dir->entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot));
                }
                list.append(dir->entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));
                for(int i=0; i<list.count(); i++)
                {
                    dirList.append(list.at(i).absoluteFilePath());
                }
                list.clear();
            }
        }
        else
        {
            addFilesFromList(baseFolder.entryInfoList(filters, QDir::Files,QDir::Name));
        }
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

void Geac::on_createEsi_clicked()
{
    esiExtractor.setRequiredFields(reqThermochemistry, reqHarmonicFrequencies, reqStandardCoordinates, reqHartreeFock);
    for(int i=0; i<fileDisplayerModel.rowCount(); i++)
    {
        QFile file("test");
        esiExtractor.setInputFile(file);
        esiExtractor.setOutputFile(file);
        esiExtractor.createEsi();
    }
}
