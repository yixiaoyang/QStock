#ifndef STOCKDATA_H
#define STOCKDATA_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QObject>
#include <QMutex>
#include <sstream>

#include "types.h"
#include "Serialize.h"

using namespace std;

#define STOCK_DATE_LEN      (16)
#define STOCK_ID_LEN        (16)
#define STOCK_NAME_LEN      (32)

enum{
    /* 0-4 */
    SINA_ITEMS_ID,
    SINA_ITEMS_TOPEN,
    SINA_ITEMS_YCLOSE,
    SINA_ITEMS_CURRENT,
    SINA_ITEMS_THIGH,

    /* 5-9 */
    SINA_ITEMS_TLOW,
    SINA_ITEMS_B1,
    SINA_ITEMS_S1,
    SINA_ITEMS_HANDS,
    SINA_ITEMS_VOLUME,

    /* 10-19 */
    SINA_ITEMS_B1CNT,   /* hands*/
    SINA_ITEMS_B1PRI,
    SINA_ITEMS_B2CNT,
    SINA_ITEMS_B2PRI,
    SINA_ITEMS_B3CNT,
    SINA_ITEMS_B3PRI,
    SINA_ITEMS_B4CNT,
    SINA_ITEMS_B4PRI,
    SINA_ITEMS_B5CNT,
    SINA_ITEMS_B5PRI,

    /* 20-29 */
    SINA_ITEMS_S1CNT,   /* hands*/
    SINA_ITEMS_S1PRI,
    SINA_ITEMS_S2CNT,
    SINA_ITEMS_S2PRI,
    SINA_ITEMS_S3CNT,
    SINA_ITEMS_S3PRI,
    SINA_ITEMS_S4CNT,
    SINA_ITEMS_S4PRI,
    SINA_ITEMS_S5CNT,
    SINA_ITEMS_S5PRI,

    /* 30-32*/
    SINA_ITEMS_DATE,
    SINA_ITEMS_HMS,
    SINA_ITEMS_UNKOWN,

    SINA_ITEMS_MAX
};

typedef struct _StockInfo{
    //char id[STOCK_ID_LEN];
    //char name[STOCK_NAME_LEN];
    //char date[STOCK_DATE_LEN];
    QString id;
    QString name;
    QString date;

    /* today */
    double current;
    double open;
    double high;
    double low;

    /* last day */
    double close;
    double volume;
    int hands;
    double adj;
    double adjVal;

    double lastCurrent;

    /* bool */
    bool isHl;
    bool showAdjVal;
}StockInfo;

typedef QMap<QString,StockInfo> StockRuntimeDB;
typedef QVector<QString> StockIdDB;

class StockData :  public QObject, public Serialize
{
friend class UCM;
    Q_OBJECT
public:
    enum{
        ERR_CODE_VOID,
        ERR_CODE_NOT_EXISTED
    };
private:
    QMutex mutex;

    StockRuntimeDB db;
    StockIdDB idb;
    std::stringstream sinaHttpStream;

    void showErrorMessage(QString errStr);
    STATUS addId(QString id);
    STATUS removeId(QString id);
public:
    StockData(QObject *parent = 0);
    ~StockData();

    /* TODO: Do it by UCM */
    STATUS updateInfo(const char* string);
    STATUS topId(QString id);
    STATUS hightlightId(QString id);

    /* get interface */
    StockRuntimeDB* getDB();
    StockIdDB* getIDB();

    // Serialize interface
public:
    Json::Value serialize();
    STATUS unSerialize(Json::Value &val);
    std::string getNodeName();
signals:
    void sig_idbChanged();
};

#endif // STOCKDATA_H
