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

  Emmanuel Nicolas - FileProcessor.h

    The class FileProcessor links a File and an EsiExtractor and permits
    the extraction of needed information.
    It emits signals when a file is processed, and eventually some log
    events.

*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>
#include <QDir>
#include <QString>

#include "esiextractor.h"
#include "checkablefile.h"

class FileProcessor : public QObject
{
    Q_OBJECT

public:
    FileProcessor(CheckableFile &inputFile);
    ~FileProcessor();
    void convertFile();
    void setupProcessor(bool &thermoChem,
                        bool &harmFreq,
                        bool &stdCoord,
                        bool &hfEnergy,
                        QDir &outFolder,
                        QString fileExt
                        );
    QString getFileName();

private:
    CheckableFile file;
    EsiExtractor esiExtractor;
    int id;

signals:
    void fileProcessed(int id);
    void logEvent(QString string);

private slots:
    void transmitProgress();

};

#endif // FILEPROCESSOR_H
