/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2014 - Emmanuel Nicolas

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

#ifndef GEAC_H
#define GEAC_H

#include "ui_geac.h"

#include <QCloseEvent>
#include <QDir>
#include <QFileInfoList>

#include "filemanager.h"
#include "filemanagerdelegate.h"

class Geac : public QMainWindow
{
    Q_OBJECT

public:
    explicit Geac(QWidget *parent = 0);

private:
    void setupFileDisplayer();
    void display(QString string);
    void clearLog();
    void addFilesFromList(QFileInfoList fileNames);
    void readSettings();
    void writeSettings();
    void closeEvent(QCloseEvent *);
    void increaseProgressBarMax();
    void increaseProgressBarValue();

    bool reqThermochemistry;
    bool reqHarmonicFrequencies;
    bool reqStandardCoordinates;
    bool reqHartreeFock;

    FileManager fileDisplayerModel;
    FileManagerDelegate fileDisplayerDelegate;
    Ui::Geac ui;
    QDir baseFolder;
    QDir esiFolder;
    QFile cifOutput;
    QStringList dirList;

public slots:
    void displayLog(QString string);
    void showFileFinished(int id);
    void fileConverted(int id);

private slots:
    void showProgressBar();
    void hideProgressBar();
    void repaintFileDisplayer();
    void on_actionFran_ais_triggered();
    void on_actionEnglish_triggered();
    void on_Button_DedicatedFolder_clicked();
    void on_fileDisplayer_clicked(QModelIndex index);
    void on_createEsi_clicked();
    void on_clearFiles_clicked();
    void on_SaveFolderSelection_clicked();
    void on_standardCoordinates_stateChanged(int);
    void on_hartreeFock_stateChanged(int);
    void on_thermochemistry_stateChanged(int);
    void on_harmonicFrequencies_stateChanged(int);
    void on_actionOpen_Folder_triggered();
    void on_actionOpen_File_triggered();
    void on_actionQuit_triggered();
    void on_Button_CIF_clicked();
};

#endif // GEAC_H
