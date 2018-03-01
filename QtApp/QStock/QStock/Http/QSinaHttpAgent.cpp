#include "QSinaHttpAgent.h"

#include <QNetworkReply>

void QSinaHttpAgent::setIdb(StockIdDB *value)
{
    idb = value;
    if(idb){
        if(idb->isEmpty()){
            /* 默认添加上证和深圳指数 */
            idb->append("sz399001");
            idb->append("sh000001");
        }
    }
}

void QSinaHttpAgent::request(QString url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64…) Gecko/20100101 Firefox/57.0");
    request.setRawHeader("Accept-Language", "en-US,en;q=0.5");

    /*
     *  WARN:放在线程内使用QNetworkAccessManager时没有进行线程的事件循环，需要调用exec()
     *  才能开启线程的事件循环， 因此解决方式为：get(request)后面加上exec()，使线程进行
     *  事件循环。
     *
     *  线程中的run函数返回后线程即结束，根本无法等到reply的finished信号。因此需要加入
     *  QEventLoop来挂起线程。
     */
    http->get(request);
    requestCount++;
}

QSinaHttpAgent::QSinaHttpAgent(QString m_host)
{
    requestCount = 0;
    host = m_host;
    sep = '\n';
    eachFetchCnt = 5;
    http = new QNetworkAccessManager(this);
    /*
     *  @WARN:QNetworkAccessManager是一个单独的类，工作在主线程，将其移到此工作线程，防止
     *        QObject: Cannot create children for a parent that is in a different thread.
     *        错误
     */
    //http->moveToThread(this);
    /*
     *  WARN:放在线程内使用QNetworkAccessManager时没有进行线程的事件循环，需要调用exec()
     *  才能开启线程的事件循环， 因此解决方式为：get(request)后面加上exec()，使线程进行
     *  事件循环。
     */
    connect(http, SIGNAL(finished(QNetworkReply*)),this, SLOT(slot_finished(QNetworkReply*)));
}

QSinaHttpAgent::~QSinaHttpAgent()
{
}

void QSinaHttpAgent::slot_finished(QNetworkReply* reply)
{
    if (reply) {
        if(reply->error() == QNetworkReply::NoError){
            QByteArray data = reply->readAll();
            int lastSep = 0;
            buffer.append(data);
            lastSep = buffer.lastIndexOf(sep);
            if(lastSep > 0){
                emit readyRead(buffer.left(lastSep+1));
                buffer.remove(0,lastSep+1);
            }
        }else{
            qDebug() << reply->error();
        }
        requestCount--;
    } else {
    }
    if(reply)
        reply->close();
    emit httpDone(true);
}


STATUS QSinaHttpAgent::fetchStockData()
{
    if(!idb){
        return STATUS_NULL;
    }
    if(idb->isEmpty()){
        return STATUS_NULL;
    }
    this->run();
    return STATUS_OK;
}

void QSinaHttpAgent::run()
{
    int left = idb->size();
    int size = idb->size();
    int count = 0;
    QString uri;

    while(left >= eachFetchCnt){
        uri = QString("/list=");

        count = eachFetchCnt;
        while(count--){
            uri.append(idb->at(size-left));
            uri.append(",");
            left--;
        }
        uri.remove(uri.length()-1,1);
        request(host+uri);
    }

    if(left > 0){
        uri = QString("/list=");

        count = left;
        while(count--){
            uri.append(idb->at(size-left));
            uri.append(",");
            left--;
        }
        uri.remove(uri.length()-1,1);
        request(host+uri);
    }
}
