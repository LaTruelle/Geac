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
    this->initPeriodicTable();
}

LogParser::LogParser(CheckableFile *file)
{
    fileToParse = file;
    this->initPeriodicTable();
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
            // Skip header
            for (int ctr = 1; ctr<=4; ctr++)
            {
                fileToParse->readLine();
            }
            QString coordLine = fileToParse->readLine();
            while (!coordLine.contains("------------")) // i.e. not at the end of the table
            {
                // Read current line, of the form
                // "N  AtomicNumber 0 Xcoord Ycoord Zcoord"
                qDebug() << coordLine;
                // Split the string acoording to previously described pattern
                QStringList list = coordLine.trimmed().split(QRegExp("\\s+"));
                Atom atom;
                // TODO Check for case of atoms Bq and X (Ghost and Dummy atoms)
                // TODO emit error if element is not a float, to avoid crash for wrong casting.
                atom.element = periodicTable.value(list.at(1).toInt());
                atom.x = list.at(3).toFloat();
                atom.y = list.at(4).toFloat();
                atom.z = list.at(5).toFloat();
                standardCoordinates.append(atom);
                coordLine = fileToParse->readLine();
            }
            // Update nAtoms with length of coordinates
            nAtoms = standardCoordinates.size();
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
    // TODO: Check that all data is there. (And do something with it!)
    // (like some warning, or wrong conversion state, something)
    // Save everything in CheckableFile
    fileToParse->setHarmonicFrequencies(this->getHarmonicFrequencies());
    fileToParse->setThermochemistry(this->getThermochemistry());
    fileToParse->setCoordinates(this->getStandardCoordinates());
    fileToParse->setHartreeFockEnergy(this->getHartreeFockEnergy());
    fileToParse->setNAtoms(this->getNAtoms());
    fileToParse->setConversionState(true);
}

void LogParser::setFileToParse(CheckableFile &file)
{
    fileToParse = &file;
}

QList<Atom> LogParser::getStandardCoordinates() const
{
    return standardCoordinates;
}

void LogParser::setStandardCoordinates(const QList<Atom> &value)
{
    standardCoordinates = value;
}

QStringList LogParser::getThermochemistry() const
{
    return thermochemistry;
}

void LogParser::setThermochemistry(const QStringList &value)
{
    thermochemistry = value;
}

QStringList LogParser::getHarmonicFrequencies() const
{
    return harmonicFrequencies;
}

void LogParser::setHarmonicFrequencies(const QStringList &value)
{
    harmonicFrequencies = value;
}

QString LogParser::getHartreeFockEnergy() const
{
    return hartreeFockEnergy;
}

void LogParser::setHartreeFockEnergy(const QString &value)
{
    hartreeFockEnergy = value;
}

QString LogParser::getNAtoms() const
{
    return nAtoms;
}

void LogParser::setNAtoms(const QString &value)
{
    nAtoms = value;
}

