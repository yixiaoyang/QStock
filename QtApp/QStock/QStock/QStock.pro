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

SOURCES += main.cpp\
    QStockMainWindows.cpp \
    Data/StockData.cpp \
    Data/Serialize.cpp \
    Data/HistoryDB.cpp \
    Http/QHttpAgent.cpp \
    Dialog/AboutDialog.cpp

HEADERS  += QStockMainWindows.h \
    types.h\
    Data/StockData.h \
    Data/Serialize.h \
    Data/HistoryDB.h \
    Http/QHttpAgent.h \
    Dialog/AboutDialog.h

FORMS    += QStockMainWindows.ui \
    Dialog/AboutDialog.ui

RESOURCES += \
    resources/iconRes.qrc
