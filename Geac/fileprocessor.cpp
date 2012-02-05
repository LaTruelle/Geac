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

  Emmanuel Nicolas - FileProcessor.cpp

    The class FileProcessor links a File and an EsiExtractor and permits
    the extraction of needed information.
    It emits signals when a file is processed, and eventually some log
    events.

*/

#include "fileprocessor.h"
#include <iostream>

FileProcessor::FileProcessor(QString fileName)
{
    file.setFileName(fileName);
}

FileProcessor::~FileProcessor()
{
}

void FileProcessor::setupProcessor(bool &thermoChem,
                                   bool &harmFreq,
                                   bool &stdCoord,
                                   bool &hfEnergy,
                                   QDir &outFolder,
                                   QString &fileExt
                                   )
{
    // transmit necessary data directly to the extractor
    esiExtractor.setRequiredFields(thermoChem, harmFreq, stdCoord, hfEnergy);
    esiExtractor.setOutputFolder(outFolder);
    esiExtractor.setExtension(fileExt);
}

void FileProcessor::convertFile()
{
    // convert File
}
