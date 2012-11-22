#include "cookiepersistantubuntuonerequest.h"
using namespace QUbuntuOne;
CookiePersistantUbuntuOneRequest::CookiePersistantUbuntuOneRequest(QString url,RequestType type, QObject * object)
    :UbuntuOneRequest(url,type,object)
{

}

void CookiePersistantUbuntuOneRequest::processResponseHeader(QNetworkReply * reply)
{

    QVariant var = reply->header(SetCookieHeader);
    QList<QNetworkCookie> cookies = qobject_cast<QList<QNetworkCookie> > (var.data())
}
