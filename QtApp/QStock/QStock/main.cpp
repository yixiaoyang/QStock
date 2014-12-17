#include "QStockMainWindows.h"
#include <QApplication>
#include <QTextCodec>

#include <iostream>
#include "Http/CurlHttpAgent.h"
#include "./quote/quote.h"

void test_curl_http(){
    CurlHttpAgent agent;
    agent.downloadURL("http://ichart.yahoo.com/table.csv?s=002065.sz&a=08&b=25&c=2010&d=09&e=8&f=2010&g=d","002065.sz.csv");
}

void test_quote(){
    std::string petr4Quotes = quote::getLatestQuotesCsv
           ("petr4.sa", {quote::QuoteType::symbol,
                         quote::QuoteType::name,
                         quote::QuoteType::lastTradePriceOnly,
                         quote::QuoteType::lastTradeDate,
                         quote::QuoteType::lastTradeTime});
    std::cout << petr4Quotes << std::endl;
    // quote ranges can be daily, weekly, monthly, or dividends only
    std::string petr4HistoricalPrices = quote::getHistoricalQuotesCsv("002065.sz",
                                                                      2014, 1, 1,
                                                                      2014, 12, 1,
                                                                      quote::RangeType::daily);
    std::cout << petr4HistoricalPrices << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    /* TODO: */
    //test_curl_http();
    test_quote();

    QStockMainWindows w;
    w.show();

    return a.exec();
}
