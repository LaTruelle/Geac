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
    // Hide Progress Bar
    ui.progressBar->hide();
    ui.progressLabel->hide();
    // Call to readSettings necessary here
    reqHarmonicFrequencies = false;     // Default for the moment. To be updated, according to stored preferences.
    reqHartreeFock = false;
    reqStandardCoordinates = false;
    reqThermochemistry = false;
}

void Geac::setupFileDisplayer()
{
    // Set Header Style
    ui.fileDisplayer->horizontalHeader()->setClickable(false);
    ui.fileDisplayer->horizontalHeader()->setFixedHeight(30);
    ui.fileDisplayer->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui.fileDisplayer->horizontalHeader()->setStyleSheet("QHeaderView::section{padding-left: 10px; font: 15px; color: black;}");
    // Set File Displayer Style
    ui.fileDisplayer->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.fileDisplayer->verticalHeader()->hide();
    ui.fileDisplayer->setAlternatingRowColors(true);
    ui.fileDisplayer->setShowGrid(false);
    ui.fileDisplayer->setStyleSheet("selection-background-color : rgba(0, 0, 255, 25%)");
    // Set Sizes of columns
    ui.fileDisplayer->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);        // As big as possible
    ui.fileDisplayer->setColumnWidth(1,ui.fileDisplayer->horizontalHeader()->height()); // Squares at the end of the table
    ui.fileDisplayer->horizontalHeader()->setResizeMode(1,QHeaderView::Fixed);
    ui.fileDisplayer->setColumnWidth(2,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->horizontalHeader()->setResizeMode(2,QHeaderView::Fixed);
    ui.fileDisplayer->setColumnWidth(3,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->horizontalHeader()->setResizeMode(3,QHeaderView::Fixed);
}

void Geac::display(QString string)
{
    ui.textDisplay->setPlainText(string + "\n" + ui.textDisplay->toPlainText());
}

void Geac::clearLog()
{
    ui.textDisplay->clear();
}

void Geac::on_actionOpen_File_triggered()
{
    // Open File Dialog to select File --> With filters (or without)
    CheckFileDialog *dialog = new CheckFileDialog();
    dialog->setMultipleFilesMode();
    dialog->setDirectory(QDir::homePath());
    dialog->exec();
    QFileInfoList fileList;
    // Iterate over the selected files to retrieve them
    for(int i=0; i<dialog->selectedFiles().count(); i++)
    {
        fileList.append(QFileInfo(dialog->selectedFiles().at(i)));
    }
    // Add the files in the model
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
        int f = fileDisplayerModel.addFile(file);
        if (f==0)
            display(file->fileName() + tr(" added"));
        else
            display(file->fileName() + tr(" already included"));
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

void Geac::on_SaveFolderSelection_clicked()
{
    // Sets the dedicated folder in which all files will be stored
    esiFolder.setPath(QFileDialog::getExistingDirectory(this, tr("Store ESI in this directory"),
                                                        QDir::homePath(), QFileDialog::ShowDirsOnly)
                      );
    // Display the name of the folder in the box
    ui.folderToSave->setText(esiFolder.dirName());
}

void Geac::on_clearFiles_clicked()
{
    // Clear the log
    this->fileDisplayerModel.clearFiles();
    this->clearLog();
    this->display(tr("Files Cleared"));
}

void Geac::on_createEsi_clicked()
{
    // Show the progress Bar
    ui.progressBar->show();
    ui.progressLabel->show();
    // Transmit the requirements to the extractor
    esiExtractor.setRequiredFields(reqThermochemistry, reqHarmonicFrequencies, reqStandardCoordinates, reqHartreeFock);
    // Iterate over the files and convert them
    for(int i=0; i<fileDisplayerModel.rowCount(); i++)
    {
        if (fileDisplayerModel.getRequiredConversion(i))
        {
            QFile file(fileDisplayerModel.getFilePath(i));
            // Retrieve the name of the current file and transmit it to the extractor
            esiExtractor.setInputFile(file);
            // Depending on the state of the destination switch
            if (ui.Button_DedicatedFolder->isChecked())
            {
                // Set a dedicated folder
                esiExtractor.setOutputFolder(esiFolder);
            }
            else if(ui.Button_SameFolder->isChecked())
            {
                // Set the folder of the current file to be the output path
                QString fileDir = file.fileName();
                fileDir.remove(fileDir.lastIndexOf("/"), fileDir.length());
                QDir dir(fileDir);
                esiExtractor.setOutputFolder(dir);
            }
            // Launch the extractor, and transmit him the extension to give to the output file
            esiExtractor.createEsi(ui.esiExtension->text());
            // Display in log
            display(tr("File ") + file.fileName() + tr(" Converted successfully."));
            // set converted state in manager
            fileDisplayerModel.setConverted(i);
            // Update view
            ui.fileDisplayer->viewport()->update();
        }
    }
    // Hide Progress Bar
    ui.progressBar->hide();
    ui.progressLabel->hide();
}

void Geac::on_fileDisplayer_clicked(QModelIndex index)
{
    // Use the Model to change the data upon clicking
    if (fileDisplayerModel.setData(index, true, Qt::EditRole)){
        // Update the view
        ui.fileDisplayer->viewport()->update();
    }
}

void Geac::on_Button_DedicatedFolder_clicked()
{
    // If clicked, this forces the user to enter a valid directory.
    if(ui.folderToSave->text() == "..." || ui.folderToSave->text().isEmpty()){
        ui.SaveFolderSelection->click();
    }
    // Checks if the user has entered a valid directory, if not, we get back to the "same folder" setting
    if(ui.folderToSave->text() == "..." || ui.folderToSave->text().isEmpty()){
        ui.Button_SameFolder->click();
    }
}

void Geac::on_actionEnglish_triggered()
{
    // Translate UI to English
}

void Geac::on_actionFran_ais_triggered()
{
    // Translate UI to French
}

void Geac::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void Geac::readSettings()
{
    // Read Settings
}

void Geac::writeSettings()
{
    // Write Settings
}
