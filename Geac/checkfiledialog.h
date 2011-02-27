#ifndef CHECKFILEDIALOG_H
#define CHECKFILEDIALOG_H

#include <QFileDialog>
#include <QCheckBox>

class CheckFileDialog : public QFileDialog
{
public:
    CheckFileDialog();
    void setMultipleFilesMode();
    void setDirectoryMode();
    bool getRecursivity();

private:
    QCheckBox *recursive;
    QStringList filters;
};

#endif // CHECKFILEDIALOG_H
