#ifndef ESIEXTRACTOR_H
#define ESIEXTRACTOR_H

#include <QFile>

class EsiExtractor
{
public:
    EsiExtractor(QFile &inputFile, QFile &ESI);
};

#endif // ESIEXTRACTOR_H
