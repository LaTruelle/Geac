#ifndef GEAC_H
#define GEAC_H

#include "ui_geac.h"
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QCloseEvent>
#include "filemanager.h"
#include "filemanagerdelegate.h"
#include "esiextractor.h"
#include "processingthread.h"

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

    bool reqThermochemistry;
    bool reqHarmonicFrequencies;
    bool reqStandardCoordinates;
    bool reqHartreeFock;

    EsiExtractor esiExtractor;
    FileManager fileDisplayerModel;
    FileManagerDelegate fileDisplayerDelegate;
    ProcessingThread thread;
    Ui::Geac ui;
    QDir baseFolder;
    QDir esiFolder;
    QFile fileToConvert;
    QFile convertedFile;
    QStringList dirList;

public slots:
    void displayLog(QString string);
    void setProgressBarValue(int i);

private slots:
    void showProgressBar();
    void hideProgressBar();
    void on_actionFran_ais_triggered();
    void on_actionEnglish_triggered();
    void on_Button_DedicatedFolder_clicked();
    void on_fileDisplayer_clicked(QModelIndex index);
    void on_createEsi_clicked();
    void on_clearFiles_clicked();
    void on_SaveFolderSelection_clicked();
    void on_standardCoordinates_stateChanged(int );
    void on_hartreeFock_stateChanged(int );
    void on_thermochemistry_stateChanged(int );
    void on_harmonicFrequencies_stateChanged(int );
    void on_actionOpen_Folder_triggered();
    void on_actionOpen_File_triggered();
};

#endif // GEAC_H
