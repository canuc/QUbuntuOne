#include "ubuntuonerequest.h"
#include "../exception/qexception.h"
#include <QMutexLocker>
#include "../exception/invalidrequesttype.h"

using namespace QUbuntuOne;

UbuntuOneRequest::UbuntuOneRequest(QString url,UbuntuOneRequest::RequestType type,QObject *parent) :
    QObject(parent)
{
    _type = type;
    _url =url;
    _networkAccessManager = new QNetworkAccessManager(this);
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
    if ( _status != UbuntuOneRequest::RequestStatusIncomplete ) {
        throw new QException("Double setting the request status");
    } else {
        _status = status;
        emit(status);
    }
    return;
}

void UbuntuOneRequest::run ()
{
    if ( _currentRequest < getMaxRetries()) {
        QNetworkRequest * req = createRequest();


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

QNetworkRequest * UbuntuOneRequest::createRequest()
{
    return NULL;
}

QNetworkReply * UbuntuOneRequest::doRequest(QNetworkRequest * req)
{
    QNetworkReply * reply;
    if ( getRequestType() == RequestTypeGet ) {
        reply = doGetRequest(req);
    } else if ( getRequestType() == RequestTypePost ) {
        reply = doGetRequest(req);
    } else if ( getRequestType() == RequestTypePut ) {
        reply = doPutRequest(req);
    } else if ( getRequestType() == RequestTypeDelete ) {
        reply = doDeleteRequest(req);
    }

    if ( reply != NULL ) {
        /**
         * connect all the slots and signals
         */
        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorRecieved(QNetworkReply::NetworkError)));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
        connect(reply,SIGNAL(uploadProgress(qint64,qint64)), this,SLOT(uploadProgress(qint64,qint64)));
        connect(reply,SIGNAL(finished()),this,SLOT(finished()));
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

 void UbuntuOneRequest::downloadProgress( qint64 bytesReceived, qint64 bytesTotal )
 {
    QNetworkReply * reply =  qobject_cast<QNetworkReply *>(sender());
    progressUpdatedDownload(bytesReceived,bytesTotal,reply);
 }

 void UbuntuOneRequest::uploadProgress ( qint64 bytesSent, qint64 bytesTotal )
 {
    QNetworkReply * reply =  qobject_cast<QNetworkReply *>(sender());
    progressUpdatedUpload(bytesSent,bytesTotal,reply);
 }

 void UbuntuOneRequest::finished()
 {
    QNetworkReply * reply =  qobject_cast<QNetworkReply *>(sender());
    requestFinnished(reply);
 }

 void UbuntuOneRequest::processError(QNetworkReply::NetworkError code,QNetworkReply * reply) {

 }

 void UbuntuOneRequest::progressUpdatedDownload(qint64 bytes,qint64 bytesTotal, QNetworkReply * reply) {

 }

 void UbuntuOneRequest::progressUpdatedUpload(qint64 bytes, qint64 bytesTotal, QNetworkReply * reply) {

 }

 void UbuntuOneRequest::requestFinnished(QNetworkReply * reply) {

 }
