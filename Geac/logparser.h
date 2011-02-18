#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <QFile>

class LogParser
{
public:
    LogParser(QFile &file);

private:
    QFile *fileToParse;
};

#endif // LOGPARSER_H
