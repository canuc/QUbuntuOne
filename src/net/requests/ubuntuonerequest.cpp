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

#include "ubuntuonerequest.h"
#include "../exception/qexception.h"
#include <QMutexLocker>
#include "../exception/invalidrequesttype.h"
#include <QtNetwork/QHttpMultiPart>

using namespace QUbuntuOne;

UbuntuOneRequest::UbuntuOneRequest(QString url,UbuntuOneRequest::RequestType type,QObject *parent) :
    QObject(parent),_type(type),_url(url),_status(RequestStatusIncomplete),_currentRequest(0),_networkAccessManager(new QNetworkAccessManager(this))
{

}

UbuntuOneRequest::~UbuntuOneRequest()
{
}

QString UbuntuOneRequest::getUrl() const {
    return _url;
}

bool UbuntuOneRequest::isComplete() const {
    return (_status != UbuntuOneRequest::RequestStatusIncomplete);
}

bool UbuntuOneRequest::isSuccess() const {
    return (_status != UbuntuOneRequest::RequestStatusSucess);
}

bool UbuntuOneRequest::isError() const {
    return (_status != UbuntuOneRequest::RequestStatusError);
}

bool UbuntuOneRequest::isCanceled() const {
    return (_status != UbuntuOneRequest::RequestStatusCanceled);
}

void UbuntuOneRequest::setRequestStatus(UbuntuOneRequest::RequestStatus status)
{
    QMutexLocker locker(&_mutex);
    if ( _status == UbuntuOneRequest::RequestStatusIncomplete ) {
        _status = status;
        emit(status);
    }
    return;
}

void UbuntuOneRequest::run ()
{
    if ( _currentRequest < getMaxRetries()) {
        QNetworkRequest * req = createRequest();

        // Do we have a request that we should attempt?
        if ( req != NULL ) {
            doRequest(req);
        } else {
            throw new QException("Error with setting the request status!");
        }


        // Increment the sequence number
        _currentRequest++;
    }
}

const int UbuntuOneRequest::getMaxRetries() const
{
    return 3;
}

bool UbuntuOneRequest::autoDelete () const
{
    return true;
}

