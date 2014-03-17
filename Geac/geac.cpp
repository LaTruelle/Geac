/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2012 - Emmanuel Nicolas

  GEAC is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  ---

  Emmanuel Nicolas - Geac.h

    The class Geac defines the main window of the software, putting
    together the file manager, the file processor, a log display, and
    functions to add files or folders of files.
*/

#include "geac.h"
#include <QFileDialog>
#include <QSettings>
#include "checkfiledialog.h"
#include "fileprocessor.h"

Geac::Geac(QWidget *parent) : QMainWindow(parent)
{
    // Setup Model / View / Delegate system
    ui.setupUi(this);
    ui.fileDisplayer->setModel(&fileDisplayerModel);
    ui.fileDisplayer->setItemDelegate(&fileDisplayerDelegate);
    setupFileDisplayer();
    // Connect Log signals to the log displayer
    connect(&fileDisplayerModel, SIGNAL(eventToDisplay(QString)), this, SLOT(displayLog(QString)));
    // Hide Progress Bar and set its max to 0
    ui.progressBar->setMaximum(0);
    hideProgressBar();
    // Read Preferences (previously used folders, state of buttons, etc.)
    readSettings();
    // Start Processing thread
    processingThread.start();
}

void Geac::setupFileDisplayer()
{
    // Set Header Style
    ui.fileDisplayer->horizontalHeader()->setSectionsClickable(false);
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
    ui.fileDisplayer->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch); // As big as possible
    ui.fileDisplayer->setColumnWidth(1,ui.fileDisplayer->horizontalHeader()->height()); // Squares at the end of the table
    ui.fileDisplayer->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui.fileDisplayer->setColumnWidth(2,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui.fileDisplayer->setColumnWidth(3,ui.fileDisplayer->horizontalHeader()->height());
    ui.fileDisplayer->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
}

void Geac::display(QString string)
{
    ui.textDisplay->setPlainText(string + "\n" + ui.textDisplay->toPlainText());
}

void Geac::clearLog()
{
    ui.textDisplay->clear();
}

void Geac::addFilesFromList(QFileInfoList fileNames)
{
    // Retrieve files in the list and add them to model
    int limit = fileNames.count();
    for (int i=0; i<limit; i++)
    {
        CheckableFile *file = new CheckableFile(this);
        file->setFileName(fileNames.takeFirst().absoluteFilePath());
        fileDisplayerModel.addFile(file);
    }
}

void Geac::readSettings()
{
    QSettings settings;
    reqHarmonicFrequencies = settings.value("reqHarmonicFrequencies",false).toBool();
    ui.harmonicFrequencies->setChecked(reqHarmonicFrequencies);
    reqHartreeFock = settings.value("reqHartreeFock",false).toBool();
    ui.hartreeFock->setChecked(reqHartreeFock);
    reqStandardCoordinates = settings.value("reqStandardCoordinates",false).toBool();
    ui.standardCoordinates->setChecked(reqStandardCoordinates);
    reqThermochemistry = settings.value("reqThermochemistry",false).toBool();
    ui.thermochemistry->setChecked(reqThermochemistry);
}

void Geac::writeSettings()
{
    QSettings settings;
    settings.setValue("reqHarmonicFrequencies", reqHarmonicFrequencies);
    settings.setValue("reqHartreeFock",reqHartreeFock);
    settings.setValue("reqStandardCoordinates",reqStandardCoordinates);
    settings.setValue("reqThermochemistry",reqThermochemistry);
}

void Geac::closeEvent(QCloseEvent *event)
 {
    processingThread.quit();
    while (processingThread.isRunning()) {
        // Do Nothing but wait
    }
    writeSettings();
    event->accept();
 }

void Geac::increaseProgressBarMax(){
    // Add 1 to the max --> serves as a counter for number of files
    ui.progressBar->setMaximum(ui.progressBar->maximum()+1);
    // Show the progress bar
    showProgressBar();
}

