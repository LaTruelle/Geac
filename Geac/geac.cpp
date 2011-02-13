#include "geac.h"

Geac::Geac(QWidget *parent) :
    QMainWindow(parent){
    ui.setupUi(this);
}

void Geac::on_actionOpen_File_triggered()
{
    // Open File Dialog to select File --> With filters (or without)
}

void Geac::on_actionOpen_Folder_triggered()
{
    // Open File Dialog to select Folder
    //    --> With tick for subfolders and recursively fetching all files or no
    //    -->
}
