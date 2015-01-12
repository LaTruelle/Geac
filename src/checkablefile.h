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

  Emmanuel Nicolas - Checkablefile.h

    The class CheckableFile defines an extension of QFile adding fields
    converted and toConvert with the adequate functions and slots to
    interact with them.

*/

#ifndef CHECKABLEFILE_H
#define CHECKABLEFILE_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QList>

struct Atom{
    QString element;
    int x;
    int y;
    int z;
};

class CheckableFile : public QFile
{
    Q_OBJECT
public:
    explicit CheckableFile(QObject *parent);
    CheckableFile(CheckableFile & file);
    CheckableFile();
    bool getConversionState();
    bool getConversionRequired();
    void setId(int i);
    int getId();
    QString displayName();

    QString getNAtoms() const;
    void setNAtoms(const QString &value);

    QString getHartreeFockEnergy() const;
    void setHartreeFockEnergy(const QString &value);

    QStringList getThermochemistry() const;
    void setThermochemistry(const QStringList &value);

    QStringList getHarmonicFrequencies() const;
    void setHarmonicFrequencies(const QStringList &value);

    bool getDataExtracted() const;
    void setDataExtracted(bool value);

    QList<Atom> getCoordinates() const;
    void setCoordinates(const QList<Atom> &value);

private:
    bool converted;
    bool toConvert;
    bool dataExtracted;
    int id;
    QString nAtoms;
    QString hartreeFockEnergy;
    QStringList thermochemistry;
    QStringList harmonicFrequencies;
    QList<Atom> coordinates;

signals:

public slots:
    void setConversionState(bool boolean);
    void setConversionRequired(bool boolean);
};

#endif // CHECKABLEFILE_H
