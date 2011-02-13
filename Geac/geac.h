#ifndef GEAC_H
#define GEAC_H

#include "ui_geac.h"
#include <QDir>
#include <QFile>

class Geac : public QMainWindow
{
    Q_OBJECT

public:
    explicit Geac(QWidget *parent = 0);

private:
    Ui::Geac ui;
    QDir baseFolder;
    QFile fileToConvert;
    QFile convertedFile;

private slots:
    void on_actionOpen_Folder_triggered();
    void on_actionOpen_File_triggered();
};

#endif // GEAC_H
