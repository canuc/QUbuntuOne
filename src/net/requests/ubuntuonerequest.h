#ifndef UBUNTUONEREQUEST_H
#define UBUNTUONEREQUEST_H

#include <QObject>
namespace QUbuntuOne {

    /**
      * UbuntuOneRequest
      * The base atom for a request that can be inherited to create a
      * new item
      */
    class UbuntuOneRequest : public QObject
    {
        Q_OBJECT
    public:
        UbuntuOneRequest(RequestType type,QObject *parent = 0);

        enum RequestType {
            RequestTypeGet    = 0x00,
            RequestTypePut    = 0x01,
            RequestTypePost   = 0x02,
            RequestTypeDelete = 0x03
        };

        RequestType getRequestType() const;
    private:
        RequestType _type;
        QString _url;
    signals:

    public slots:

    };
}

#endif // UBUNTUONEREQUEST_H
