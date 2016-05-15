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
#include <QDebug>
#include <QDir>

CheckableFile::CheckableFile(QObject *parent) : QFile(parent)
{
    converted = false;
    toConvert = true;
}

CheckableFile::CheckableFile() : QFile()
{
    // Nothing to do
}

CheckableFile::CheckableFile(const CheckableFile &file) : QFile(file.fileName())
{
    converted = file.getConversionState();
    toConvert = file.getConversionRequired();
    dataExtracted = file.getDataExtracted();
    nAtoms = file.getNAtoms();
    hartreeFockEnergy = file.getHartreeFockEnergy();
    harmonicFrequencies = file.getHarmonicFrequencies();
    thermochemistry = file.getThermochemistry();
    coordinates = file.getCoordinates();
}

bool CheckableFile::getConversionRequired() const
{
    return toConvert;
}

bool CheckableFile::getConversionState() const
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

QString CheckableFile::displayName()
{
    return this->fileName().remove(
        0, this->fileName().lastIndexOf(QDir::separator()) + 1);
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

QList<QStringList> CheckableFile::getXYZCoordinates() const
{
    QList<QStringList> XYZcoordinates;
    for (int line = 0; line < nAtoms.toInt(); ++line) {
        // Add line to coordinates list
        QString element = coordinates.at(line).element;
        QString x = QString::number(coordinates.at(line).x, 'f', 8);
        QString y = QString::number(coordinates.at(line).y, 'f', 8);
        QString z = QString::number(coordinates.at(line).z, 'f', 8);
        QStringList stringList;
        stringList.append(element);
        stringList.append(x);
        stringList.append(y);
        stringList.append(z);
        XYZcoordinates.append(stringList);
    }
    return XYZcoordinates;
}

QDataStream &operator<<(QDataStream &stream, CheckableFile *const &file)
{
    stream << file->fileName();
    stream << file->getConversionState();
    stream << file->getConversionRequired();
    stream << file->getDataExtracted();
    stream << file->getNAtoms();
    stream << file->getHartreeFockEnergy();
    QStringList thermochemistry = file->getThermochemistry();
    stream << thermochemistry.size();
    foreach (QString string, thermochemistry) {
        stream << string;
    }
    QStringList harmonicFrequencies = file->getHarmonicFrequencies();
    stream << harmonicFrequencies.size();
    foreach (QString string, harmonicFrequencies) {
        stream << string;
    }
    QList<Atom> coordinates = file->getCoordinates();
    stream << coordinates.size();
    foreach (Atom atom, coordinates) {
        stream << atom.element;
        stream << atom.x;
        stream << atom.y;
        stream << atom.z;
    }

    return stream;
}

QDataStream &operator>>(QDataStream &stream, CheckableFile *&file)
{
    QString fileName;
    bool conversionState;
    bool conversionRequired;
    bool dataExtracted;
    QString NAtoms;
    QString hartreeFockEnergy;
    int thermoChemistrySize;
    QStringList thermoChemistry;
    int harmonicFrequenciesSize;
    QStringList harmonicFrequencies;
    int coordinatesSize;
    QList<Atom> coordinates;

    stream >> fileName;
    stream >> conversionState;
    stream >> conversionRequired;
    stream >> dataExtracted;
    stream >> NAtoms;
    stream >> hartreeFockEnergy;
    stream >> thermoChemistrySize;
    for (int i = 0; i < thermoChemistrySize; ++i) {
        QString string;
        stream >> string;
        thermoChemistry.append(string);
    }
    stream >> harmonicFrequenciesSize;
    for (int i = 0; i < harmonicFrequenciesSize; ++i) {
        QString string;
        stream >> string;
        harmonicFrequencies.append(string);
    }
    stream >> coordinatesSize;
    for (int i = 0; i < coordinatesSize; ++i) {
        Atom atom;
        stream >> atom.element;
        stream >> atom.x;
        stream >> atom.y;
        stream >> atom.z;
        coordinates.append(atom);
    }

    file->setFileName(fileName);
    file->setConversionState(conversionState);
    file->setConversionRequired(conversionRequired);
    file->setDataExtracted(dataExtracted);
    file->setNAtoms(NAtoms);
    file->setHartreeFockEnergy(hartreeFockEnergy);
    file->setThermochemistry(thermoChemistry);
    file->setHarmonicFrequencies(harmonicFrequencies);
    file->setCoordinates(coordinates);

    return stream;
}
