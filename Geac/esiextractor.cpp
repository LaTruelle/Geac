#include "esiextractor.h"
#include <QMessageBox>
#include <iostream>
#include <QTextStream>

EsiExtractor::EsiExtractor()
{
}

EsiExtractor::EsiExtractor(QFile &inputFile)
{
    EsiExtractor::inputFile.setFileName(inputFile.fileName());
    QString fileName = inputFile.fileName();
}

void EsiExtractor::createEsi(QString fileExtension)
{
    QMessageBox msg;
    // We check the existence of the input File
    if(!inputFile.exists())
    {
        msg.setText(QObject::tr("The file ")+inputFile.fileName()+QObject::tr(" does not exist !"));
        msg.exec();
    }
    else{
        // We check if the file can be read
        if (!QFileInfo(inputFile).isReadable())
        {
            msg.setText(QObject::tr("The file ")+inputFile.fileName()+QObject::tr(" cannot be opened !"));
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
            if(QFile(outFile).exists())
            {
               // We have a problem : delete and overwrite ?
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
    outputFile.setFileName(outputFolder.absolutePath() + "/" + outFile);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outputFile);
    out << "toto";
    outputFile.close();
}

void EsiExtractor::setInputFile(QFile &inputFile)
{
    EsiExtractor::inputFile.setFileName(inputFile.fileName());
}

void EsiExtractor::setOutputFolder(QDir &outputFolder)
{
    EsiExtractor::outputFolder.setPath(outputFolder.absolutePath());
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
