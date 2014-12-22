#include "ucm.h"
#include <QDir>
#include <fstream>
#include <iostream>
#include "includes.h"

UCM::UCM() :IPublisher()
{
    this->userCfgFile =  string("./") + USERCONFIG_FILE;
}

UCM::~UCM()
{
}

STATUS UCM::loadUserConfig()
{
    QDir dir;
    ifstream fin;
    Json::Reader reader;
    Json::Value val;
    fin.open (this->userCfgFile.c_str (), ios::in);

    debug_print(DBG_DEBUG,"[StockData::loadUserConfig()]: %s/%s",
                dir.currentPath().toStdString().c_str(),
                this->userCfgFile.c_str ());
    if (!reader.parse(fin, root, false)){
        qErrnoWarning("[StockData::loadUserConfig()]: root json data null");
        return STATUS_FAILED;
    }

    fin.close ();

    /* unserialize stock data */
    val = root[stock_data.getNodeName()];
    if(val!=Json::nullValue){
        stock_data.unSerialize (val);
    }else{
        qErrnoWarning("[StockData::loadUserConfig]: userconfig json data null");
    }

    fin.close ();

    return STATUS_OK;
}


STATUS UCM::saveUserConfig()
{
    std::ofstream fout;
    fout.open (userCfgFile.c_str (),std::ios::out);
    root[stock_data.getNodeName ()] = stock_data.serialize ();
    fout << root;
    fout.close ();

    return STATUS_OK;
}

StockData *UCM::getStockData()
{
    return &stock_data;
}

HistoryDB *UCM::getHistoryDB()
{
    return &history_db;
}

StockIdDB *UCM::getIDB()
{
    return &stock_data.idb;
}

int UCM::handleMsg(Message &msg, void* )
{
    int ret = STATUS_OK;
    switch(msg.mhdr.mid){
    case STOCK_DATA_CHGED:{
        if(msg.mhdr.op == MSG_OP_ADD){
            ret = stock_data.addId(QString(msg.mhdr.opt.asString));
        }else if(msg.mhdr.op == MSG_OP_DEL){
            ret = stock_data.removeId(QString(msg.mhdr.opt.asString));
        }else{
            ret = STATUS_FAILED;
        }
        break;
    }
    case STOCK_DATA_SAVE:{
        ret = this->saveUserConfig();
        break;
    }
    default:
        ret = STATUS_ERR_NOT_EXISTED;
        break;
    }
    return ret;
}

