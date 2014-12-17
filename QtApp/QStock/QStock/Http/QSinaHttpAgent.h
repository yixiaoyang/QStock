#ifndef QHTTPAGENT_H
#define QHTTPAGENT_H

#include <QThread>
#include <QHttp>
#include <QString>
#include <QByteArray>
#include "Data/StockData.h"

class QSinaHttpAgent : public QThread
{
    Q_OBJECT
private:
    QHttp *http;
    QString url;
    QString host;

    StockIdDB* idb;
    int eachFetchCnt;
    void updateUri();
public:
    QSinaHttpAgent(QString host="");
    ~QSinaHttpAgent();

    QString uri;
    char sep;
    QByteArray buffer;

    STATUS fetchStockData();
    void setIdb(StockIdDB *value);
private slots:
    /* sina http slot */
    void slot_httpDone(bool);
    void on_dataReadProgress(int,int);
    void on_readyRead(QHttpResponseHeader);
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
