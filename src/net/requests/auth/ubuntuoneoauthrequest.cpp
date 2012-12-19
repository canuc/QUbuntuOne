/**
 * QUbuntuOne - UbuntuOne for symbian and Harmattan
 *
 * Author: Julian Haldenby (j.haldenby@gmail.com)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  QUbuntuOne is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General
 *  Public License along with QUbuntuOne.  If not, see
 *  <http://www.gnu.org/licenses/>.
 */

#include "ubuntuoneoauthrequest.h"
#include <QtNetwork/QNetworkRequest>
#include <QVariantMap>
#include <QMap>
#include <QDebug>
using namespace QUbuntuOne;

static const QString formatUbuntuOneOAuthRequestUrl(QString url,QString description)
{
    return QString(url) + QString("ws.op").toLatin1().toBase64() + QString("=") + QString ("authenticate") + QString("token_name") + QString("=") + QString("Ubuntu One @ "+description).toLatin1().toBase64();
}

UbuntuOneOAuthRequest::UbuntuOneOAuthRequest(QString username,QString password,QObject *parent) :
    JSONUbuntuOneRequest(formatUbuntuOneOAuthRequestUrl("https://login.ubuntu.com/api/1.0/authentications?","other"),RequestTypeGet,parent)
{
    _username = username;
    _password = password;
}


void UbuntuOneOAuthRequest::addRequestHeader(QNetworkRequest *req)
{
    QString basicAuthString = QString("%1:%2").arg(_username,_password);
    req->setRawHeader(QString('Accept').toLatin1(),QString('application/json').toLatin1());
    req->setRawHeader(QString("Authorization").toLatin1(),QString("Basic %1").arg(QString(basicAuthString.toLatin1().toBase64())).toLatin1());
}

void UbuntuOneOAuthRequest::processData(const QByteArray &bytes)
{
    JSONUbuntuOneRequest::processData(bytes);
    QVariantMap map = getJsonResult();

    QMap<QString,QVariant>::Iterator tokenIt = map.find("token");
    QMap<QString,QVariant>::Iterator secretTokenIt = map.find("token_secret");
    qDebug() << bytes;
    if ( tokenIt != map.end() && secretTokenIt != map.end() ) {
        _resultantSecretToken = tokenIt->toString();
        _resultantToken = tokenIt->toString();
    }

    return;
}

const QString & UbuntuOneOAuthRequest::getSecretToken() const
{
    return _resultantSecretToken;
}

const QString & UbuntuOneOAuthRequest::getToken() const
{
    return _resultantToken;
}



