#include "QHttpAgent.h"

QHttpAgent::QHttpAgent(QString m_host)
{
    this->host = m_host;
    sep = '\n';

    http = new QHttp(this);
    /*"http://hq.sinajs.cn"*/
    http->setHost(host);
    url=QString(m_host);

    connect(http, SIGNAL(done(bool)),this, SLOT(slot_httpDone(bool)));
    connect(http, SIGNAL(dataReadProgress(int,int)),this, SLOT(on_dataReadProgress(int,int)));
    connect(http, SIGNAL(readyRead(QHttpResponseHeader)),this, SLOT(on_readyRead(QHttpResponseHeader)));
}

void QHttpAgent::slot_httpDone(bool done)
{
    emit httpDone(done);
}

void QHttpAgent::on_dataReadProgress(int done, int total)
{
    emit dataReadProgress(done,total);
}

void QHttpAgent::on_readyRead(QHttpResponseHeader )
{
    int lastSep = 0;
    buffer.append(http->readAll());
    lastSep = buffer.lastIndexOf(sep);
    if(lastSep > 0){
        emit readyRead(buffer.left(lastSep+1));
        buffer.remove(0,lastSep+1);
    }
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
    header.setValue("Host", host);
    http->setHost(host);
    http->request(header);
}
