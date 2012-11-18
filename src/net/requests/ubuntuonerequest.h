#ifndef UBUNTUONEREQUEST_H
#define UBUNTUONEREQUEST_H

#include <QObject>
#include <QMutex>
#include <QRunnable>
#include <QtNetwork/QNetworkReply>
namespace QUbuntuOne {

    /**
      * UbuntuOneRequest
      * The base atom for a request that can be inherited to create a
      * new item
      */
    class UbuntuOneRequest : public QObject, public QRunnable
    {
    Q_OBJECT
    public:

        typedef enum {
            RequestTypeGet    = 0x00,
            RequestTypePut    = 0x01,
            RequestTypePost   = 0x02,
            RequestTypeDelete = 0x03
        } RequestType;

        typedef enum {
            RequestStatusIncomplete = 0x00,
            RequestStatusSucess     = 0x01,
            RequestStatusCanceled   = 0x02,
            RequestStatusError      = 0x03
        } RequestStatus;

        UbuntuOneRequest(QString url,RequestType type,QObject *parent = 0);


        RequestType getRequestType() const {
            return _type;
        }
        RequestStatus getRequestStatus() const {
            return _status;
        }

        /**
         * @brief isComplete returns true if the request has changed status
         * @return is complete
         */
        bool isComplete() const;

        /**
         * @brief isSuccess the request success
         * @return the request success
         */
        bool isSuccess() const;

        /**
         * @brief isError
         * @return is the request in error state
         */
        bool isError() const;

        /**
         * @brief isCanceled is the current request cancelled
         * @return is the request cancelled
         */
        bool isCanceled() const;

        /**
         * This is the overriden to auto delete the ubuntu request once attached
         * to a thread pool
         * @brief autoDelete the autodelete
         * @returns true
         */
        bool autoDelete () const;
        /**
         * Overriden run method of QRunnable
         */
        void run ();


    protected:
        virtual QNetworkReply * request()=0;
        virtual QNetworkRequest * createRequest()=0;
        /**
         * @brief doPostRequest preform the post request and return the network reply object
         * @param req the request to post
         * @return reply object
         */
        virtual QNetworkReply * doPostRequest(QNetworkRequest * req)=0;
        /**
         * Do delete request
         * @brief doDeleteRequest preform delete request
         * @param req the request to preform the delete on
         * @return delete reply
         */
        virtual QNetworkReply * doDeleteRequest(QNetworkRequest * req)=0;
        /**
         * This will preform the put request on this classes specified url
         * @param req the reuqest to process
         * @return the reply that should be parsed
         */
        virtual QNetworkReply * doPutRequest(QNetworkRequest * req)=0;
        /**
         * This will preform the get request
         * @param req a simple get request
         * @return the reply object
         */
        virtual QNetworkReply * doGetRequest(QNetworkRequest * req)=0;
        /**
         * @brief setRequestStatus( RequestStatus status )
         * @param status the status to a status
         */
        void setRequestStatus(RequestStatus status);
        /**
         * This will get the requested url
         * @brief getUrl get url
         * @return the url string
         */
        QString getUrl() const;
        const int getMaxRetries() const;

        void processError(QNetworkReply::NetworkError code,QNetworkReply * reply);
        void progressUpdatedDownload(qint64 bytes,qint64 bytesTotal, QNetworkReply * reply);
        void progressUpdatedUpload(qint64 bytes, qint64 bytesTotal, QNetworkReply * reply);
        void requestFinnished(QNetworkReply * reply);
        QNetworkReply * doRequest(QNetworkRequest * req);
    private:
        RequestType   _type;
        RequestStatus _status = RequestStatusIncomplete;
        QMutex _mutex;
        QString _url;
        QNetworkAccessManager * _networkAccessManager = NULL;

        int _currentRequest = 0;
    signals:
        void statusChanged(RequestStatus status);

    public slots:

    protected slots:
        void errorRecieved(QNetworkReply::NetworkError code);
        void downloadProgress( qint64 bytesReceived, qint64 bytesTotal );
        void uploadProgress ( qint64 bytesSent, qint64 bytesTotal );
        void finished();
    };
}

#endif // UBUNTUONEREQUEST_H
