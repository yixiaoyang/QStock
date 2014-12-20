#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T14:15:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QStock
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

include(./lib/jsoncpp/jsoncpp.pri)

win32{
    LIBS += -L $${PWD}\lib\curl
    LIBS += -DCURL_STATICLIB -lcurl  -lws2_32 -lwldap32
}
unix{
    LIBS += -L  $${PWD}\lib\curl\linux
    LIBS +=  -DCURL_STATICLIB -lcurl
}

INCLUDEPATH += ./lib/curl/include
DEFINES += CURL_STATICLIB

SOURCES += main.cpp\
    QStockMainWindows.cpp \
    Data/StockData.cpp \
    Data/Serialize.cpp \
    Data/HistoryDB.cpp \
    Dialog/AboutDialog.cpp \
    Http/CurlHttpAgent.cpp \
    Http/QSinaHttpAgent.cpp \
    Widget/QQuoteWavesWidget.cpp \
    Http/YahooHttpAgent.cpp \
    Quote/QuoteTools.cpp \
    Quote/DateRange.cpp \
    Data/HistoryDBItem.cpp \
    Data/YahooHistoryItem.cpp \
    Ucm/ipublisher.cpp \
    Ucm/isubscriber.cpp \
    Ucm/message.cpp \
    Ucm/ucm.cpp

HEADERS  += QStockMainWindows.h \
    types.h\
    Data/StockData.h \
    Data/Serialize.h \
    Data/HistoryDB.h \
    Dialog/AboutDialog.h \
    Http/CurlHttpAgent.h \
    Http/QSinaHttpAgent.h \
    Widget/QQuoteWavesWidget.h \
    Http/YahooHttpAgent.h \
    Quote/QuoteTools.h \
    Quote/DateRange.h \
    Data/HistoryDBItem.h \
    Data/YahooHistoryItem.h \
    Ucm/ipublisher.h \
    Ucm/isubscriber.h \
    Ucm/message.h \
    Ucm/ucm.h \
    includes.h

FORMS    += QStockMainWindows.ui \
    Dialog/AboutDialog.ui \
    Widget/qquotewaveswidget.ui

RESOURCES += \
    resources/iconRes.qrc
