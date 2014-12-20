#ifndef QUOTETOOLS_H
#define QUOTETOOLS_H

#include <QString>
#include "types.h"
#include <QDateTime>
#include "Data/YahooHistoryItem.h"

class QuoteTools
{
public:
    static QString symbolA2Yahoo(QString aStr);
    static QString genFilename(QString symbol);
    static QString getDownloadDir();
    static QString yahooHistoryItem2InfoString(YahooHistoryItem& item);
};

#endif // QUOTETOOLS_H
