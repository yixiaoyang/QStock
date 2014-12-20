#ifndef YAHOOHTTPAGENT_H
#define YAHOOHTTPAGENT_H

#include <QThread>
#include <QList>

#include "types.h"
#include "CurlHttpAgent.h"
#include "Quote/DateRange.h"

class YahooHttpAgent : public QThread
{
    Q_OBJECT
private:
    typedef struct _DownloadListItem{
        QString symbol;
        QString url;
        QString filename;
    }DownloadListItem;

    QString urlPrefix;
    QString downloadDir;

    QList<DownloadListItem> downloadList;

    CurlHttpAgent curl;
    void appendToDownloadList(QString symbol, QString& url, QString& filename);
public:
    YahooHttpAgent();
    ~YahooHttpAgent();

    STATUS downloadQuotes(QString symbol, DateRange &rang);
protected:
    void run();
signals:
    void downloadDone(QString,QString);
};

#endif // YAHOOHTTPAGENT_H
