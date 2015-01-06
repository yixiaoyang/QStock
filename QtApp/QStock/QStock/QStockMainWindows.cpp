#include "QStockMainWindows.h"
#include "ui_QStockMainWindows.h"
#include <QHttp>
#include <QUrl>
#include <QMainWindow>
#include <QTextCodec>
#include <QMessageBox>

#include <iostream>
#include "Data/StockData.h"
#include "Dialog/AboutDialog.h"
#include "Quote/DateRange.h"
#include "includes.h"

QStockMainWindows::QStockMainWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QStockMainWindows)
{
    ui->setupUi(this);

    g_getUcm()->registerFor(this,ISUBSCRIBER_ID_QSTOCK_MAIN_WINDOWS,this->objectName());

    ui->runtimeTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->runtimeTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_myPositionHistorys->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_myPositionHistorys->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_myPositions->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_myPositions->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_myPosProfile->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_myPosProfile->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    stock_data = NULL;
    stock_data = g_getUcm()->getStockData();
    assert(stock_data != NULL);

    history_db = NULL;
    history_db = g_getUcm()->getHistoryDB();
    assert(history_db != NULL);

    view_setting.falling = Qt::darkGreen;
    view_setting.rising = Qt::red;
    view_setting.hightlightBkg = Qt::yellow;
    view_setting.topBkg = Qt::darkGreen;
    view_setting.urlArrayCnt = 5;
    view_setting.sysTimerMsec = 5000;

    lastSelRow = -1;
    fetchCnt = 0;
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(fetchCnt);

    connect(stock_data,SIGNAL(sig_idbChanged()),this,SLOT(slot_idbChanged()));

    sysTimer = new QTimer(this);
    connect(sysTimer,SIGNAL(timeout()),this,SLOT(slot_sysTimeFreshed()));
    sysTimer->start(view_setting.sysTimerMsec); /*5s*/

    sinaAgent = new QSinaHttpAgent("hq.sinajs.cn");
    connect(sinaAgent, SIGNAL(httpDone(bool)),this, SLOT(slot_sinaHttpDone(bool)));
    connect(sinaAgent, SIGNAL(dataReadProgress(int,int)),this, SLOT(slot_sinaDataReadProgress(int,int)));
    connect(sinaAgent, SIGNAL(readyRead(QByteArray)),this, SLOT(slot_sinaReadyRead(QByteArray)));
    sinaAgent->setIdb(stock_data->getIDB());

    yahooAgent = new YahooHttpAgent;
    connect(yahooAgent,SIGNAL(downloadDone(QString,QString)),this,SLOT(slot_yahooHttpDownloadDone(QString,QString)));

    ui->runtimeTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget_myPositionHistorys->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget_myPositions->setContextMenuPolicy(Qt::CustomContextMenu);

    runtimePopMenu = new QMenu(ui->runtimeTableWidget);
    runtimeTopAction = new QAction("Place On Top ",this);
    runtimeDelAction = new QAction("Remove ",this);
    runtimeHlAction = new QAction("Hightlight & DisHightlight it",this);
    runtimeDetailAction = new QAction("Detail",this);

    runtimeTopAction->setIcon(QIcon(":/main/icons/top.png"));
    runtimeDelAction->setIcon(QIcon(":/main/icons/del.png"));
    runtimeHlAction->setIcon(QIcon(":/main/icons/highlight.png"));
    runtimeDetailAction->setIcon(QIcon(":/main/icons/waves.png"));

    connect(runtimeTopAction,SIGNAL(triggered()),this,SLOT(slot_runtimeTopAction()));
    connect(runtimeDelAction,SIGNAL(triggered()),this,SLOT(slot_runtimeDelAction()));
    connect(runtimeHlAction,SIGNAL(triggered()),this,SLOT(slot_runtimeHlAction()));
    connect(runtimeDetailAction,SIGNAL(triggered()),this,SLOT(slot_runtimeDetailAction()));

    runtimePopMenu->addAction(runtimeDelAction);
    runtimePopMenu->addAction(runtimeTopAction);
    runtimePopMenu->addAction(runtimeHlAction);
    runtimePopMenu->addAction(runtimeDetailAction);

    connect(ui->runtimeTableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_tblCustomContextMenuRequested(QPoint)));

    fetchStockData();

    ui->widget_wavesfooter->hide();
}

QStockMainWindows::~QStockMainWindows()
{
    sinaAgent->terminate();
    sinaAgent->wait(200);
    yahooAgent->terminate();
    yahooAgent->wait(200);

    g_getUcm()->unRegisterFor(this);

    delete sinaAgent;
    delete ui;
}

