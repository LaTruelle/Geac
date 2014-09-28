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
