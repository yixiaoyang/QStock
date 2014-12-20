#ifndef QUOTETOOLS_H
#define QUOTETOOLS_H

#include <QString>
#include "types.h"
#include <QDateTime>

class QuoteTools
{
public:
    static QString symbolA2Yahoo(QString aStr);
    static QString genFilename(QString symbol);
    static QString getDownloadDir();
};

#endif // QUOTETOOLS_H
