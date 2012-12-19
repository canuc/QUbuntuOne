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

#ifndef UBUNTUONEOAUTHREQUEST_H
#define UBUNTUONEOAUTHREQUEST_H

#include "../jsonubuntuonerequest.h"

namespace QUbuntuOne {

     /*!
     * This will request will retrieve a request token with a specified username
     * and password.
     *
     * \brief The UbuntuOneOAuthRequest class Request to retrieve auth token.
     */
    class UbuntuOneOAuthRequest : public JSONUbuntuOneRequest
    {
        Q_OBJECT
    public:

        explicit UbuntuOneOAuthRequest(QString username,QString password,QObject *parent = 0);

        /**
         * Once our request has completed we will be able to retriev the secret token
         * that we will be able to use as an auth token.
         *
         * @pre isSuccess() must return true
         * @brief getSecretToken
         * @return the secret token
         */
        const QString & getSecretToken() const;
        /**
         * Once our request has completed you will be able to retrieve this value
         * upon sucess.
         *
         * \link https://one.ubuntu.com/developer/account_admin/auth/index#accessing-ubuntu-one-apis
         * \pre isSuccess() must return true
         * \brief getSecretToken
         * \return the secret token
         */
        const QString & getToken() const;
    protected:
        /*!
         * Overriden addRequestHeader adds the authorization header.
         *
         * \link https://one.ubuntu.com/developer/account_admin/auth/index#accessing-ubuntu-one-apis
         * \brief addRequestHeader
         * \param req
         */
        virtual void addRequestHeader(QNetworkRequest *req);
        /*!
         * Parse out the relavent data.
         *
         * \brief processData overriden to retrieve the relavent JSON values
         * \param bytes byte array returned by the request
         */
        virtual void processData(const QByteArray & bytes);
    private:
        QString _username;  //!< The user's username
        QString _password;  //!< The user's password, cleartext

        QString _resultantSecretToken; //!< The secret token parsed from the json result
        QString _resultantToken; //!< The auth token parsed from the json response

    signals:
        // nothing
    public slots:
        // nothing
    };
}

#endif // UBUNTUONEOAUTHREQUEST_H
