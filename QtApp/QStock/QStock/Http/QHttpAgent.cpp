#include "QHttpAgent.h"

QHttpAgent::QHttpAgent(QString m_host)
{
    this->host = m_host;

    http = new QHttp(this);
    /*"http://hq.sinajs.cn"*/
    http->setHost(host);
    url=QString("http://hq.sinajs.cn");

    connect(http, SIGNAL(done(bool)),this, SLOT(on_httpDone(bool)));
    connect(http, SIGNAL(dataReadProgress(int,int)),this, SLOT(on_dataReadProgress(int,int)));
    connect(http, SIGNAL(readyRead(QHttpResponseHeader)),this, SLOT(on_readyRead(QHttpResponseHeader)));

}

void QHttpAgent::on_httpDone(bool done)
{
    emit httpDone(done);
}

void QHttpAgent::on_dataReadProgress(int done, int total)
{
    emit dataReadProgress(done,total);
}

void QHttpAgent::on_readyRead(QHttpResponseHeader )
{
    QByteArray bytes=http->readAll();
    emit readyRead(bytes);
}

void QHttpAgent::fetchStockData()
{
    if(uri.isEmpty()){
        return ;
    }
    if(this->isRunning()){
        return ;
    }
    this->start();
}

void QHttpAgent::run()
{
    QHttpRequestHeader header("GET",uri);
    header.setValue("Host", "hq.sinajs.cn");
    http->setHost("hq.sinajs.cn");
    http->request(header);
}
