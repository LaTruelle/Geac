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

  Emmanuel Nicolas - EsiExtractor.h

    The class EsiExtractor extracts all necessary elements from a given file to build an ESI.
    -> Harmonic Frequencies
    -> Standard Coordinates (Using NAtoms value)
    -> Thermochemistry (energies, enthalpies)
    -> Hartree Fock Energy

*/

#ifndef ESIEXTRACTOR_H
#define ESIEXTRACTOR_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>
#include "logparser.h"
#include "checkablefile.h"

class EsiExtractor
{
public:
    EsiExtractor();
    EsiExtractor(CheckableFile &inputFile);
    void setInputFile(CheckableFile &inputFile);
    void setOutputFolder(QDir &outputFolder);
    void setRequiredFields(bool &thermochemistry,
                           bool &harmonicFrequencies,
                           bool &standardCoordinates,
                           bool &hartreeFockEnergy);
    void createEsi();
    void setExtension(QString extension);

private:
    void writeData(QString &outFile);

    bool reqThermochemistry;
    bool reqHarmonicFrequencies;
    bool reqStandardCoordinates;
    bool reqHartreeFock;
    bool alwaysOverwrite;
    bool neverOverwrite;
    LogParser parser;
    QDir outputFolder;
    CheckableFile inputFile;
    QFile outputFile;
    QString fileExtension;
};

#endif // ESIEXTRACTOR_H
