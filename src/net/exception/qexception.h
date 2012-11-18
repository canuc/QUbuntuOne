#ifndef QEXCEPTION_H
#define QEXCEPTION_H
#include <QString>

class QException
{
public:
    QException(QString name);

protected:
    QString _exceptionType;
    QString _exceptionName;
};

#endif // QEXCEPTION_H
