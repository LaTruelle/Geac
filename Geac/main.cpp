#include <QtGui/QApplication>
#include <QTranslator>
#include <QLibraryInfo>
// #include <QtPlugin>
#include "geac.h"

// http://www.qtcentre.org/threads/11532-How-to-add-qsvg/page2
// http://doc.trolltech.com/4.7/plugins-howto.html#static-plugins
// http://www.qtcentre.org/threads/15752-Images-not-shown-in-static-release-exe-(QT4.4.0-commercial-windows)
// http://doc.qt.nokia.com/4.7/qtglobal.html#Q_WS_MAC Preprocessor macros list

// Q_IMPORT_PLUGIN(qsvg)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Setup general app parameters
    QCoreApplication::setApplicationName("Geac");
    QCoreApplication::setOrganizationDomain("sourceforge.net");
    QCoreApplication::setOrganizationName("E Nicolas");

    // Enable translation
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
    QTranslator geacTranslator;
    geacTranslator.load("geac_" + QLocale::system().name());
    app.installTranslator(&geacTranslator);

    // Launch Main Window
    Geac w;
    w.showMaximized();
    return app.exec();
}
