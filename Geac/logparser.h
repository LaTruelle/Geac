#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <QFile>

class LogParser
{
public:
    LogParser();
    LogParser(QFile &file);
    void setFileToParse(QFile &file);

private:
    QFile *fileToParse;
};

#endif // LOGPARSER_H
