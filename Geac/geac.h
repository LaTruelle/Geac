#ifndef GEAC_H
#define GEAC_H

#include "ui_geac.h"
#include <QDir>
#include <QFile>
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

    bool reqThermochemistry;
    bool reqHarmonicFrequencies;
    bool reqStandardCoordinates;
    bool reqHartreeFock;

    FileManager fileDisplayerModel;
    FileManagerDelegate fileDisplayerDelegate;
    Ui::Geac ui;
    QDir baseFolder;
    QDir esiFolder;
    QFile fileToConvert;
    QFile convertedFile;

private slots:
    void on_clearFiles_clicked();
    void on_toolButton_clicked();
    void on_standardCoordinates_stateChanged(int );
    void on_hartreeFock_stateChanged(int );
    void on_thermochemistry_stateChanged(int );
    void on_harmonicFrequencies_stateChanged(int );
    void on_actionOpen_Folder_triggered();
    void on_actionOpen_File_triggered();
};

#endif // GEAC_H
