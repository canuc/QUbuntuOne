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

#include "testwrangler.h"

#include <QtTest/QTest>
#include "requesttest.h"

TestWrangler::TestWrangler(QCoreApplication *parent) :
    QObject(parent)
{
    addTest(new RequestTest(this));
}

TestWrangler::~TestWrangler()
{
    return;
}

void TestWrangler::runTests() {
    int numberOfTests = testList.count();

    for ( int i =0; i < numberOfTests; i++ ) {
        QObject * currentTest = testList.at(i);
        QTest::qExec(currentTest);
    }

    return;
}

void TestWrangler::addTest(QObject * testObject)
{
    testList.append(testObject);
}
