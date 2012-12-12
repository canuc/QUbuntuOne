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

#include "requesttest.h"
#ifdef UBUNTU_CLOUD_TEST
#include "../net/requests/ubuntuonerequest.h"
#include <QDebug>
#include <QApplication>
#include "unistd.h"

using namespace QUbuntuOne;
RequestTest::RequestTest(QObject *parent) :
    QObject(parent)
{
}

void RequestTest::testSingleRequest()
{
    QScopedPointer<UbuntuOneRequest> request(new UbuntuOneRequest("http://www.google.com",UbuntuOneRequest::RequestTypeGet,this));
    request->run();
    QApplication::processEvents(QEventLoop::WaitForMoreEvents,2000);
    QApplication::sendPostedEvents();
    sleep(1); // Sleep For a second
    QApplication::processEvents(QEventLoop::WaitForMoreEvents,2000);
    QApplication::sendPostedEvents();

    QCOMPARE(request->getRequestStatus(),UbuntuOneRequest::RequestStatusSucess);
}


#endif
