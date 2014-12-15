#include "StockData.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>

/*
0：”大秦铁路”，股票名字；
1：”27.55″，今日开盘价；
2：”27.25″，昨日收盘价；
3：”26.91″，当前价格；
4：”27.55″，今日最高价；
5：”26.20″，今日最低价；
6：”26.91″，竞买价，即“买一”报价；
7：”26.92″，竞卖价，即“卖一”报价；
8：”22114263″，成交的股票数，由于股票交易以一百股为基本单位，所以在使用时，通常把该值除以一百；
9：”589824680″，成交金额，单位为“元”，为了一目了然，通常以“万元”为成交金额的单位，所以通常把该值除以一万；
10：”4695″，“买一”申请4695股，即47手；
11：”26.91″，“买一”报价；
12：”57590″，“买二”
13：”26.90″，“买二”
14：”14700″，“买三”
15：”26.89″，“买三”
16：”14300″，“买四”
17：”26.88″，“买四”
18：”15100″，“买五”
19：”26.87″，“买五”
20：”3100″，“卖一”申报3100股，即31手；
21：”26.92″，“卖一”报价
(22, 23), (24, 25), (26,27), (28, 29)分别为“卖二”至“卖四的情况”
30：”2008-01-11″，日期；
31：”15:05:32″，时间；
32:
*/

//static QString testString="var hq_str_sh601006=\"大秦铁路,10.29,10.27,10.22,10.60,10.15,10.20,10.21,144962333,1500819855,589930,10.20,415158,10.19,492831,10.18,130700,10.17,265000,10.16,24351,10.21,10000,10.23,95512,10.24,131315,10.25,104000,10.26,2014-12-12,15:03:04,00\";var hq_str_sz002065=\"东华软件,19.20,19.09,19.99,20.30,19.10,19.99,20.00,60413170,1206093564.28,292020,19.99,144717,19.98,34448,19.97,70830,19.96,17900,19.95,135411,20.00,38700,20.01,50466,20.02,57826,20.03,44300,20.04,2014-12-12,15:55:36,00\";";
static QString l_labelPrefix("var hq_str_");

void StockData::showErrorMessage( QString errStr)
{
    QMessageBox::information(NULL, "ERROR", errStr,
        QMessageBox::Ok, QMessageBox::Ok);
}

StockData::StockData(QObject* parent) : QObject(parent),Serialize()
{
    this->userCfgFile =  string("./") + USERCONFIG_FILE;
}

StockData::~StockData()
{

}

STATUS StockData::updateInfo(const char* string)
{
    if(!string){
        return STATUS_FAILED;
    }
    QString name;
    QString id;

    StockInfo info;
    QString str(string);
    QStringList list = str.split(';',QString::SkipEmptyParts);
    int start = 0;
    int end = 0;
    QString item;

    memset(&info,0,sizeof(StockInfo));

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
                strncpy(info.date,tokens[SINA_ITEMS_DATE].toStdString().c_str(),STOCK_DATE_LEN);
                it.value().open = info.open;
                it.value().high = info.high;
                it.value().low = info.low;
                it.value().close = info.close;
                it.value().volume = info.volume;
                it.value().hands = info.hands;
                it.value().current = info.current;
                it.value().adj = info.adj;
            }
        }else{
            continue;
        }
    }

    return STATUS_OK;
}

STATUS StockData::addId(QString &id)
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
    for(int i =0; i< idb.size(); i++){
        ids += idb[i];
        ids += ",";
    }
    ids.remove(ids.length()-1,1);
    idbVal["idb"]=ids.toStdString();
    return idbVal;
}

STATUS StockData::unSerialize(Json::Value &val)
{
    string idbStr = val["idb"].asString();
    QString idsQStr(idbStr.c_str());
    if(!idsQStr.isEmpty()){
        QStringList list = idsQStr.split(',',QString::SkipEmptyParts);
        for(int i = 0 ;i <list.size(); i++){
            this->idb.append(list.at(i));
        }
    }

    return STATUS_OK;
}

std::string StockData::getNodeName()
{
    return "StockData";
}

STATUS StockData::loadUserConfig()
{
    ifstream fin;
    Json::Reader reader;
    Json::Value val;
    fin.open (this->userCfgFile.c_str (), ios::in);
    if (!reader.parse(fin, root, false)){
        qErrnoWarning("[StockData::loadUserConfig()]: root json data null");
        return STATUS_FAILED;
    }
    fin.close ();

    val = root[this->getNodeName()];
    if(val!=Json::nullValue){
        this->unSerialize (val);
    }else{
        qErrnoWarning("[StockData::loadUserConfig]: userconfig json data null");
    }

    return STATUS_OK;
}

STATUS StockData::saveUserConfig()
{
    ofstream fout;
    fout.open (this->userCfgFile.c_str (), ios::out);
    root[this->getNodeName ()] = this->serialize ();
    fout << root;
    fout.close ();

    return STATUS_OK;
}
