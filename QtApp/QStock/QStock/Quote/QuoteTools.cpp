#include "QuoteTools.h"
#include <cstring>
#include <cstdio>

QString QuoteTools::symbolA2Yahoo(QString aStr)
{
    /* szXXXXXX or shXXXXXX */
    QString tok("sz");
    int start = aStr.indexOf(tok,Qt::CaseInsensitive);
    if(start != 0){
        tok = QString("sh");
        start = aStr.indexOf(tok,Qt::CaseInsensitive);
        if(start != 0){
            return QString::null;
        }
        tok = QString("ss");
    }
    return aStr.right(aStr.length()-tok.length())+"."+tok;
}

QString QuoteTools::genFilename(QString symbol)
{
    return symbol+".csv";;
}

QString QuoteTools::getDownloadDir()
{
    return QString("./Downloads");
}

QString QuoteTools::yahooHistoryItem2InfoString(YahooHistoryItem &item)
{
    QString date_str = item.date.toString("yyyy-MM-dd Close:");

#if 0
    date_str += QString::number(item.close,'f',2);
    date_str += ", Open:";
    date_str += QString::number(item.open,'f',2);
    date_str += ", High:";
    date_str += QString::number(item.high,'f',2);
    date_str += ", Low:";
    date_str += QString::number(item.low,'f',2);
    date_str += ", Volume:";
    date_str += QString::number(item.volume,'f',2);
    date_str += ", Adj-Close:";
    date_str += QString::number(item.adj,'f',2);
#else
    const static int size = 256;
    char str[size];
    memset(str,0,size);
    sprintf(str,"%.02f, Open:%.02f, High:%.02f, Low:%.02f, Volume:%.02f, Adj-Close:%.02f",
             item.close, item.open, item.high, item.low, item.volume, item.adj);
    date_str.append(str);
#endif
    return date_str;
}
