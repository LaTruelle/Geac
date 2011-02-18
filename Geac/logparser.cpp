#include "logparser.h"

LogParser::LogParser()
{

}

LogParser::LogParser(QFile &file)
{
    fileToParse->setFileName(file.fileName());
}

void LogParser::setFileToParse(QFile &file)
{
    fileToParse = &file;
}
