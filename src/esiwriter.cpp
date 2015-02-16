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

  Emmanuel Nicolas - esiwriter

    The class esiwriter extracts all necessary elements from a given file to build an ESI.
    -> Harmonic Frequencies
    -> Standard Coordinates (Using NAtoms value)
    -> Thermochemistry (energies, enthalpies)
    -> Hartree Fock Energy

*/

#include "esiwriter.h"
#include <QMessageBox>
#include <QTextStream>

// Define static variables
bool EsiWriter::alwaysOverwrite = false;
bool EsiWriter::neverOverwrite = false;

EsiWriter::EsiWriter()
{
    canWriteFile = false;
}

EsiWriter::EsiWriter(CheckableFile &inputFile)
{
    setInputFile(inputFile);
    canWriteFile = false;
}

void EsiWriter::setExtension(QString extension)
{
    fileExtension = extension;
}

void EsiWriter::createEsi()
{
    checkInputFile();

    if (canWriteFile) {
        writeData();
    }
}

void EsiWriter::writeData()
{
    // Open the file
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    // Setup a QTextStream
    QTextStream out(&outputFile);
    // Add data according to requirements
    /* TODO: Use the QList<Atom> scheme
    if (reqStandardCoordinates)
        out << parser.getStandardCoordinates().join("") << endl;
    if (reqHarmonicFrequencies)
        out << parser.getHarmonicFrequencies().join("") << endl;
    if (reqThermochemistry)
        out << parser.getThermochemistry().join("") << endl;
    if (reqHartreeFock)
        out << parser.getHartreeFockEnergy() << endl;
    */
    // We close the file
    outputFile.close();
    // Emit signal
    emit fileProcessed();
}

void EsiWriter::checkInputFile()
{
    // Include all test about Include file here
    QMessageBox msg;
    // We check the existence of the input File
    if(!inputFile.exists())
    {
        msg.setText(QObject::tr("The file %1 does not exist !").arg(inputFile.fileName()));
        msg.exec();
        // Emit log signal !
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
            // We can setup the outputFile
            QString outFile = inputFile.fileName().remove(0,inputFile.fileName().lastIndexOf("/")+1);
            // --> inputName.log
            outFile.remove(outFile.lastIndexOf("."), outFile.length()-1);
            // --> inputName
            outFile.append(fileExtension);
            // --> inputName_fileExtension
            // We can setup the QFile outputFile
            outputFile.setFileName(outputFolder.absolutePath() + "/" + outFile);
            // We have a proper QFile, we check its existence, and if we can write in the directory
            if(outputFile.exists() && !alwaysOverwrite && !neverOverwrite)
            {
                // We have a problem : Ask for the user to decide
                msg.setText(QObject::tr("The file %1 already exists").arg(outputFile.fileName()));
                msg.setInformativeText(QObject::tr("Do you want to overwrite it ?"));
                msg.setStandardButtons(QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll);
                msg.setDefaultButton(QMessageBox::YesToAll);
                switch (msg.exec())
                {
                case QMessageBox::Yes:
                    // Delete and authorize overwrite
                    QFile(outFile).remove();
                    canWriteFile = true;
                    break;
                case QMessageBox::YesToAll:
                    // Delete file, authorize overwrite and save it for next time
                    QFile(outFile).remove();
                    canWriteFile = true;
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
                canWriteFile = true;
            }
        }
    }
}

void EsiWriter::setInputFile(CheckableFile &inputFile)
{
    EsiWriter::inputFile.setFileName(inputFile.fileName());
}

void EsiWriter::setOutputFolder(QDir &outputFolder)
{
    this->outputFolder.setPath(outputFolder.absolutePath());
}

void EsiWriter::setRequiredFields(bool &thermochemistry,
                                     bool &harmonicFrequencies,
                                     bool &standardCoordinates,
                                     bool &hartreeFockEnergy)
{
    reqThermochemistry = thermochemistry;
    reqHarmonicFrequencies = harmonicFrequencies;
    reqStandardCoordinates = standardCoordinates;
    reqHartreeFock = hartreeFockEnergy;
}

void EsiWriter::setupExtractor(bool &thermochemistry,
                                  bool &harmonicFrequencies,
                                  bool &standardCoordinates,
                                  bool &hartreeFockEnergy,
                                  QDir &outputFolder,
                                  QString extension)
{
    // Setup Fields to save
    setRequiredFields(thermochemistry, harmonicFrequencies, standardCoordinates, hartreeFockEnergy);
    // Set output Folder
    setOutputFolder(outputFolder);
    // Set Extension of ESI
    setExtension(extension);
}
