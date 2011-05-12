#include "logparser.h"

LogParser::LogParser()
{
}

LogParser::LogParser(QFile &file)
{
    fileToParse->setFileName(file.fileName());
}

void LogParser::parse()
{
    fileToParse->open(QIODevice::ReadOnly);
    while(!fileToParse->atEnd())
    {
        QByteArray line = fileToParse->readLine();
        if (line.contains("NAtoms"))
        {
            int natPos = line.indexOf("NAtoms");
            nAtoms = line.right(line.length()-natPos-8).trimmed(); // Removes "NAtoms =" and all spaces
            int spacePos = nAtoms.indexOf(" ");
            nAtoms = nAtoms.left(spacePos+1);
        }
        if (line.contains("Standard orientation"))
        {
            standardCoordinates.clear(); // We empty the list from previous coordinates
            for(int ctr = 1; ctr<= nAtoms.toInt()+5; ctr++)
            {
                standardCoordinates.append(fileToParse->readLine());
            }
        }
        if (line.contains("Gibbs"))
        {
            thermochemistry.clear(); // Empty the list from previous energies
            for(int ctr = 0; ctr<4; ctr++)
            {
                thermochemistry.append(QString(fileToParse->readLine()));
            }
        }
        if (line.contains("Harmonic frequencies"))
        {
            // Retrieve Three Lowest Harmonic Frequencies.
            // Start by reading the header but not save it
            for (int ctr = 1; ctr<=3; ctr++)
            {
                fileToParse->readLine();
            }
            // Then actually save the next 6 lines that contains the Harmonic Frequencies
            for (int ctr = 1; ctr <= 6; ctr++)
            {
                harmonicFrequencies.append(QString(fileToParse->readLine()));
            }
        }
        if (line.contains("HF="))
        {
            hartreeFockEnergy.clear(); // Removes previous definitions
            // Retrieve HF energy.
            line.remove(0,line.indexOf("HF")); // line begins with HF=
            if (line.contains("\\")) // All the required data is on the same line
            {
                line.remove(line.indexOf("\\"), line.length());
                hartreeFockEnergy.append(line);
            }
            else // the data is split over two lines
            {
                QString lineStr = QString(line);
                lineStr.remove(" ");
                lineStr.remove("\n");
                hartreeFockEnergy.append(lineStr);
                line = fileToParse->readLine();
                line.remove(line.indexOf("\\"), line.length());
                hartreeFockEnergy.append(line);
            }
        }
    }
    fileToParse->close();
}

void LogParser::setFileToParse(QFile &file)
{
    fileToParse = &file;
}

QStringList LogParser::getThermochemistry()
{
    return thermochemistry;
}

QStringList LogParser::getHarmonicFrequencies()
{
    return harmonicFrequencies;
}

QStringList LogParser::getStandardCoordinates()
{
    return standardCoordinates;
}

QString LogParser::getHartreeFockEnergy()
{
    return hartreeFockEnergy;
}

QString LogParser::getNAtoms()
{
    return nAtoms;
}
