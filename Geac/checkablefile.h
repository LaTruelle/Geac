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

  Emmanuel Nicolas - Checkablefile.h

    The class CheckableFile defines an extension of QFile adding fields
    converted and toConvert with the adequate functions and slots to
    interact with them.

*/

#ifndef CHECKABLEFILE_H
#define CHECKABLEFILE_H

#include <QFile>

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

private:
    bool converted;
    bool toConvert;
    int id;

signals:

public slots:
    void setConversionState(bool boolean);
    void setConversionRequired(bool boolean);
};

#endif // CHECKABLEFILE_H
