#include "HistoryDBItem.h"
#include "Quote/QuoteTools.h"

#include <QFile>
#include <QTextStream>

#include <iostream>

HisStatistics HistoryDBItem::getStats() const
{
    return stats;
}

STATUS HistoryDBItem::loadItemsFromFile()
{
    QString filename = QuoteTools::getDownloadDir()+"/"+QuoteTools::genFilename(this->symbol);
    QFile file(filename);
    QTextStream txtInput(&file);

    QString lineStr;
    YahooHistoryItem item;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        /* TODO: use exception */
        debug_print(DBG_DEBUG,"[HistoryDBItem::loadItemsFromFile]: Open historyd svc file %s failed.",
                    filename.toStdString().c_str());
        return STATUS_FAILED;
    }

    /* skip the first line */
    lineStr = txtInput.readLine();
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        if(YahooHistoryItemHelper::string2item(lineStr,item) != STATUS_OK){
            debug_print(DBG_DEBUG,"Parsing Yahoo Quote String Failed");
            continue;
        }

        /* statics */
        if(item.close > stats.maxClose)
            stats.maxClose = item.close;
        if(item.close < stats.minClose)
            stats.minClose = item.close;

        itemsVector.append(item);
    }

    file.close();
    return STATUS_OK;
}

YahooHistoryItems *HistoryDBItem::getItems()
{
    return &itemsVector;
}

HistoryDBItem::HistoryDBItem(QString s):symbol(s)
{
    stats.maxClose = -1.00;
    stats.minClose = 999999999999.00;
}

HistoryDBItem::~HistoryDBItem()
{
    itemsVector.clear();
}
