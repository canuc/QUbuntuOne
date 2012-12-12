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

#include "test.h"

#ifndef REQUESTTEST_H
#define REQUESTTEST_H

    #ifdef UBUNTU_CLOUD_TEST
    #include <QtTest/QTest>

    class RequestTest : public QObject
    {
        Q_OBJECT
    public:
        explicit RequestTest(QObject *parent = 0);

    signals:

    private slots:
        void testSingleRequest();
    };

    #endif // ifdef UBUNTU_CLOUT_TEST
#endif  // REQUESTTEST_H
