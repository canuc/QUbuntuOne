#include "qubuntuonepostrequest.h"
using namespace QUbuntuOne;
QUbuntuOnePostRequest::QUbuntuOnePostRequest(QString url,QObject *parent) :
    UbuntuOneRequest(url,UbuntuOneRequest::RequestTypePost, parent)
{
}
