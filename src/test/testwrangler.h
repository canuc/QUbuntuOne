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

#ifndef TESTWRANGLER_H
#define TESTWRANGLER_H

#include <QObject>
#include <QCoreApplication>

/*!
 * This will pull together all the test classes. So that main will stay clean
 *
 * \brief The TestWrangler class
 */
class TestWrangler : public QObject
{
    Q_OBJECT
private:
    QList<QObject*> testList;//!< The lists of tests that should be run

protected:
    void addTest(QObject * testObject); //!< Add a test to the runtime,
                                        //! should be called internally

public:
    explicit TestWrangler(QCoreApplication *parent = 0);
    virtual ~TestWrangler();

    void runTests();
signals:
    
public slots:
    
};

#endif // TESTWRANGLER_H
