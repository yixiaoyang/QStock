#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T14:15:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QStock
TEMPLATE = app

include(./lib/jsoncpp/jsoncpp.pri)
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
    Http/CurlHttpAgent.cpp

HEADERS  += QStockMainWindows.h \
    types.h\
    Data/StockData.h \
    Data/Serialize.h \
    Data/HistoryDB.h \
    Http/QHttpAgent.h \
    Dialog/AboutDialog.h \
    Http/CurlHttpAgent.h

FORMS    += QStockMainWindows.ui \
    Dialog/AboutDialog.ui

RESOURCES += \
    resources/iconRes.qrc
