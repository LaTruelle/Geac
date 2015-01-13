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

  Emmanuel Nicolas - LogParser.cpp

    The class LogParser parses a Gaussian log file and extracts several
    information from it such as Thermochemistry, HG Energy, etc.

*/

#include "logparser.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

LogParser::LogParser()
{
}

LogParser::LogParser(CheckableFile *file)
{
    fileToParse = file;
}

void LogParser::parse()
{
    fileToParse->open(QIODevice::ReadOnly);
    while(!fileToParse->atEnd())
    {
        QByteArray line = fileToParse->readLine();
        if (line.contains("NAtoms"))
        {
            int natPos = line.indexOf("NAtoms");
            nAtoms = line.right(line.length()-natPos-8).trimmed(); // Removes "NAtoms =" and all spaces
            int spacePos = nAtoms.indexOf(" ");
            nAtoms = nAtoms.left(spacePos+1);
        }
        if (line.contains("Standard orientation") || line.contains("Input orientation"))
        {
            standardCoordinates.clear(); // We empty the list from previous coordinates
            for(int ctr = 1; ctr<= nAtoms.toInt()+5; ctr++)
            {
                standardCoordinates.append(fileToParse->readLine());
            }
        }
        if (line.contains("Gibbs"))
        {
            thermochemistry.clear(); // Empty the list from previous energies
            for(int ctr = 0; ctr<4; ctr++)
            {
                thermochemistry.append(QString(fileToParse->readLine()));
            }
        }
        if (line.contains("Harmonic frequencies"))
        {
            harmonicFrequencies.clear(); // Remove all previous matches (calcall computations for exemple)
            // Retrieve Three Lowest Harmonic Frequencies.
            // Start by reading the header but not save it
            for (int ctr = 1; ctr<=3; ctr++)
            {
                fileToParse->readLine();
            }
            // Then actually save the next 6 lines that contains the Harmonic Frequencies
            for (int ctr = 1; ctr <= 6; ctr++)
            {
                harmonicFrequencies.append(QString(fileToParse->readLine()));
            }
        }
        if (line.contains("SCF Done"))
        {
            hartreeFockEnergy.clear(); // Removes previous definitions
            // Line is of the form  " SCF Done: E(Functional) =   -123.456789    A.U. after n cycles  "
            // Retrieve HF energy.
            int equalPosition = line.indexOf("=");
            hartreeFockEnergy = line.right(line.length() - equalPosition).trimmed();
            int AUposition = hartreeFockEnergy.indexOf("A.U.");
            hartreeFockEnergy = "HF " + hartreeFockEnergy.left(AUposition).trimmed();
        }
    }
    fileToParse->close();
    // Save everything in CheckableFile
    fileToParse->setHarmonicFrequencies(this->getHarmonicFrequencies());
    fileToParse->setThermochemistry(this->getThermochemistry());
    // currentFile->setCoordinates(this->getStandardCoordinates()); // Needs conversion to QList<Atom>
    fileToParse->setHartreeFockEnergy(this->getHartreeFockEnergy());
    fileToParse->setNAtoms(this->getNAtoms());
}

void LogParser::setFileToParse(CheckableFile &file)
{
    fileToParse = &file;
}

QStringList LogParser::getThermochemistry()
{
    return thermochemistry;
}

QStringList LogParser::getHarmonicFrequencies()
{
    return harmonicFrequencies;
}

QStringList LogParser::getStandardCoordinates()
{
    return standardCoordinates;
}

QString LogParser::getHartreeFockEnergy()
{
    return hartreeFockEnergy;
}

QString LogParser::getNAtoms()
{
    return nAtoms;
}
