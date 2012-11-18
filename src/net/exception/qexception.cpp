#include "qexception.h"

QException::QException(QString name)
{
    _exceptionName = name;
    _exceptionType = "";
}
