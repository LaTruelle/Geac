#ifndef CIFWRITER_H
#define CIFWRITER_H

#include <QObject>

class CifWriter : public QObject
{
    Q_OBJECT
public:
    explicit CifWriter(QObject *parent = 0);
    ~CifWriter();

signals:

public slots:
};

#endif // CIFWRITER_H
