#include "HistoryDB.h"

HistoryDB::HistoryDB()
{
}

HistoryDB::~HistoryDB()
{
    historyMap.clear();
}

STATUS HistoryDB::tryToInsertItem(QString symbol)
{
    STATUS ret = STATUS_OK;
    HistoryDBMap::iterator it = historyMap.find(symbol);
    if(it != historyMap.end()){
        return STATUS_ERR_EXISTED;
    }

    HistoryDBItem item(symbol);
    if((ret = item.loadItemsFromFile()) != STATUS_OK){
        return ret;
    }
    historyMap.insert(symbol,item);

    return ret;
}

const YahooHistoryItems *HistoryDB::getYahooHistoryItems(QString symbol)
{
    HistoryDBMap::iterator it = historyMap.find(symbol);
    if(it == historyMap.end()){
        debug_print(DBG_DEBUG,"History of %s not existed",symbol.toStdString().c_str());
        return NULL;
    }
    return it.value().getItems();
}

HisStatistics HistoryDB::getYahooHistoryStats(QString symbol)
{
    HisStatistics stat;
    HistoryDBMap::iterator it = historyMap.find(symbol);

    memset(&stat,0,sizeof(HisStatistics));
    if(it == historyMap.end()){
        debug_print(DBG_DEBUG,"History of %s not existed",symbol.toStdString().c_str());
        return stat;
    }
    return it.value().getStats();
}
