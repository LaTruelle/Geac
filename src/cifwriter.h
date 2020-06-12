/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2020 - Emmanuel Nicolas

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

  Emmanuel Nicolas - CifWriter

*/

#ifndef CIFWRITER_H
#define CIFWRITER_H

#include "checkablefile.h"
#include <QList>
#include <QObject>

class CifWriter : public QObject
{
    Q_OBJECT
public:
    CifWriter();
    void addFiletoList(CheckableFile file);
    void addListofFiles(QList<CheckableFile *> list);
    void setOutputFile(QFile &file);
    void createCif();

signals:
    void fileProcessed(QString fileName);

private:
    QList<CheckableFile *> files;
    QFile outputFile;
};

#endif // CIFWRITER_H
