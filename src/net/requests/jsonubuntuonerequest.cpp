/**
 * QUbuntuOne - UbuntuOne for symbian and Harmattan
 *
 * Author: Julian Haldenby (j.haldenby@gmail.com)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3.0 of the License, or (at your option) any later version.
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

#include "jsonubuntuonerequest.h"
#include "../../qjson/parser.h"

using namespace QUbuntuOne;
using namespace QJson;

JSONUbuntuOneRequest::JSONUbuntuOneRequest(QString url,UbuntuOneRequest::RequestType type,QObject *parent) : UbuntuOneRequest(url,type,parent)
{

}

void JSONUbuntuOneRequest::processData(const QByteArray & bytes)
{
    QJson::Parser parser;
    bool ok;
    _resultMap = parser.parse(bytes, &ok).toMap();
}


const QVariantMap & JSONUbuntuOneRequest::getJsonResult() const
{
    return _resultMap;
}
