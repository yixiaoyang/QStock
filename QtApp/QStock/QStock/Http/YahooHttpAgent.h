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
        QString url;
        QString filename;
    }DownloadListItem;

    QString urlPrefix;
    QString downloadDir;

    QList<DownloadListItem> downloadList;

    CurlHttpAgent curl;
    void appendToDownloadList(QString& url, QString& filename);
public:
    YahooHttpAgent();
    ~YahooHttpAgent();

    STATUS downloadQuotes(QString key, DateRange &rang);
protected:
    void run();
private slots:
    void slot_downloadDone(int);
signals:
    void downloadDone(int);
};

#endif // YAHOOHTTPAGENT_H
