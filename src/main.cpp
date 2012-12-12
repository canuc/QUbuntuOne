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

#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#ifdef UBUNTU_CLOUD_TEST
    #include "test/testwrangler.h"
#endif

Q_DECL_EXPORT int main(int argc, char *argv[])
{
#ifndef UBUNTU_CLOUD_TEST
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/UbuntuCloud/main.qml"));
    viewer.showExpanded();

    return app->exec();
#else
    QScopedPointer<QCoreApplication> app(new QCoreApplication(argc,argv) );

    QScopedPointer<TestWrangler> wrangler(new TestWrangler());
    wrangler->runTests();
#endif
}
