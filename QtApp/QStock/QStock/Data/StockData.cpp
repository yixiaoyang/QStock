#include "StockData.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>

static QString l_labelPrefix("var hq_str_");

void StockData::showErrorMessage( QString errStr)
{
    QMessageBox::information(NULL, "ERROR", errStr,
        QMessageBox::Ok, QMessageBox::Ok);
}

StockData::StockData(QObject* parent) : QObject(parent),Serialize()
{

}

StockData::~StockData()
{

}

STATUS StockData::updateInfo(const char* string)
{
    if(!string){
        return STATUS_FAILED;
    }
    bool isFirstLoading = false;
    QString name;
    QString id;

    StockInfo info;
    QString str(string);
    QStringList list = str.split(';',QString::SkipEmptyParts);
    int start = 0;
    int end = 0;
    QString item;

    memset(&info,0,sizeof(StockInfo));
    info.lastCurrent = -1.00;

    for(int cnt = 0; cnt < list.count(); cnt++){
        item = list.at(cnt);
        if(item.length() <= l_labelPrefix.length()){
            continue;
        }
        start = item.indexOf('"');
        end = item.lastIndexOf('"');

        /* skip " itself */
        start++;

        if((end >= start)&&(end != -1)){
            QString infos = item.mid(start,end-start);
            QStringList tokens = infos.split(',',QString::SkipEmptyParts);

            /*var hq_str_sh601006="*/
            int id_start = item.indexOf(l_labelPrefix);
            int id_end = item.indexOf('=');
            id = item.mid(id_start+l_labelPrefix.length(),id_end-id_start-l_labelPrefix.length());

            if(tokens.isEmpty())
                name = "unknown";
            else
                name = tokens[0];

            if(start == end){
                showErrorMessage(QString("Stock id ")+id+" name "+name+QString(" not existed!"));
                this->removeId(id);
                continue;
            }
            if(id.isEmpty() || tokens.size() < SINA_ITEMS_MAX){
                qWarning("tokens should have more than 32 items");
                showErrorMessage(QString("Stock id ")+id+" name "+name+QString(" parsed failed!"));
                this->removeId(id);
                continue;
            }
            strncpy(info.name,name.toStdString().c_str(),STOCK_NAME_LEN);
            strncpy(info.id,id.toStdString().c_str(),STOCK_ID_LEN);
            strncpy(info.date,tokens[SINA_ITEMS_DATE].toStdString().c_str(),STOCK_DATE_LEN);
            info.open = tokens[SINA_ITEMS_TOPEN].toDouble();
            info.high = tokens[SINA_ITEMS_THIGH].toDouble();
            info.low = tokens[SINA_ITEMS_TLOW].toDouble();
            info.close = tokens[SINA_ITEMS_YCLOSE].toDouble();
            info.volume = tokens[SINA_ITEMS_VOLUME].toDouble();
            info.hands = tokens[SINA_ITEMS_HANDS].toInt();
            info.current = tokens[SINA_ITEMS_CURRENT].toDouble();
            if(info.open < 0.00001 && info.open > -0.00001){
                info.adj = 0.0;
            }else{
                info.adj = (info.current-info.close)/info.close;
            }
            StockRuntimeDB::iterator it = db.find(id);
            if(it == db.end()){
                db.insert(id,info);
            }else{
                if(it.value().name[0]==0){
                    isFirstLoading = true;
                    strncpy(it.value().name,info.name,STOCK_ID_LEN);
                }
                if(it.value().id[0]==0)
                    strncpy(it.value().id,info.id,STOCK_NAME_LEN);
                if(it.value().date[0]==0)
                    strncpy(it.value().date, info.date,STOCK_DATE_LEN);

                strncpy(info.date,tokens[SINA_ITEMS_DATE].toStdString().c_str(),STOCK_DATE_LEN);
                it.value().open = info.open;
                it.value().high = info.high;
                it.value().low = info.low;
                it.value().close = info.close;
                it.value().volume = info.volume;
                it.value().hands = info.hands;
                it.value().lastCurrent = it.value().current;
                it.value().current = info.current;
                it.value().adj = info.adj;
            }
        }else{
            continue;
        }
    }

    if(isFirstLoading){
        emit sig_idbChanged();
    }
    return STATUS_OK;
}

STATUS StockData::addId(QString id)
{
    if(idb.indexOf(id) < 0){
        idb.append(id);
        emit sig_idbChanged();
        return STATUS_OK;
    }else{
        return STATUS_ERR_EXISTED;
    }
}

STATUS StockData::removeId(QString id)
{
    int index = idb.indexOf(id);
    if(index < 0){
        return STATUS_ERR_NOT_EXISTED;
    }else{
        idb.remove(index);
        db.remove(id);
        emit sig_idbChanged();
        return STATUS_OK;
    }
}

STATUS StockData::topId(QString id)
{
    int index = idb.indexOf(id);
    if(index < 0){
        return STATUS_ERR_NOT_EXISTED;
    }else{
        if(index != 0){
            idb.remove(index);
            idb.push_front(id);
            emit sig_idbChanged();
        }else{
            /* not changed */
        }
        return STATUS_OK;
    }
    return STATUS_OK;
}

STATUS StockData::hightlightId(QString id)
{
    StockRuntimeDB::iterator it = db.find(id);
    if(it != db.end()){
        if(it.value().isHl){
             it.value().isHl = false;
        }else{
            it.value().isHl = true;
        }
    }else{
        return STATUS_ERR_NOT_EXISTED;
    }
    return STATUS_OK;
}

StockRuntimeDB *StockData::getDB()
{
    return &db;
}

StockIdDB *StockData::getIDB()
{
    return &idb;
}

Json::Value StockData::serialize()
{
    Json::Value idbVal;
    QString ids;
    QString hls;
    StockRuntimeDB::iterator db_it = db.begin();

    for(int i =0; i< idb.size(); i++){
        ids += idb[i];
        ids += ",";
    }
    ids.remove(ids.length()-1,1);
    idbVal["idb"]=ids.toStdString();

    while(db_it != db.end()){
        if(db_it.value().isHl){
            hls += db_it.key();
            hls += ",";
        }
        db_it++;
    }
    hls.remove(hls.length()-1,1);
    idbVal["hl"]=hls.toStdString();
    return idbVal;
}

STATUS StockData::unSerialize(Json::Value &val)
{
    string idbStr = val["idb"].asString();
    string hlStr = val["hl"].asString();

    QString idsQStr(idbStr.c_str());
    QString hlQStr(hlStr.c_str());

    StockInfo info;
    if(!idsQStr.isEmpty()){
        QStringList list = idsQStr.split(',',QString::SkipEmptyParts);
        for(int i = 0 ;i <list.size(); i++){
            this->idb.append(list.at(i));

            memset(&info,0,sizeof(StockInfo));
            this->db.insert(list.at(i),info);
        }
    }

    if(!hlQStr.isEmpty()){
        QStringList list = hlQStr.split(',',QString::SkipEmptyParts);
        for(int i = 0; i < list.size(); i++){
            StockRuntimeDB::iterator db_it = db.find(list.at(i));
            if(db_it != db.end()){
                db_it.value().isHl = true;
            }
        }
     }

    return STATUS_OK;
}

std::string StockData::getNodeName()
{
    return "StockData";
}

