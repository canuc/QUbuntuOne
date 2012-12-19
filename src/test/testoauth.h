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

#ifndef TESTOAUTH_H
#define TESTOAUTH_H

#include <QObject>
#include <QSharedPointer>
#include "src/kqoauth/kqoauthmanager.h"
class testOAuth : public QObject
{
    Q_OBJECT
public:
    explicit testOAuth(QObject *parent = 0);
private:
    const QString username;
    const QString password;
    const QString consumerKey;
    const QString consumerKeyPriv;
    QSharedPointer<KQOAuthManager> _authManager;
signals:
    
public slots:

private slots:
    void initTestCase();
    void testOAuthLogin();
    void cleanupTestCase();
};

#endif // TESTOAUTH_H
