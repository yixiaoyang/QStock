#ifndef HISTORYDB_H
#define HISTORYDB_H

#include <QMap>
#include "HistoryDBItem.h"

typedef QMap<QString,HistoryDBItem> HistoryDBMap;
class HistoryDB
{
private:
    HistoryDBMap historyMap;

public:
    HistoryDB();
    ~HistoryDB();

    STATUS tryToInsertItem(QString symbol);
    const YahooHistoryItems* getYahooHistoryItems(QString symbol);
    HisStatistics getYahooHistoryStats(QString symbol);
};

#endif // HISTORYDB_H
