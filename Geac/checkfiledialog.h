#ifndef CHECKFILEDIALOG_H
#define CHECKFILEDIALOG_H

#include <QFileDialog>
#include <QCheckBox>

class CheckFileDialog : public QFileDialog
{
public:
    CheckFileDialog();
    bool getRecursivity();

private:
    QCheckBox *recursive;
};

#endif // CHECKFILEDIALOG_H