void LogParser::initPeriodicTable()
{
    // Fills the QHash containing the periodic table
    periodicTable.insert(1,"H");
    periodicTable.insert(2,"He");
    periodicTable.insert(3,"Li");
    periodicTable.insert(4,"Be");
    periodicTable.insert(5,"B");
    periodicTable.insert(6,"C");
    periodicTable.insert(7,"N");
    periodicTable.insert(8,"O");
    periodicTable.insert(9,"F");
    periodicTable.insert(10,"Ne");
    periodicTable.insert(11,"Na");
    periodicTable.insert(12,"Mg");
    periodicTable.insert(13,"Al");
    periodicTable.insert(14,"Si");
    periodicTable.insert(15,"P");
    periodicTable.insert(16,"S");
    periodicTable.insert(17,"Cl");
    periodicTable.insert(18,"Ar");
    periodicTable.insert(19,"K");
    periodicTable.insert(20,"Ca");
    periodicTable.insert(21,"Sc");
    periodicTable.insert(22,"Ti");
    periodicTable.insert(23,"V");
    periodicTable.insert(24,"Cr");
    periodicTable.insert(25,"Mn");
    periodicTable.insert(26,"Fe");
    periodicTable.insert(27,"Co");
    periodicTable.insert(28,"Ni");
    periodicTable.insert(29,"Cu");
    periodicTable.insert(30,"Zn");
    periodicTable.insert(31,"Ga");
    periodicTable.insert(32,"Ge");
    periodicTable.insert(33,"As");
    periodicTable.insert(34,"Se");
    periodicTable.insert(35,"Br");
    periodicTable.insert(36,"Kr");
    periodicTable.insert(37,"Rb");
    periodicTable.insert(38,"Sr");
    periodicTable.insert(39,"Y");
    periodicTable.insert(40,"Zr");
    periodicTable.insert(41,"Nb");
    periodicTable.insert(42,"Mo");
    periodicTable.insert(43,"Tc");
    periodicTable.insert(44,"Ru");
    periodicTable.insert(45,"Rh");
    periodicTable.insert(46,"Pd");
    periodicTable.insert(47,"Ag");
    periodicTable.insert(48,"Cd");
    periodicTable.insert(49,"In");
    periodicTable.insert(50,"Sn");
    periodicTable.insert(51,"Sb");
    periodicTable.insert(52,"Te");
    periodicTable.insert(53,"I");
    periodicTable.insert(54,"Xe");
    periodicTable.insert(55,"Cs");
    periodicTable.insert(56,"Ba");
    periodicTable.insert(57,"La");
    periodicTable.insert(58,"Ce");
    periodicTable.insert(59,"Pr");
    periodicTable.insert(60,"Nd");
    periodicTable.insert(61,"Pm");
    periodicTable.insert(62,"Sm");
    periodicTable.insert(63,"Eu");
    periodicTable.insert(64,"Gd");
    periodicTable.insert(65,"Tb");
    periodicTable.insert(66,"Dy");
    periodicTable.insert(67,"Ho");
    periodicTable.insert(68,"Er");
    periodicTable.insert(69,"Tm");
    periodicTable.insert(70,"Yb");
    periodicTable.insert(71,"Lu");
    periodicTable.insert(72,"Hf");
    periodicTable.insert(73,"Ta");
    periodicTable.insert(74,"W");
    periodicTable.insert(75,"Re");
    periodicTable.insert(76,"Os");
    periodicTable.insert(77,"Ir");
    periodicTable.insert(78,"Pt");
    periodicTable.insert(79,"Au");
    periodicTable.insert(80,"Hg");
    periodicTable.insert(81,"Tl");
    periodicTable.insert(82,"Pb");
    periodicTable.insert(83,"Bi");
    periodicTable.insert(84,"Po");
    periodicTable.insert(85,"At");
    periodicTable.insert(86,"Rn");
    periodicTable.insert(87,"Fr");
    periodicTable.insert(88,"Ra");
    periodicTable.insert(89,"Ac");
    periodicTable.insert(90,"Th");
    periodicTable.insert(91,"Pa");
    periodicTable.insert(92,"U");
    periodicTable.insert(93,"Np");
    periodicTable.insert(94,"Pu");
    periodicTable.insert(95,"Am");
    periodicTable.insert(96,"Cm");
    periodicTable.insert(97,"Bk");
    periodicTable.insert(98,"Cf");
    periodicTable.insert(99,"Es");
    periodicTable.insert(100,"Fm");
    periodicTable.insert(101,"Md");
    periodicTable.insert(102,"No");
    periodicTable.insert(103,"Lr");
    periodicTable.insert(104,"Rf");
    periodicTable.insert(105,"Db");
    periodicTable.insert(106,"Sg");
    periodicTable.insert(107,"Bh");
    periodicTable.insert(108,"Hs");
    periodicTable.insert(109,"Mt");
    periodicTable.insert(110,"Ds");
    periodicTable.insert(111,"Rg");
    periodicTable.insert(112,"Cn");
    periodicTable.insert(113,"Uut");
    periodicTable.insert(114,"Fl");
    periodicTable.insert(115,"Uup");
    periodicTable.insert(116,"Lv");
    periodicTable.insert(117,"Uus");
    periodicTable.insert(118,"Uuo");
}
