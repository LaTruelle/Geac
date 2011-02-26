#include "esiextractor.h"

EsiExtractor::EsiExtractor()
{
    this->createParser();
}

EsiExtractor::EsiExtractor(QFile &inputFile)
{
    EsiExtractor::inputFile = &inputFile;
    QString fileName = inputFile.fileName();
    EsiExtractor::outputFile->fileName() = fileName.insert(fileName.length()-4, "_esi");
    this->createParser();
}

EsiExtractor::EsiExtractor(QFile &inputFile, QFile &outputFile)
{
    EsiExtractor::inputFile = &inputFile;
    EsiExtractor::outputFile = &outputFile;
    this->createParser();
}

void EsiExtractor::createParser()
{
    parser.setFileToParse(*inputFile);
}

void EsiExtractor::createEsi()
{
    parser.parse();
}

void EsiExtractor::setInputFile(QFile &inputFile)
{
    EsiExtractor::inputFile = &inputFile;
}

void EsiExtractor::setOutputFile(QFile &outputFile)
{
    EsiExtractor::outputFile = &outputFile;
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
