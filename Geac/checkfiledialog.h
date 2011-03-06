#ifndef CHECKFILEDIALOG_H
#define CHECKFILEDIALOG_H

#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>

class CheckFileDialog : public QFileDialog
{
public:
    enum fileFilter{
        all,
        outAndLog,
        out,
        log
    };
    CheckFileDialog();
    void setMultipleFilesMode();
    void setDirectoryMode();
    bool getRecursivity();
    int getFileFilter();

private:
    QCheckBox *recursive;
    QComboBox *fileFilterBox;
    QStringList filters;
};

#endif // CHECKFILEDIALOG_H