/*!!! TODO:  clean these codes, its not gentle !!! */
void QStockMainWindows::updateRuntimeInfo()
{
    StockRuntimeDB* db = stock_data->getDB();
    StockIdDB* idb = stock_data->getIDB();
    StockRuntimeDB::iterator it = db->begin();
    StockIdDB::iterator itIdb = idb->begin();

    StockInfo info;
    QTableWidget* tblWidget = ui->runtimeTableWidget;
    QTableWidgetItem* item;
    int cnt = 0;
    int col = 0;

    if(tblWidget->rowCount() != db->size()){
        tblWidget->setRowCount(db->size());
    }
    for(cnt = 0;itIdb != idb->end(); itIdb++, cnt++){
        it = db->find(*itIdb);
        if(it == db->end()){
            continue;
        }

        col = 0;
        info = it.value();
        /*name,id,date,open,high,low,close,volume,adj*/
        item = new QTableWidgetItem(it.value().name);
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }
        tblWidget->setItem(cnt,col++,item);

        item = new QTableWidgetItem(QString(info.id));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }
#ifdef SHOW_DATE
        item = new QTableWidgetItem(QString(info.date));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }
#endif
        item = new QTableWidgetItem(QString::number(info.current,'f',2));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }
        if(info.lastCurrent > 0){
            if(info.lastCurrent < info.current){
                item->setBackgroundColor(Qt::green);
            }else if(info.lastCurrent == info.current){
                item->setBackgroundColor(Qt::transparent);
            }else{
                item->setBackgroundColor(Qt::red);
            }
        }

        item = new QTableWidgetItem(QString::number(info.open,'f',2));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }

        item = new QTableWidgetItem(QString::number(info.high,'f',2));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }

        item = new QTableWidgetItem(QString::number(info.low,'f',2));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }

        item = new QTableWidgetItem(QString::number(info.close,'f',2));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }

        item = new QTableWidgetItem(QString::number(info.hands));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }

        if(it.value().showAdjVal){
            item = new QTableWidgetItem(QString::number(info.adjVal,'f',2));
        }else{
            item = new QTableWidgetItem(QString::number(info.adj*100,'f',4)+"%");
        }
        if(info.adj < 0){
            item->setTextColor(view_setting.falling);
        }else{
            item->setTextColor(view_setting.rising);
        }
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }
    }
}

void QStockMainWindows::fetchStockData()
{
    sinaAgent->fetchStockData();
}

STATUS QStockMainWindows::loadSymbolHistory(QString symbol)
{
    ui->widget_quoteWaves->loadSymbolHistory(symbol);
    return STATUS_OK;
}

STATUS QStockMainWindows::loadSymbolHistory()
{
    ui->widget_quoteWaves->loadSymbolHistory();
    return STATUS_OK;
}

STATUS QStockMainWindows::checkAndLoadSymbolHistory()
{
    int index = ui->comboBox_watchList->currentIndex();
    StockIdDB* idb = NULL;
    if(index < 0)
        return STATUS_ERR_NOT_EXISTED;
    idb = stock_data->getIDB();
    if(idb){
        if(index < idb->size()){
            QString symbol = idb->at(index);
            if(yahooAgent->isDownloading(symbol)){
                return STATUS_FAILED;
            }else{
                STATUS ret = history_db->tryToInsertItem(symbol);
                if(ret == STATUS_ERR_EXISTED || ret == STATUS_OK){
                    loadSymbolHistory(symbol);
                }else if(ret != STATUS_OK){
                    QDateTime date_end = QDateTime::currentDateTime();
                    QDateTime date_start = date_end.addDays(0-DAYS_OF_YEAR);
                    DateRange rang(date_start.date(),date_end.date());
                    yahooAgent->downloadQuotes(symbol,rang);
                    ui->statusBar->showMessage(QString("Yahooo history of ")+symbol+QString(" is downloading..."));
                }
            }
        }
    }
    return STATUS_OK;
}

void QStockMainWindows::on_pushButtonAddCode_clicked()
{
    QString id = ui->lineEditAddCode->text();
    Message msg(STOCK_DATA_CHGED,this->id,MSG_FLAGS_NOTIFY_ALL,id,MSG_OP_ADD);
    g_getUcm()->post(msg);
}

void QStockMainWindows::slot_sinaHttpDone(bool )
{

}

