#include <QtGui/QApplication>
#include "geac.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Geac w;
    w.show();

    return a.exec();
}
