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
    EsiExtractor(QFile &inputFile, QFile &outputFile);
    EsiExtractor(QFile &inputFile);

    QStringList getThermochemistry();
    QStringList getHarmonicFrequencies();
    QStringList getStandardCoordinates();
    QString getHartreeFockEnergy();

private:
    void createParser();
    void createEsi();

    LogParser parser;
    QFile *inputFile;
    QFile *outputFile;
    QStringList thermochemistry;
    QStringList harmonicFrequencies;
    QStringList standardCoordinates;
    QString hartreeFockEnergy;
};

#endif // ESIEXTRACTOR_H
