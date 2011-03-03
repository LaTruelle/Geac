#ifndef ESIEXTRACTOR_H
#define ESIEXTRACTOR_H

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
    EsiExtractor(QFile &inputFile, QFile &outputFile);
    EsiExtractor(QFile &inputFile);
    void setInputFile(QFile &inputFile);
    void setOutputFile(QFile &outputFile);
    void setRequiredFields(bool &thermochemistry,
                           bool &harmonicFrequencies,
                           bool &standardCoordinates,
                           bool &hartreeFockEnergy);
    void createEsi();

private:
    void createParser();

    bool reqThermochemistry;
    bool reqHarmonicFrequencies;
    bool reqStandardCoordinates;
    bool reqHartreeFock;
    LogParser parser;
    QFile *inputFile;
    QFile *outputFile;
};

#endif // ESIEXTRACTOR_H