QNetworkReply * UbuntuOneRequest::doRequest(QNetworkRequest * req)
{
    QNetworkReply * reply = NULL;

    switch (getRequestType()) {
        case RequestTypeGet:
             reply = doGetRequest(req);
             break;
        case RequestTypePost:
              reply = doPostRequest(req);
              break;
        case RequestTypePut:
              reply = doPutRequest(req);
              break;
        case RequestTypeDelete:
             reply = doDeleteRequest(req);
             break;
        default:
            throw new InvalidRequestType();
    }

    if ( reply != NULL ) {
        /*
         * connect all the slots and signals
         */
        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorRecieved(QNetworkReply::NetworkError)));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
        connect(reply,SIGNAL(uploadProgress(qint64,qint64)), this,SLOT(uploadProgress(qint64,qint64)));

        connect(reply,SIGNAL(finished()),this,SLOT(finished()));
        //
        // To free up any memory that is associated with the request we are
        // going to connect the finished slot to the deleteLater
        //
        connect(reply,SIGNAL(finished()),reply,SLOT(deleteLater()));
    } else {
        throw new InvalidRequestType();
    }

    return reply;
}

 void UbuntuOneRequest::errorRecieved(QNetworkReply::NetworkError code)
 {
     // process response
     QNetworkReply * reply =  qobject_cast<QNetworkReply *>(sender());
     processError(code,reply);
 }

 /*!
  * \brief UbuntuOneRequest::downloadProgress
  * \param bytesReceived
  * \param bytesTotal
  */
 void UbuntuOneRequest::downloadProgress( qint64 bytesReceived, qint64 bytesTotal )
 {
    QNetworkReply * reply =  qobject_cast<QNetworkReply *>(sender());
    progressUpdatedDownload(bytesReceived,bytesTotal,reply);
 }

 /*!
  * Upload progress is complete.
  *
  * \param bytesSent the number of bytes sent
  * \param bytesTotal the number of bytes in the request
  */
 void UbuntuOneRequest::uploadProgress ( qint64 bytesSent, qint64 bytesTotal )
 {
    QNetworkReply * reply =  qobject_cast<QNetworkReply *>(sender());
    progressUpdatedUpload(bytesSent,bytesTotal,reply);
 }

 /*!
  * signal finished emitted.
  *
  * \brief UbuntuOneRequest::finished the request for the current request has completed
  */
 void UbuntuOneRequest::finished()
 {
    QNetworkReply * reply =  qobject_cast<QNetworkReply *>(sender());
    requestFinished(reply);
 }

 /*!
  * Process an error response.
  */
 void UbuntuOneRequest::processError(QNetworkReply::NetworkError code,QNetworkReply * reply) {
     setRequestStatus(RequestStatusError);
 }

 /*!
  * Handle any progress update.
  *
  * /param bytes the number of bytes downloaded in this update
  * /param bytesTotal the number of total bytes downloaded
  * /param reply the associated network reply
  */
 void UbuntuOneRequest::progressUpdatedDownload(qint64 bytes,qint64 bytesTotal, QNetworkReply * reply) {

 }

 /*!
  * Progress updated for an upload
  * \brief UbuntuOneRequest::progressUpdatedUpload the progress is updated
  * \param bytes the total number of bytes
  * \param bytesTotal the number of bytes total for the upload
  * \param reply
  */
 void UbuntuOneRequest::progressUpdatedUpload(qint64 bytes, qint64 bytesTotal, QNetworkReply * reply) {

 }

 /*!
  * Can be overloaded to provide functionality when the request finishes
  *
  * \brief UbuntuOneRequest::requestFinished request finishes
  * \param reply the corresponding reply object for this
  */
 void UbuntuOneRequest::requestFinished(QNetworkReply * reply) {
    setRequestStatus(RequestStatusSucess);

    _data = reply->readAll();
    processData(_data);
 }

 void UbuntuOneRequest::processResponseHeader(QNetworkReply * req) {
    // no-op
 }


 /*!
  * \brief doPostRequest preform the post request and return the network reply object
  * \param req the request to post
  * \see getMultipartData()
  * \return reply object
  */
 QNetworkReply * UbuntuOneRequest::doPostRequest(QNetworkRequest * req)
 {
     QScopedPointer<QHttpMultiPart> multipartData(getPostMultipartData());
     return _networkAccessManager->post(*req,multipartData.data());
 }

 /*!
  * This will return the required mutlipart data only used in post methods
  * \brief getMultipartData
  * \return
  */
 QHttpMultiPart * UbuntuOneRequest::getPostMultipartData() {
    return NULL;
 }

 /*!
  * Do delete request
  * \brief doDeleteRequest preform delete request
  * \param req the request to preform the delete on
  * \return delete reply
  */
 QNetworkReply * UbuntuOneRequest::doDeleteRequest(QNetworkRequest * req)
 {
     return _networkAccessManager->deleteResource(*req);
 }

 /*!
  * This will preform the put request on this classes specified url
  * \param req the reuqest to process
  * \see getPutMultipartData()
  * \return the reply that should be parsed
  */
 QNetworkReply * UbuntuOneRequest::doPutRequest(QNetworkRequest * req)
 {
    QScopedPointer<QHttpMultiPart> multipartData(getPutMultipartData());
    return _networkAccessManager->put(*req,multipartData.data());
 }

 /*!
  * This will return the required mutlipart data only used in post methods
  * \brief getPutMultipartData called from the put request
  * \return NULL, or multipart data pointer
  */
 QHttpMultiPart * UbuntuOneRequest::getPutMultipartData() {
    return NULL;
 }

 /*!
  * This will preform the get request
  * \param req a get request
  * \return the reply object
  */
 QNetworkReply * UbuntuOneRequest::doGetRequest(QNetworkRequest * req) {
    return _networkAccessManager->get(*req);
 }

 /*!
  * Create a new QNetworkRequest, the default implementation will call {\ref addRequestHeader()}
  * all the necessary headers.
  *
  * \return the created request, not NULL.
  */
 QNetworkRequest * UbuntuOneRequest::createRequest() {
     QNetworkRequest * request = new QNetworkRequest(QUrl(getUrl()));

     addRequestHeader(request);

     return request;
 }

 /*!
  * Adds the required headers to the specified request. Default implementation is
  * a no-op.
  *
  * \brief addRequestHeader add all the neccessary headers
  * \param req the request to add headers to
  */
 void UbuntuOneRequest::addRequestHeader(QNetworkRequest * req)
 {
    // No-op
 }

 const QByteArray & UbuntuOneRequest::getBytes() const  {
    return _data;
 }

 void UbuntuOneRequest::processData(const QByteArray & bytes) {
     // no-op
 }
