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
        if (line.contains("NAtoms")){
            int natPos = line.indexOf("NAtoms");
            nAtoms = line.right(line.length()-natPos-8).trimmed(); // Removes "NAtoms =" and all spaces
            int spacePos = nAtoms.indexOf(" ");
            nAtoms = nAtoms.left(spacePos+1);
        }
        if (line.contains("Standard orientation")){
            standardCoordinates.clear(); // We empty the list from previous coordinates
            for(int ctr = 1; ctr<= nAtoms.toInt()+6; ctr++)
            {
                standardCoordinates.append(fileToParse->readLine());
            }
        }
        if (line.contains("Gibbs")){
            for(int ctr = 0; ctr<4; ctr++)
            {
                thermochemistry.append(QString(fileToParse->readLine()));
            }
        }
        if (line.contains("HF=")){
            // Retrieve HF energy. Careful, it can be split over 2 lines : \HF=xxxxxx
            //                                                             xx\
            // Need to use \ to split.
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
