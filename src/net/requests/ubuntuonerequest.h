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

#ifndef UBUNTUONEREQUEST_H
#define UBUNTUONEREQUEST_H

#include <QObject>
#include <QMutex>
#include <QRunnable>
#include <QtNetwork/QNetworkReply>
namespace QUbuntuOne {

    /*!
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

        /*!
         * virtual destructor - clean up any allocations
         */
        virtual ~UbuntuOneRequest();

        RequestType getRequestType() const {
            return _type;
        }
        RequestStatus getRequestStatus() const {
            return _status;
        }

        /*!
         * \brief isComplete returns true if the request has changed status
         * \return is complete
         */
        bool isComplete() const;

        /*!
         * \brief isSuccess the request success
         * \return the request success
         */
        bool isSuccess() const;

        /*!
         * \brief isError
         * \return is the request in error state
         */
        bool isError() const;

        /*!
         * \brief isCanceled is the current request cancelled
         * \return is the request cancelled
         */
        bool isCanceled() const;

        /*!
         * This is the overriden to auto delete the ubuntu request once attached
         * to a thread pool
         * \brief autoDelete the autodelete
         * \returns true
         */
        virtual bool autoDelete () const;
        /*!
         * Overriden run method of QRunnable
         */
        void run ();

         /*!
          * get the byte data
          * \brief get the request bytes
          * \return the byte data
          */
          const QByteArray & getBytes() const;
    protected:

        /*!
         * Create a new QNetworkRequest, the default implementation will call {\ref addRequestHeader()}
         * all the necessary headers. The request will use the url retrieved by: {\ref getUrl}.
         *
         * \return the created request, not NULL.
         */
        virtual QNetworkRequest * createRequest();

        /*!
         * \brief doPostRequest preform the post request and return the network reply object
         * \param req the request to post
         * \return reply object
         */
        virtual QNetworkReply * doPostRequest(QNetworkRequest * req);

        /*!
         * Do delete request
         * \brief doDeleteRequest preform delete request
         * \param req the request to preform the delete on
         * \return delete reply
         */
        virtual QNetworkReply * doDeleteRequest(QNetworkRequest * req);

        /*!
         * This will preform the put request on this classes specified url
         * \param req the reuqest to process
         * \return the reply that should be parsed
         */
        virtual QNetworkReply * doPutRequest(QNetworkRequest * req);

        /*!
         * This will preform the get request
         * \param req a simple get request
         * \return the reply object
         */
        virtual QNetworkReply * doGetRequest(QNetworkRequest * req);

        /*!
         * \brief setRequestStatus( RequestStatus status )
         * \param status the status to a status
         */
        void setRequestStatus(RequestStatus status);

        /*!
         * This will return the required mutlipart data only used in post methods
         * \brief getPutMultipartData called from the put request
         * \return NULL, or multipart data pointer
         */
        virtual QHttpMultiPart * getPutMultipartData();

        /*!
         * This will return the required mutlipart data only used in post methods
         * \brief getMultipartData
         * \return
         */
        virtual QHttpMultiPart * getPostMultipartData();

        /*!
         * This will get the requested url
         * \brief getUrl get url
         * \return the url string
         */
        QString getUrl() const;

        /*!
         * The number of max retries that should be attempted with the data contained in this request.
         * something rational is the default value 3. The sequence number is a single request and not a
         * \brief getMaxRetries
         * \return
         */
        const int getMaxRetries() const;

        /*!
         * These are the the callback slots that will be called based on the status
         */
        virtual void processError(QNetworkReply::NetworkError code,QNetworkReply * reply);
        virtual void progressUpdatedDownload(qint64 bytes,qint64 bytesTotal, QNetworkReply * reply);
        virtual void progressUpdatedUpload(qint64 bytes, qint64 bytesTotal, QNetworkReply * reply);
        virtual void requestFinnished(QNetworkReply * reply);

        /*!
         * This will run the request process and hook up the returned reply
         * to the correct slots and signals.
         *
         * \brief doRequest the request to run
         * \param req
         * \throws InvalidRequestType*
         * \return the network request type
         */
        virtual QNetworkReply * doRequest(QNetworkRequest * req);

        /*!
         * Process all the headers from the replys.
         * \brief processResponseHeader
         * \param req the network response
         */
        virtual void processResponseHeader(QNetworkReply * req);

        /*!
         * Adds the required headers to the specified request. Default implementation is
         * a no-op.
         *
         * \brief addRequestHeader add all the neccessary headers
         * \param req the request to add headers to
         */
        virtual void addRequestHeader(QNetworkRequest * req);

    private:
        RequestType   _type;
        RequestStatus _status;
        QMutex _mutex;
        QString _url;
        QNetworkAccessManager * _networkAccessManager;
        int _currentRequest;
        QByteArray _data;

    signals:
        void statusChanged(RequestStatus status);
    public slots:

    protected slots:
        void errorRecieved(QNetworkReply::NetworkError code);
        void downloadProgress( qint64 bytesReceived, qint64 bytesTotal );
        /*!
         * Update the progress of an upload.
         * \pre object emiting this signal MUST be a QNetworkRequest
         * \brief uploadProgress the total upload progress
         * \param bytesSent the number of bytes sent in the request
         * \param bytesTotal the number of total bytes that were uploaded
         */
        void uploadProgress ( qint64 bytesSent, qint64 bytesTotal );

        /*!
         * Slot should be called when the wrapped NetworkRequest is completed.
         * \brief finished The request has completed
         * \see QNetworkReply::finnished()
         */
        void finished();
    };
}

#endif // UBUNTUONEREQUEST_H
