/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2014 - Emmanuel Nicolas

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

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "geac.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Setup general app parameters
    QCoreApplication::setApplicationName("Geac");
    QCoreApplication::setOrganizationDomain("github.com");
    QCoreApplication::setOrganizationName("Emmanuel Nicolas");

    // Enable translation
    QTranslator geacTranslator;
    geacTranslator.load("geac_" + QLocale::system().name().section('_',0,0),":/translations/");
    app.installTranslator(&geacTranslator);

    // Launch Main Window
    Geac w;
    w.showMaximized();
    return app.exec();
}
