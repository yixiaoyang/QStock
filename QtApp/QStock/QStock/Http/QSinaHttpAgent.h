#ifndef QHTTPAGENT_H
#define QHTTPAGENT_H

#include <QThread>
#include <QNetworkAccessManager>
#include <QString>
#include <QByteArray>
#include <QList>
#include "Data/StockData.h"

class QSinaHttpAgent : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *http;
    QString host;

    StockIdDB* idb;
    int eachFetchCnt;
    void updateUri();

    void request(QString url);
public:
    QSinaHttpAgent(QString host="");
    ~QSinaHttpAgent();

    QString uri;
    char sep;
    QByteArray buffer;
    int requestCount;

    STATUS fetchStockData();
    void setIdb(StockIdDB *value);
    void setHttp(QNetworkAccessManager *value);

private slots:
    /* sina http slot */
    void slot_finished(QNetworkReply*);

    // QThread interface
protected:
    void run();
signals:
    void readyRead();
    void httpDone(bool);
    void dataReadProgress(int,int);
    void readyRead(QByteArray);
};

#endif // QHTTPAGENT_H
