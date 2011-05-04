#ifndef ESIEXTRACTOR_H
#define ESIEXTRACTOR_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>
#include "logparser.h"

/*
This class extracts all necessary elements from a given file to build an ESI.
    -> Harmonic Frequencies
    -> Standard Coordinates (Using NAtoms value)
    -> Thermochemistry (energies, enthalpies)
    -> Hartee Fock Energy
 */

class EsiExtractor
{
public:
    EsiExtractor();
    EsiExtractor(QFile &inputFile);
    void setInputFile(QFile &inputFile);
    void setOutputFolder(QDir &outputFolder);
    void setRequiredFields(bool &thermochemistry,
                           bool &harmonicFrequencies,
                           bool &standardCoordinates,
                           bool &hartreeFockEnergy);
    void createEsi(QString fileExtension);

private:
    void writeData(QString &outFile);

    bool reqThermochemistry;
    bool reqHarmonicFrequencies;
    bool reqStandardCoordinates;
    bool reqHartreeFock;
    LogParser parser;
    QDir outputFolder;
    QFile inputFile;
    QFile outputFile;
};

#endif // ESIEXTRACTOR_H
