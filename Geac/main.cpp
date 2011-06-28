#include <QtGui/QApplication>
#include <QTranslator>
#include <QLibraryInfo>
// #include <QtPlugin>
#include "geac.h"

// http://www.qtcentre.org/threads/11532-How-to-add-qsvg/page2
// http://doc.trolltech.com/4.7/plugins-howto.html#static-plugins
// http://www.qtcentre.org/threads/15752-Images-not-shown-in-static-release-exe-(QT4.4.0-commercial-windows)

// Q_IMPORT_PLUGIN(qsvg)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
    QTranslator myappTranslator;
    myappTranslator.load("geac_" + QLocale::system().name());
    app.installTranslator(&myappTranslator);

    Geac w;
    w.showMaximized();
    return app.exec();
}
