#include "YahooHistoryItem.h"

#include <QStringList>
#include <QDateTime>
#include <QDate>

YahooHistoryItemHelper::YahooHistoryItemHelper()
{
}

STATUS YahooHistoryItemHelper::string2item(QString &lineStr, YahooHistoryItem &item)
{
    /* 2014-05-05,37.13,38.20,36.70,37.88,3593700,18.77 */
    QStringList tokens = lineStr.split(',',QString::SkipEmptyParts);

    /*Date,Open,High,Low,Close,Volume,Adj Close*/
    if(tokens.size() != YahooHistoryItemMax){
        return STATUS_FAILED;
    }
    item.date = QDate::fromString(tokens[YahooHistoryItemDate], "yyyy-MM-dd");
    item.open = tokens[YahooHistoryItemOpen].toDouble();
    item.high = tokens[YahooHistoryItemHigh].toDouble();
    item.low = tokens[YahooHistoryItemLow].toDouble();
    item.close = tokens[YahooHistoryItemClose].toDouble();
    item.volume = tokens[YahooHistoryItemVolume].toDouble();
    item.adj = tokens[YahooHistoryItemMaxAdj].toDouble();
    return STATUS_OK;
}

