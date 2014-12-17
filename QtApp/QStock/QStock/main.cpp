#include "QStockMainWindows.h"
#include <QApplication>
#include <QTextCodec>

#include <iostream>
#include "Http/CurlHttpAgent.h"

void test_curl_http(){
    CurlHttpAgent agent;
    agent.downloadURL("http://ichart.yahoo.com/table.csv?s=002065.sz&a=08&b=25&c=2010&d=09&e=8&f=2010&g=d","002065.sz.csv");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    /* TODO: */
    //test_curl_http();

    QStockMainWindows w;
    w.show();

    return a.exec();
}
