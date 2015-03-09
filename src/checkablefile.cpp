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

  Emmanuel Nicolas - Checkablefile.cpp

    The class CheckableFile defines an extension of QFile adding fields
    converted and toConvert with the adequate functions and slots to
    interact with them.

*/

#include "checkablefile.h"
#include <QDir>

CheckableFile::CheckableFile(QObject *parent) :
    QFile(parent)
{
    converted = false;
    toConvert = true;
}

CheckableFile::CheckableFile() :
    QFile()
{
    // Nothing to do
}

CheckableFile::CheckableFile(CheckableFile & file) :
    QFile(file.fileName())
{
    converted = file.getConversionState();
    toConvert = file.getConversionRequired();
    id = file.getId();
    dataExtracted = file.getDataExtracted();
    nAtoms = file.getNAtoms();
    hartreeFockEnergy = file.getHartreeFockEnergy();
    harmonicFrequencies = file.getHarmonicFrequencies();
    thermochemistry = file.getThermochemistry();
    coordinates = file.getCoordinates();
}

bool CheckableFile::getConversionRequired()
{
    return toConvert;
}

bool CheckableFile::getConversionState()
{
    return converted;
}

void CheckableFile::setConversionState(bool boolean)
{
    converted = boolean;
}

void CheckableFile::setConversionRequired(bool boolean)
{
    toConvert = boolean;
}

void CheckableFile::setId(int i)
{
    id = i;
}

int CheckableFile::getId()
{
    return id;
}

QString CheckableFile::displayName()
{
    return this->fileName().remove(0,this->fileName().lastIndexOf(QDir::separator())+1);
}

QString CheckableFile::getNAtoms() const
{
    return nAtoms;
}

void CheckableFile::setNAtoms(const QString &value)
{
    nAtoms = value;
}

QString CheckableFile::getHartreeFockEnergy() const
{
    return hartreeFockEnergy;
}

void CheckableFile::setHartreeFockEnergy(const QString &value)
{
    hartreeFockEnergy = value;
}

QStringList CheckableFile::getThermochemistry() const
{
    return thermochemistry;
}

void CheckableFile::setThermochemistry(const QStringList &value)
{
    thermochemistry = value;
}

QStringList CheckableFile::getHarmonicFrequencies() const
{
    return harmonicFrequencies;
}

void CheckableFile::setHarmonicFrequencies(const QStringList &value)
{
    harmonicFrequencies = value;
}

bool CheckableFile::getDataExtracted() const
{
    return dataExtracted;
}

void CheckableFile::setDataExtracted(bool value)
{
    dataExtracted = value;
}

QList<Atom> CheckableFile::getCoordinates() const
{
    return coordinates;
}

void CheckableFile::setCoordinates(const QList<Atom> &value)
{
    coordinates = value;
}

QList<QStringList> CheckableFile::getXYZCoordinates()
{
    // TODO Return XYZ coordinates
    QList<QStringList> XYZcoordinates;
    for (int line = 0; line < nAtoms.toInt(); ++line) {
        // Add line to coordinates list
        QString element = coordinates.at(line).element;
        QString x = QString::number(coordinates.at(line).x,'f',8);
        QString y = QString::number(coordinates.at(line).y,'f',8);
        QString z = QString::number(coordinates.at(line).z,'f',8);
        QStringList stringList;
        stringList.append(element);
        stringList.append(x);
        stringList.append(y);
        stringList.append(z);
        XYZcoordinates.append(stringList);
    }
    return XYZcoordinates;
}
