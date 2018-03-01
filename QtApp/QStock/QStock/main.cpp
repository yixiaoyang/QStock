#include "QStockMainWindows.h"
#include <QApplication>
#include <QTextCodec>

#include "includes.h"
#include "types.h"
#include <iostream>
#include "Http/CurlHttpAgent.h"


/***********************************************************/
/* Local Static Data                                       */
/***********************************************************/
LOCAL int _debug_level = DBG_DEBUG;

LOCAL UCM l_ucm;
LOCAL UCM* l_ucm_ptr = &l_ucm;

/***********************************************************/
/* Test                                                    */
/***********************************************************/
void test_curl_http(){
    CurlHttpAgent agent;
    agent.downloadURL("http://ichart.yahoo.com/table.csv?s=002065.sz&a=08&b=25&c=2010&d=09&e=8&f=2010&g=d","002065.sz.csv");
}

/***********************************************************/
/* Global                                                  */
/***********************************************************/
PUBLIC int g_debugLevel()
{
    return _debug_level;
}

PUBLIC UCM* g_getUcm()
{
    return l_ucm_ptr;
}

/***********************************************************/
/* Local Static Data                                       */
/***********************************************************/\
LOCAL STATUS load_data()
{
    STATUS ret = STATUS_OK;
    l_ucm_ptr->loadUserConfig();
    return ret;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    qRegisterMetaType<Message>("Message&");
    qRegisterMetaType<Message>("Message");

    /* init */
    load_data();

    QStockMainWindows w;
    w.show();

    return a.exec();
}
