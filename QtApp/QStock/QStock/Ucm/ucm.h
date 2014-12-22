/*
 * (C) Copyright 2013-2015. All rights reserved.
 * Uniform Configuration Module.Control all actions on configl load or save.
 *
 * @brief   Uniform Configuration Module.Control all actions on configl load or save.
 * @file    ucm.h
 * @version 1.0
 * @author  Leon
 * @note
 *      -Create by Leon<hityixiaoyang@gmail.com> on 27Jun14.
 */
#ifndef UCM_H
#define UCM_H

#include <string>

#include "json/json.h"
#include "types.h"
#include "ipublisher.h"
#include "isubscriber.h"
#include "message.h"
#include <QObject>
#include <QThread>

#include "Data/StockData.h"
#include "Data/HistoryDB.h"

#define USERCONFIG_FILE     "user.conf"

class UCM : public IPublisher
{
Q_OBJECT
private:
    std::string userCfgFile;
    Json::Value root;
    Json::Reader reader;

    /* userconfig data */
private:
    StockData stock_data;
    HistoryDB history_db;
public:
    UCM();
    ~UCM();

    /* operation interface */
    STATUS loadUserConfig();
    STATUS saveUserConfig();

    StockData* getStockData();
    HistoryDB* getHistoryDB();
    StockIdDB* getIDB();

    // IPublisher interface
private:
    int handleMsg(Message &msg,void* param=NULL);
    int syncWithRemote(Message &msg, void *param);
};

#endif // UCM_H
