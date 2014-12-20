#ifndef HAHOOHISTORYITEM_H
#define HAHOOHISTORYITEM_H

#include "types.h"
#include <QString>
#include <QDate>

enum{
    YahooHistoryItemDate,
    YahooHistoryItemOpen,
    YahooHistoryItemHigh,
    YahooHistoryItemLow,
    YahooHistoryItemClose,
    YahooHistoryItemVolume,
    YahooHistoryItemMaxAdj,
    YahooHistoryItemMax
};

typedef struct _YahooHistoryItem{
    QDate date;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adj;
}YahooHistoryItem;

class YahooHistoryItemHelper
{
private:
    /* line string: 2014-12-16,38.36,38.62,37.49,38.11,4759700,38.11 */

public:
    YahooHistoryItemHelper();
    static STATUS string2item(QString &lineStr, YahooHistoryItem& item);
};

#endif // HAHOOHISTORYITEM_H
