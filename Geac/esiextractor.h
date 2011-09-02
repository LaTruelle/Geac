#ifndef ESIEXTRACTOR_H
#define ESIEXTRACTOR_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>
#include "logparser.h"
#include "checkablefile.h"

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
    EsiExtractor(CheckableFile &inputFile);
    void setInputFile(CheckableFile &inputFile);
    void setOutputFolder(QDir &outputFolder);
    void setRequiredFields(bool &thermochemistry,
                           bool &harmonicFrequencies,
                           bool &standardCoordinates,
                           bool &hartreeFockEnergy);
    void createEsi();
    void setExtension(QString extension);

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
    QString fileExtension;
};

#endif // ESIEXTRACTOR_H
