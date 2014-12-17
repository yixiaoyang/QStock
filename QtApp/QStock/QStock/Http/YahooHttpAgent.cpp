#include "YahooHttpAgent.h"
#include "Quote/QuoteTools.h"

#include <QDir>

void YahooHttpAgent::appendToDownloadList(QString &url, QString &filename)
{
    DownloadListItem item;
    item.url = url;
    item.filename = filename;
    downloadList.append(item);
}

YahooHttpAgent::YahooHttpAgent()
{
    //s=002065.sz&a=08&b=25&c=2010&d=09&e=8&f=2010&g=d","002065.sz.csv"

    urlPrefix = QString("http://ichart.yahoo.com/table.csv?");
    downloadDir = QString("./Downloads");

    QDir dir;
    if(! dir.exists(downloadDir) ) {
        dir.mkdir(downloadDir);
    }

}

YahooHttpAgent::~YahooHttpAgent()
{
    if(this->isRunning()){
        this->terminate();
    }
}

STATUS YahooHttpAgent::downloadQuotes(QString key, DateRange& rang)
{
    QString url = urlPrefix;
    QString filename = this->downloadDir+"/"+key+".csv";
    QString s = QuoteTools::KeyA2Yahoo(key);

    if(s == QString::null)
        return STATUS_FAILED;

    url.append("s=");
    url.append(s);
    url.append("&a=");
    url.append(QString::number(rang.sMonth));
    url.append("&b=");
    url.append(QString::number(rang.sDay));
    url.append("&c=");
    url.append(QString::number(rang.sYear));
    url.append("&d=");
    url.append(QString::number(rang.eMonth));
    url.append("&e=");
    url.append(QString::number(rang.eDay));
    url.append("&f=");
    url.append(QString::number(rang.eYear));
    url.append("&g=d&ignore=.csv");

    appendToDownloadList(url,filename);
    if(!this->isRunning()){
        this->start();
    }

    return STATUS_OK;
}

void YahooHttpAgent::run()
{
    DownloadListItem item;
    if(!this->downloadList.isEmpty()){
        item = this->downloadList.first();
        curl.downloadURL(item.url.toStdString().c_str(),item.filename.toStdString().c_str());
        this->downloadList.removeFirst();
    }
}

void YahooHttpAgent::slot_downloadDone(int)
{

}
