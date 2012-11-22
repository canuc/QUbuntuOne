#ifndef COOKIEPERSISTANTUBUNTUONEREQUEST_H
#define COOKIEPERSISTANTUBUNTUONEREQUEST_H

#include <QHash>
#include <QtNetwork/QNetworkReply>

namespace QUbuntuOne {
    class CookiePersistantUbuntuOneRequest : public UbuntuOneRequest
    {
    Q_OBJECT
    private:
        QHash<QString,QString> cookieKeyTable;

    protected:
        void processResponseHeader(QNetworkReply * req);
    public:
        CookiePersistantUbuntuOneRequest(QString url,RequestType type, QObject * parent = 0);


    };
}

#endif // COOKIEPERSISTANTUBUNTUONEREQUEST_H
