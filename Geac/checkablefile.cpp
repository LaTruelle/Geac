#include "checkablefile.h"
#include <QDir>

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

QString CheckableFile::displayName()
{
    return this->fileName().remove(0,this->fileName().lastIndexOf(QDir::separator())+1);
}