void QStockMainWindows::slot_sinaDataReadProgress(int , int )
{
    if((fetchCnt++) > ui->progressBar->maximum() ){
        fetchCnt = 1;
    }
    ui->progressBar->setValue(fetchCnt);
    //ui->statusBar->showMessage(QString("Fetched ")+QString::number(fetchCnt)+" times");
}

void QStockMainWindows::slot_sinaReadyRead(QByteArray bytes)
{
    if(stock_data->updateInfo(bytes.data()) == STATUS_OK){
        StockIdDB* idb = stock_data->getIDB();

        updateRuntimeInfo();
        if(ui->comboBox_watchList->count() != idb->size()){
            slot_idbChanged();
        }
    }else{
        ui->statusBar->showMessage("fetch stock data failed",5000);
    }
}

void QStockMainWindows::slot_yahooHttpDownloadDone(QString symbol, QString filename)
{
    loadSymbolHistory(symbol);
    debug_print(DBG_DEBUG, "Yahooo history file %s download done",symbol.toStdString().c_str());
    ui->statusBar->showMessage(QString("Yahooo history of ")+symbol+QString(" download to ")+filename);
}

void QStockMainWindows::slot_sysTimeFreshed()
{
    fetchStockData();
}

void QStockMainWindows::slot_idbChanged()
{
    StockIdDB* idb = stock_data->getIDB();
    StockRuntimeDB* db = stock_data->getDB();
    StockRuntimeDB::iterator db_it;
    QString id;
    QString name;

    /* update combobox watch list */
    ui->comboBox_watchList->clear();

    for(int i = 0; i <idb->size(); i++){
        id = idb->at(i);
        db_it = db->find(id);
        if(db_it != db->end()){
            name = db_it.value().name;
        }else{
            name.clear();
            continue;
        }
        ui->comboBox_watchList->addItem(id+":"+name);
    }
}

void QStockMainWindows::on_actionAbout_triggered()
{
    AboutDialog dlg(this);
    dlg.exec();
    dlg.setAttribute (Qt::WA_DeleteOnClose);
}

void QStockMainWindows::on_action_SaveWatchList_triggered()
{
    Message msg(STOCK_DATA_SAVE,this->id,MSG_FLAGS_NOTIFY_ALL,0);
    g_getUcm()->post(msg);
}

void QStockMainWindows::slot_runtimeDelAction()
{
    if(lastSelRow >= 0){
        if(lastSelRow < ui->runtimeTableWidget->rowCount()){
            QTableWidgetItem* item = ui->runtimeTableWidget->item(lastSelRow,RUNTIME_COL_KEY);
            if(item){
                Message msg(STOCK_DATA_CHGED,this->id,MSG_FLAGS_NOTIFY_ALL,item->text(),MSG_OP_DEL);
                g_getUcm()->post(msg);
            }
        }
    }
}

void QStockMainWindows::slot_runtimeTopAction()
{
    if(lastSelRow >= 0){
        if(lastSelRow < ui->runtimeTableWidget->rowCount()){
            QTableWidgetItem* item = ui->runtimeTableWidget->item(lastSelRow,RUNTIME_COL_KEY);
            if(item){
                stock_data->topId(item->text());
                item->setBackground(view_setting.topBkg);
            }
        }
    }
}

void QStockMainWindows::slot_runtimeHlAction()
{
    if(lastSelRow >= 0){
        if(lastSelRow < ui->runtimeTableWidget->rowCount()){
            QTableWidgetItem* item = ui->runtimeTableWidget->item(lastSelRow,RUNTIME_COL_KEY);
            if(item){
                if(stock_data->hightlightId(item->text()) == STATUS_OK){
                    if(item->backgroundColor() == view_setting.hightlightBkg){
                        item->setBackground(Qt::white);
                    }else{
                        item->setBackground(view_setting.hightlightBkg);
                    }
                }
            }
        }
    }
}

void QStockMainWindows::slot_runtimeDetailAction()
{
    if(lastSelRow >= 0){
        if(lastSelRow < ui->runtimeTableWidget->rowCount()){
            QTableWidgetItem* item = ui->runtimeTableWidget->item(lastSelRow,RUNTIME_COL_KEY);
            if(item){
                QDateTime date_end = QDateTime::currentDateTime();
                QDateTime date_start = date_end.addDays(0-DAYS_OF_YEAR);
                DateRange rang(date_start.date(),date_end.date());
                /* show detail */
                yahooAgent->downloadQuotes(item->text(),rang);
            }
        }
    }
}

