#include "esiextractor.h"

EsiExtractor::EsiExtractor(QFile &inputFile, QFile &ESI)
{
    ESI.fileName() = inputFile.fileName().append("ESI");
}
