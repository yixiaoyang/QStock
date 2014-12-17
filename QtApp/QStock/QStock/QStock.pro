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
include(./lib/quote/src/quote.pri)


win32{
    LIBS += -L  $${PWD}\lib\curl
    LIBS +=  -DCURL_STATICLIB -lcurl  -lws2_32 -lwldap32
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
    Http/QHttpAgent.cpp \
    Dialog/AboutDialog.cpp \
    Http/CurlHttpAgent.cpp \
#    quote/string_util.cpp \
#    quote/Exception.cpp \
#    quote/curl_util.cpp \
#    quote/core.cpp \
#    quote/conversion.cpp

HEADERS  += QStockMainWindows.h \
    types.h\
    Data/StockData.h \
    Data/Serialize.h \
    Data/HistoryDB.h \
    Http/QHttpAgent.h \
    Dialog/AboutDialog.h \
    Http/CurlHttpAgent.h \
#    quote/string_util.h \
#    quote/RangeType.h \
#    quote/QuoteTypeWrapper.h \
#    quote/QuoteType.h \
#    quote/quote.h \
#    quote/MultipleInheritancePack.h \
#    quote/Exception.h \
#    quote/curl_util.h \
#    quote/core.h \
#    quote/conversion.h

FORMS    += QStockMainWindows.ui \
    Dialog/AboutDialog.ui

RESOURCES += \
    resources/iconRes.qrc
