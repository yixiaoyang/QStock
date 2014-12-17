#include "QuoteTools.h"

QString QuoteTools::KeyA2Yahoo(QString aStr)
{
    /* szXXXXXX or shXXXXXX */
    QString tok("sz");
    int start = aStr.indexOf(tok,Qt::CaseInsensitive);
    if(start != 0){
        tok = QString("ss");
        start = aStr.indexOf(tok,Qt::CaseInsensitive);
        if(start != 0){
            return QString::null;
        }
    }
    return aStr.right(aStr.length()-tok.length())+"."+tok;
}
