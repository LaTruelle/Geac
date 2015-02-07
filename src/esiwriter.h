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

  Emmanuel Nicolas - EsiWriter
    The class EsiWriter extracts all necessary elements from a given file to build an ESI.
    -> Harmonic Frequencies
    -> Standard Coordinates (Using NAtoms value)
    -> Thermochemistry (energies, enthalpies)
    -> Hartree Fock Energy

*/

#ifndef ESIWRITER_H
#define ESIWRITER_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>
#include "logparser.h"
#include "checkablefile.h"

class EsiWriter : public QObject
{
    Q_OBJECT

public:
    EsiWriter();
    EsiWriter(CheckableFile &inputFile);
    void setInputFile(CheckableFile &inputFile);
    void setOutputFolder(QDir &outputFolder);
    void setRequiredFields(bool &thermochemistry,
                           bool &harmonicFrequencies,
                           bool &standardCoordinates,
                           bool &hartreeFockEnergy);
    void createEsi();
    void setExtension(QString extension);
    void setupExtractor(bool &thermochemistry,
                        bool &harmonicFrequencies,
                        bool &standardCoordinates,
                        bool &hartreeFockEnergy,
                        QDir &outputFolder,
                        QString extension);

signals:
    void fileProcessed();

private:
    void writeData();
    void checkInputFile();
    bool reqThermochemistry;
    bool reqHarmonicFrequencies;
    bool reqStandardCoordinates;
    bool reqHartreeFock;
    bool canWriteFile;
    LogParser parser;
    QDir outputFolder;
    CheckableFile inputFile;
    QFile outputFile;
    QString fileExtension;

    static bool alwaysOverwrite;
    static bool neverOverwrite;

};

#endif // ESIWRITER_H
