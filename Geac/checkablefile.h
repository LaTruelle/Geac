#ifndef CHECKABLEFILE_H
#define CHECKABLEFILE_H

#include <QFile>

class CheckableFile : public QFile
{
    Q_OBJECT
public:
    explicit CheckableFile(QObject *parent);
    bool getConversionState();
    bool getConversionRequired();
    QString displayName();

private:
    bool converted;
    bool toConvert;

signals:

public slots:
    void setConversionState(bool boolean);
    void setConversionRequired(bool boolean);
};

#endif // CHECKABLEFILE_H
