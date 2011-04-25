#include "esiextractor.h"

EsiExtractor::EsiExtractor()
{
}

EsiExtractor::EsiExtractor(QFile &inputFile)
{
    EsiExtractor::inputFile.setFileName(inputFile.fileName());
    QString fileName = inputFile.fileName();
}

EsiExtractor::EsiExtractor(QFile &inputFile, QFile &outputFile)
{
    EsiExtractor::inputFile.setFileName(inputFile.fileName());
    EsiExtractor::outputFile.setFileName(outputFile.fileName());
}

void EsiExtractor::createEsi(QString fileExtension)
{
    parser.setFileToParse(inputFile);
    if(outputFile.fileName()!=inputFile.fileName() && !outputFile.exists())
    {
        // The output file does not exist, and does not have the same file name than the input, and is not empty
        // We can use it.
        //parser.
    }
    //    EsiExtractor::outputFile.fileName() = fileName.insert(fileName.length()-4, "_esi"); --> Transfer in parse()
    //    this->createParser(); --> idem
    parser.parse();
}

void EsiExtractor::setInputFile(QFile &inputFile)
{
    EsiExtractor::inputFile.setFileName(inputFile.fileName());
}

void EsiExtractor::setOutputFolder(QDir &outputFolder)
{
    EsiExtractor::outputFolder = outputFolder;
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
