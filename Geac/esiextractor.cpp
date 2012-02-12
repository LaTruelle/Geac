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

  Emmanuel Nicolas - EsiExtractor.cpp

    The class EsiExtractor extracts all necessary elements from a given file to build an ESI.
    -> Harmonic Frequencies
    -> Standard Coordinates (Using NAtoms value)
    -> Thermochemistry (energies, enthalpies)
    -> Hartree Fock Energy

*/

#include "esiextractor.h"
#include <QMessageBox>
#include <iostream>
#include <QTextStream>

EsiExtractor::EsiExtractor()
{
    alwaysOverwrite = false;
    neverOverwrite = false;
}

EsiExtractor::EsiExtractor(CheckableFile &inputFile)
{
    EsiExtractor::inputFile.setFileName(inputFile.fileName());
    alwaysOverwrite = false;
    neverOverwrite = false;
}

void EsiExtractor::setExtension(QString extension)
{
    fileExtension.fromAscii(extension.toAscii());
}

void EsiExtractor::createEsi()
{
    QMessageBox msg;
    // We check the existence of the input File
    if(!inputFile.exists())
    {
        msg.setText(QObject::tr("The file %1 does not exist !").arg(inputFile.fileName()));
        msg.exec();
    }
    else{
        // We check if the file can be read
        if (!QFileInfo(inputFile).isReadable())
        {
            msg.setText(QObject::tr("The file %1 cannot be opened !").arg(inputFile.fileName()));
            msg.exec();
        }
        else
        {
            // The file is a priori valid: exists and readable
            parser.setFileToParse(inputFile);
            parser.parse();
            // The input file is parsed, we set up the output File
            QString outFile = inputFile.fileName().remove(0,inputFile.fileName().lastIndexOf(QDir::separator())+1);
            // --> inputName.log
            outFile.remove(outFile.lastIndexOf("."), outFile.length()-1);
            // --> inputName
            outFile.append(fileExtension);
            // --> inputName_fileExtension
            // We have a proper file Name, we check its existence, and if we can write in the directory
            if(QFile(outFile).exists() && !alwaysOverwrite && !neverOverwrite)
            {
                // We have a problem : Ask for the user to decide
                msg.setText(QObject::tr("the file %1 already exists").arg(inputFile.fileName()));
                msg.setInformativeText(QObject::tr("Do you want to overwrite it ?"));
                msg.setStandardButtons(QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll);
                msg.setDefaultButton(QMessageBox::YesToAll);
                switch (msg.exec())
                {
                case QMessageBox::Yes:
                    // Delete and Overwrite
                    QFile(outFile).remove();
                    writeData(outFile);
                    break;
                case QMessageBox::YesToAll:
                    // Delete and Overwrite and save it for next time
                    QFile(outFile).remove();
                    writeData(outFile);
                    alwaysOverwrite = true;
                    break;
                case QMessageBox::No:
                    // Do Nothing
                    break;
                case QMessageBox::NoToAll:
                    // Do Nothing But Save it !
                    neverOverwrite = true;
                    break;
                }
            }
            else
            {
                writeData(outFile);
            }
        }
    }
}

void EsiExtractor::writeData(QString &outFile)
{
    // Set the name with correct path
    outputFile.setFileName(outputFolder.absolutePath() + "/" + outFile);
    // Open the file
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    // Setup a QTextStream
    QTextStream out(&outputFile);
    // Add data according to requirements
    // TODO: insert headers
    if (reqStandardCoordinates)
        out << parser.getStandardCoordinates().join("") << endl;
    if (reqHarmonicFrequencies)
        out << parser.getHarmonicFrequencies().join("") << endl;
    if (reqThermochemistry)
        out << parser.getThermochemistry().join("") << endl;
    if (reqHartreeFock)
        out << parser.getHartreeFockEnergy() << endl;
    // We close the file
    outputFile.close();
}

void EsiExtractor::setInputFile(CheckableFile &inputFile)
{
    EsiExtractor::inputFile.setFileName(inputFile.fileName());
}

void EsiExtractor::setOutputFolder(QDir &outputFolder)
{
    this->outputFolder.setPath(outputFolder.absolutePath());
    qDebug("ESIin EE.cpp :"+this->outputFolder.absolutePath().toAscii());
}

void EsiExtractor::setRequiredFields(bool &thermochemistry,
                                     bool &harmonicFrequencies,
                                     bool &standardCoordinates,
                                     bool &hartreeFockEnergy)
{
    reqThermochemistry = thermochemistry;
    reqHarmonicFrequencies = harmonicFrequencies;
    reqStandardCoordinates = standardCoordinates;
    reqHartreeFock = hartreeFockEnergy;
}
