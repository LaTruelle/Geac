#include "checkablefile.h"

CheckableFile::CheckableFile(QObject *parent) :
    QFile(parent)
{
    converted = false;
    toConvert = true;
}

void CheckableFile::setConversionState(bool boolean)
{
    converted = boolean;
}

void CheckableFile::setConversionRequired(bool boolean)
{
    toConvert = boolean;
}
