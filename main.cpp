#include <QtGui/QApplication>
#include "geac.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GEAC w;
    w.show();
	// Mouahahah
    return a.exec();
}