void QStockMainWindows::slot_tblCustomContextMenuRequested(QPoint point)
{
    lastSelRow = -1;
    QTableWidgetItem* selItem = ui->runtimeTableWidget->itemAt(point);
    if(selItem != NULL){
        lastSelRow = ui->runtimeTableWidget->row(selItem);
        runtimePopMenu->exec(QCursor::pos());
    }
}

void QStockMainWindows::contextMenuEvent(QContextMenuEvent *event)
{
    return QMainWindow::contextMenuEvent(event);
}


void QStockMainWindows::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        QWidget* focuedWidget = this->focusWidget();
        if(qobject_cast<QLineEdit*>(focuedWidget)){
            ui->pushButtonAddCode->click();
        }
    }

    return QMainWindow::keyPressEvent(event);
}

void QStockMainWindows::on_pushButton_myWatching_clicked()
{
    ui->stackedWidget->setCurrentIndex(STACK_WIDGET_INDEX_WATCHING);
}

void QStockMainWindows::on_pushButton_detailQuotes_clicked()
{
    checkAndLoadSymbolHistory();
    ui->stackedWidget->setCurrentIndex(STACK_WIDGET_INDEX_DETAILS);
}

void QStockMainWindows::on_pushButton_Position_clicked()
{
    ui->stackedWidget->setCurrentIndex(STACK_WIDGET_INDEX_POSITIONS);
}


QObject *QStockMainWindows::getQobject()
{
    return this;
}

STATUS QStockMainWindows::on_STOCK_DATA_CHGED(Message &msg)
{
    switch(msg.mhdr.op){
    case MSG_OP_ADD:
        ui->lineEditAddCode->clear();
        fetchStockData();
        break;
    case MSG_OP_DEL:
        ui->runtimeTableWidget->removeRow(lastSelRow);
        break;
    default:
        break;
    }
    return STATUS_OK;
}

int QStockMainWindows::handleMsg(Message &msg)
{
    return ISubscriber::handleMsg(msg);
}


STATUS QStockMainWindows::on_STOCK_DATA_SAVE(Message &)
{
    QMessageBox::information(NULL, "Save", "Saved User Watch List to ./user.conf Succeed",
                             QMessageBox::Ok, QMessageBox::Ok);
    return STATUS_OK;
}


void QStockMainWindows::on_comboBox_watchList_currentIndexChanged(int )
{
    checkAndLoadSymbolHistory();
}


void QStockMainWindows::closeEvent(QCloseEvent *)
{
    g_getUcm()->saveUserConfig();
}

void QStockMainWindows::on_comboBox_waveView_currentIndexChanged(int index)
{
    ui->widget_quoteWaves->viewChged(index);
}


void QStockMainWindows::on_pushButton_calendar_clicked()
{
    ui->stackedWidget->setCurrentIndex(STACK_WIDGET_INDEX_CALENDAR);
}

void QStockMainWindows::on_comboBox_wavesDatetome_currentIndexChanged(int index)
{
    QDate date = QDateTime::currentDateTime().date();
    bool enable = true;
    switch(index){
    case COMBOBOX_RUOTE_DATE_1YEAR:
        enable = false;
        break;
    case COMBOBOX_RUOTE_DATE_6MONTH:
        date = date.addMonths(-6);
        break;
    case COMBOBOX_RUOTE_DATE_3MONTH:
        date = date.addMonths(-3);
        break;
    case COMBOBOX_RUOTE_DATE_1MONTH:
        date = date.addMonths(-1);
        break;
    default:
        enable = false;
        break;
    }
    ui->widget_quoteWaves->setDateLimited(enable,date);
}

void QStockMainWindows::on_runtimeTableWidget_cellDoubleClicked(int row, int column)
{
    if(column == RUNTIME_COL_ADJ){
        StockRuntimeDB* db = stock_data->getDB();
        StockIdDB* idb = stock_data->getIDB();
        StockRuntimeDB::iterator it = db->begin();
        QString key;

        QTableWidgetItem* item = ui->runtimeTableWidget->item(row,column);
        if(!item){
            return ;
        }

        if(row < idb->size()){
            key = idb->at(row);
        }

        it = db->find(key);
        if(it == db->end()){
            return;
        }

        if(it.value().showAdjVal){
            it.value().showAdjVal = false;
            item->setText(QString::number(it.value().adj*100,'f',4)+"%");
        }else{
            it.value().showAdjVal = true;
            item->setText(QString::number(it.value().adjVal,'f',2));
        }

/*
        if(info.adj < 0){
            item->setTextColor(view_setting.falling);
        }else{
            item->setTextColor(view_setting.rising);
        }
*/
    }
}
