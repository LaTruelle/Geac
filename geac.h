#ifndef GEAC_H
#define GEAC_H

#include "ui_geac.h"

class GEAC : public QMainWindow
{
    Q_OBJECT

public:
    explicit GEAC(QWidget *parent = 0);

private:
    Ui::GEAC ui;
};

#endif // GEAC_H
