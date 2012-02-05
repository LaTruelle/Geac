/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2012 - Emmanuel Nicolas

  GEAC is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  ---

  Emmanuel Nicolas - Main.cpp

    The main class that is launched, defining a QApplication, translators,
    and setting up the main Geac window.

*/

#include <QtGui/QApplication>
#include <QTranslator>
#include <QLibraryInfo>
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
    QCoreApplication::setOrganizationName("Emmanuel Nicolas");

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
