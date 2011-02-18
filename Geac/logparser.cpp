#include "logparser.h"

LogParser::LogParser(QFile &file)
{
    fileToParse->setFileName(file.fileName());
}