void Geac::increaseProgressBarValue(){
    // Increase the value of one
    ui.progressBar->setValue(ui.progressBar->value()+1);
    // We check if it was the last file to process, in which case we hide the progress bar.
    if(ui.progressBar->value() == ui.progressBar->maximum()){
        hideProgressBar();
    }
}

void Geac::displayLog(QString string)
{
    display(string);
}

void Geac::showFileFinished(int id)
{
    // Retrieve the name of the Finished file according to the id
    CheckableFile *file = fileDisplayerModel.getFileById(id);
    // Set its conversion state
    file->setConversionState(true);
    // Display the right thing in the log
    display(tr("File %1 converted").arg(file->displayName()));
    // Increment the progress bar
    this->increaseProgressBarValue();
}

void Geac::showProgressBar()
{
    // Show the progress Bar
    ui.progressBar->show();
    ui.progressLabel->show();
}

void Geac::hideProgressBar()
{
    // Hide Progress Bar
    ui.progressBar->hide();
    ui.progressLabel->hide();
}

void Geac::on_actionFran_ais_triggered()
{
    // Translate UI to French
}

void Geac::on_actionEnglish_triggered()
{
    // Translate UI to English
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

void Geac::on_fileDisplayer_clicked(QModelIndex index)
{
    // Use the Model to change the data upon clicking
    if (fileDisplayerModel.setData(index, true, Qt::EditRole)){
        // Update the view
        ui.fileDisplayer->viewport()->update();
    }
}

void Geac::on_createEsi_clicked()
{
    // Add files to thread, and launch their conversion
    for(int i=0; i<fileDisplayerModel.rowCount(); i++)
    {
        // Check if the file needs to be converted
        if(fileDisplayerModel.getFile(i).getConversionRequired())
        {
            // Define a File Processor for the file i
            FileProcessor *processor = new FileProcessor(fileDisplayerModel.getFile(i));
            // Connect the processor signal to the adequate slot
            connect(processor, SIGNAL(fileProcessed(int)), SLOT(showFileFinished(int)));

            // Setup Processor according to the dedicated folder
            if (ui.Button_DedicatedFolder->isChecked())
            {
                // Set a dedicated folder
                processor->setupProcessor(reqThermochemistry,
                                          reqHarmonicFrequencies,
                                          reqStandardCoordinates,
                                          reqHartreeFock,
                                          esiFolder,
                                          ui.esiExtension->text());
            }
            else if(ui.Button_SameFolder->isChecked())
            {
                // Set the folder of the current file to be the output path
                QString fileDir = processor->getFileName();
                fileDir.remove(fileDir.lastIndexOf("/"), fileDir.length());
                QDir dir(fileDir);
                processor->setupProcessor(reqThermochemistry,
                                          reqHarmonicFrequencies,
                                          reqStandardCoordinates,
                                          reqHartreeFock,
                                          dir,
                                          ui.esiExtension->text());
            }
            // Move the file processor to the processing thread
            processor->moveToThread(&processingThread);
            // Increase the progress bar value (and show it doing this)
            increaseProgressBarMax();
            // Start the conversion
            processor->convertFile();
        }
    }
}

void Geac::on_clearFiles_clicked()
{
    // Clear the log
    this->fileDisplayerModel.clearFiles();
    this->clearLog();
    this->display(tr("Files Cleared"));
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

void Geac::on_standardCoordinates_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqStandardCoordinates = false;
    else
        reqStandardCoordinates = true;
}

void Geac::on_hartreeFock_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqHartreeFock = false;
    else
        reqHartreeFock = true;
}

void Geac::on_thermochemistry_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqThermochemistry = false;
    else
        reqThermochemistry = true;
}

void Geac::on_harmonicFrequencies_stateChanged(int state)
{
    if(state == Qt::Unchecked)
        reqHarmonicFrequencies = false;
    else
        reqHarmonicFrequencies = true;
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

void Geac::on_actionQuit_triggered()
{
    emit this->close();
}
