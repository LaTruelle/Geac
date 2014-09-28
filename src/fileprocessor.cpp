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

  Emmanuel Nicolas - FileProcessor.cpp

    The class FileProcessor links a File and an EsiExtractor and permits
    the extraction of needed information.
    It emits signals when a file is processed, and eventually some log
    events.

*/

#include "fileprocessor.h"

FileProcessor::FileProcessor(CheckableFile &inputFile)
{
    file.setFileName(inputFile.fileName());
    id = inputFile.getId();
    esiExtractor.setInputFile(file);
    connect(&esiExtractor, SIGNAL(fileProcessed()), this, SLOT(transmitProgress()));
}

FileProcessor::~FileProcessor()
{
}

void FileProcessor::setupProcessor(bool &thermoChem,
                                   bool &harmFreq,
                                   bool &stdCoord,
                                   bool &hfEnergy,
                                   QDir &outFolder,
                                   QString fileExt
                                   )
{
    // Transmit necessary data directly to the extractor
    esiExtractor.setupExtractor(thermoChem,
                                harmFreq,
                                stdCoord,
                                hfEnergy,
                                outFolder,
                                fileExt);
}

void FileProcessor::convertFile()
{
    // Tell the extractor to build the ESI
    esiExtractor.createEsi();
}

QString FileProcessor::getFileName(){
    return file.fileName();
}

void FileProcessor::transmitProgress(){
    emit fileProcessed(id);
}
