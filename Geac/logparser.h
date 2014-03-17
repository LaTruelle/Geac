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

  Emmanuel Nicolas - LogParser.h

    The class LogParser parses a Gaussian log file and extracts several
    information from it such as Thermochemistry, HG Energy, etc.

*/

#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <QString>
#include <QStringList>

#include <checkablefile.h>

class LogParser
{
public:
    LogParser();
    LogParser(CheckableFile &file);
    void setFileToParse(CheckableFile &file);
    void parse();

    QStringList getThermochemistry();
    QStringList getHarmonicFrequencies();
    QStringList getStandardCoordinates();
    QString getHartreeFockEnergy();
    QString getNAtoms();

private:
    QFile *fileToParse;
    QStringList thermochemistry;
    QStringList harmonicFrequencies;
    QStringList standardCoordinates;
    QString hartreeFockEnergy;
    QString nAtoms;

};

#endif // LOGPARSER_H
