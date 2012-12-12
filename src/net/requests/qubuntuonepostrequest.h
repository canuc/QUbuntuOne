#ifndef QUBUNTUONEPOSTREQUEST_H
#define QUBUNTUONEPOSTREQUEST_H

#include <QObject>
#include "requests/ubuntuonerequest.h"

namespace QUbuntuOne {
    class QUbuntuOnePostRequest : public UbuntuOneRequest
    {
        Q_OBJECT
    public:
        explicit QUbuntuOnePostRequest(QString url,QObject *parent = 0);


    protected:

    signals:

    public slots:

    };
}

#endif // QUBUNTUONEPOSTREQUEST_H
