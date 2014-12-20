#include "YahooHttpAgent.h"
#include "Quote/QuoteTools.h"

#include <QDir>

void YahooHttpAgent::appendToDownloadList(QString symbol,QString &url, QString &filename)
{
    DownloadListItem item;
    item.url = url;
    item.filename = filename;
    item.symbol = symbol;
    downloadList.append(item);
}

YahooHttpAgent::YahooHttpAgent()
{
    //real-chart.finance.yahoo.com/table.csv?s=002065.SZ&a=09&b=23&c=2014&d=11&e=20&f=2014&g=d&ignore=.csv
    urlPrefix = QString("http://real-chart.finance.yahoo.com/table.csv?");
    downloadDir = QuoteTools::getDownloadDir();

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

STATUS YahooHttpAgent::downloadQuotes(QString symbol, DateRange& rang)
{
    QString url = urlPrefix;
    QString filename = this->downloadDir+"/"+QuoteTools::genFilename(symbol);
    QString s = QuoteTools::symbolA2Yahoo(symbol);

    if(s == QString::null)
        return STATUS_FAILED;
    url.append("s=");
    url.append(s);
    url.append("&a=");
    url.append(QString::number(rang.sMonth-1));
    url.append("&b=");
    url.append(QString::number(rang.sDay));
    url.append("&c=");
    url.append(QString::number(rang.sYear));
    url.append("&d=");
    url.append(QString::number(rang.eMonth-1));
    url.append("&e=");
    url.append(QString::number(rang.eDay));
    url.append("&f=");
    url.append(QString::number(rang.eYear));
    url.append("&g=d&ignore=.csv");

    appendToDownloadList(symbol,url,filename);
    if(!this->isRunning()){
        this->start();
    }

    return STATUS_OK;
}

bool YahooHttpAgent::isDownloading(QString symbol)
{
    if(downloadList.isEmpty()){
        return false;
    }
    DownloadList::iterator it = downloadList.begin();
    for(;it != downloadList.end(); it++){
        if((*it).symbol == symbol){
            return true;
        }
    }

    return false;
}

void YahooHttpAgent::run()
{
    DownloadListItem item;
    while(!this->downloadList.isEmpty()){
        item = this->downloadList.first();
        curl.downloadURL(item.url.toStdString().c_str(),item.filename.toStdString().c_str());
        this->downloadList.removeFirst();
        emit downloadDone(item.symbol,item.filename);
    }
}
