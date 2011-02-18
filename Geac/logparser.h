#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <QFile>
#include <QString>
#include <QStringList>

class LogParser
{
public:
    LogParser();
    LogParser(QFile &file);
    void setFileToParse(QFile &file);
    void parse();

    QStringList getThermochemistry();
    QStringList getHarmonicFrequencies();
    QStringList getStandardCoordinates();
    QString getHartreeFockEnergy();
    QString getNAtoms();

private:
    QFile *fileToParse;
    QStringList thermochemistry;
    QStringList harmonicFrequencies;
    QStringList standardCoordinates;
    QString hartreeFockEnergy;
    QString nAtoms;

};

#endif // LOGPARSER_H
