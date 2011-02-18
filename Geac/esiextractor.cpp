#include "esiextractor.h"

EsiExtractor::EsiExtractor(QFile &inputFile, QFile &ESI)
{
    ESI.fileName() = inputFile.fileName().append("ESI");
}

EsiExtractor::EsiExtractor(QFile &inputFile)
{
    outputFile.fileName() = inputFile.fileName();
}

void EsiExtractor::createParser()
{

}

void EsiExtractor::createEsi()
{
    this->parseInput();
}

void EsiExtractor::parseInput()
{

}

QStringList EsiExtractor::getThermochemistry()
{
    return thermochemistry;
}

QStringList EsiExtractor::getHarmonicFrequencies()
{
    return harmonicFrequencies;
}

QStringList EsiExtractor::getStandardCoordinates()
{
    return standardCoordinates;
}

QString EsiExtractor::getHartreeFockEnergy()
{
    return hartreeFockEnergy;
}
