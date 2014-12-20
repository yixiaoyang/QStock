#include "QuoteTools.h"

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
