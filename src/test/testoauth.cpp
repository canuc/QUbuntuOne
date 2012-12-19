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

#include "testoauth.h"
#include "src/kqoauth/kqoauthrequest.h"
#include "src/net/requests/auth/ubuntuoneoauthrequest.h"
#include <QDebug>
#include <QApplication>
#include "unistd.h"
#include <QtTest/QTest>
using namespace QUbuntuOne;

testOAuth::testOAuth(QObject *parent) :
    QObject(parent),username("julian.haldenby@gmail.com"),password("Blahblah1"),consumerKey("ubuntuone"),consumerKeyPriv("hammertime")
{
}

/*!
 * This will test the oauth functionality to verify that we can retrieve an
 * auth token.
 * \brief testOAuth::testOAuthLogin
 */
void testOAuth::testOAuthLogin()
{
    QScopedPointer<UbuntuOneOAuthRequest> req(new UbuntuOneOAuthRequest(username,password));
    req->run();

    QApplication::processEvents(QEventLoop::WaitForMoreEvents,2000);
    QApplication::sendPostedEvents();

    sleep(2); // Sleep For a second, and then allow the signals to be fired from
              // KQOAuth's network request

    QApplication::processEvents(QEventLoop::WaitForMoreEvents,2000);
    QApplication::sendPostedEvents();

    sleep(3); // Allow the signals to be fired from
              // KQOAuth's network request

    QApplication::processEvents(QEventLoop::WaitForMoreEvents,2000);
    QApplication::sendPostedEvents();

    QVERIFY(req->getToken().length()>0);
    QVERIFY(req->getSecretToken().length()>0);
}

void testOAuth::initTestCase()
{
    _authManager = QSharedPointer<KQOAuthManager>(new KQOAuthManager());
    _authManager->setHandleUserAuthorization(true);
}

void testOAuth::cleanupTestCase()
{
    _authManager = QSharedPointer<KQOAuthManager>(NULL);
}
