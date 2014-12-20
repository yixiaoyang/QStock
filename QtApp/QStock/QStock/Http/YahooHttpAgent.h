#ifndef YAHOOHTTPAGENT_H
#define YAHOOHTTPAGENT_H

#include <QThread>
#include <QList>

#include "types.h"
#include "CurlHttpAgent.h"
#include "Quote/DateRange.h"

typedef struct _DownloadListItem{
    QString symbol;
    QString url;
    QString filename;
}DownloadListItem;
typedef QList<DownloadListItem> DownloadList;

class YahooHttpAgent : public QThread
{
    Q_OBJECT
private:
    QString urlPrefix;
    QString downloadDir;

    DownloadList downloadList;
    CurlHttpAgent curl;
    void appendToDownloadList(QString symbol, QString& url, QString& filename);
public:
    YahooHttpAgent();
    ~YahooHttpAgent();

    STATUS downloadQuotes(QString symbol, DateRange &rang);
    bool isDownloading(QString symbol);
protected:
    void run();
signals:
    void downloadDone(QString,QString);
};

#endif // YAHOOHTTPAGENT_H
