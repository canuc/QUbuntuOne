#ifndef INVALIDREQUESTTYPE_H
#define INVALIDREQUESTTYPE_H

#include "qexception.h"

class InvalidRequestType : public QException
{
public:
    InvalidRequestType();
};

#endif // INVALIDREQUESTTYPE_H
