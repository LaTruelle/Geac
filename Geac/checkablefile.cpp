#include "checkablefile.h"

CheckableFile::CheckableFile(QObject *parent) :
    QFile(parent)
{
    converted = false;
    toConvert = true;
}

bool CheckableFile::getConversionRequired()
{
    return toConvert;
}

bool CheckableFile::getConversionState()
{
    return converted;
}

void CheckableFile::setConversionState(bool boolean)
{
    converted = boolean;
}

void CheckableFile::setConversionRequired(bool boolean)
{
    toConvert = boolean;
}
