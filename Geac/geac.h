#ifndef GEAC_H
#define GEAC_H

#include "ui_geac.h"

class Geac : public QMainWindow
{
    Q_OBJECT

public:
    explicit Geac(QWidget *parent = 0);

private:
    Ui::Geac ui;

private slots:
    void on_actionOpen_Folder_triggered();
    void on_actionOpen_File_triggered();
};

#endif // GEAC_H
