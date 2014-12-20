#ifndef HISTORYDBITEM_H
#define HISTORYDBITEM_H

#include <QVector>
#include "types.h"
#include "YahooHistoryItem.h"

typedef QVector<YahooHistoryItem> YahooHistoryItems;
typedef struct _HisStatistics{
    double maxClose;
    double minClose;
}HisStatistics;

class HistoryDBItem
{
    friend class HistoryDB;
private:
    QString symbol;
    HisStatistics stats;
    YahooHistoryItems itemsVector;

    STATUS loadItemsFromFile();
    YahooHistoryItems* getItems();
public:
    HistoryDBItem(QString s);
    ~HistoryDBItem();

    HisStatistics getStats() const;
};

#endif // HISTORYDBITEM_H
