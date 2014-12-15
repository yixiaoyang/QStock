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

QStockMainWindows::QStockMainWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QStockMainWindows)
{
    ui->setupUi(this);

    ui->runtimeTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->runtimeTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    stock_data.loadUserConfig();

    view_setting.falling = Qt::darkGreen;
    view_setting.rising = Qt::red;
    view_setting.hightlightBkg = Qt::yellow;
    view_setting.topBkg = Qt::darkGreen;
    view_setting.sysTimerMsec = 5000;

    lastSelRow = -1;
    fetchCnt = 0;
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(fetchCnt);

    connect(&stock_data,SIGNAL(sig_idbChanged()),this,SLOT(slot_idbChanged()));

    sysTimer = new QTimer(this);
    connect(sysTimer,SIGNAL(timeout()),this,SLOT(slot_sysTimeFreshed()));
    sysTimer->start(view_setting.sysTimerMsec); /*5s*/

    sinaAgent = new QHttpAgent("hq.sinajs.cn");
    connect(sinaAgent, SIGNAL(httpDone(bool)),this, SLOT(slot_sinaHttpDone(bool)));
    connect(sinaAgent, SIGNAL(dataReadProgress(int,int)),this, SLOT(slot_sinaDataReadProgress(int,int)));
    connect(sinaAgent, SIGNAL(readyRead(QByteArray)),this, SLOT(slot_sinaReadyRead(QByteArray)));

    ui->runtimeTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    runtimePopMenu = new QMenu(ui->runtimeTableWidget);
    runtimeTopAction = new QAction("Place on Top ",this);
    runtimeDelAction = new QAction("Delete ",this);
    runtimeHlAction = new QAction("Hightlight & DisHightlight it",this);

    runtimeTopAction->setIcon(QIcon(":/main/icons/top.png"));
    runtimeDelAction->setIcon(QIcon(":/main/icons/del.png"));
    runtimeHlAction->setIcon(QIcon(":/main/icons/highlight.png"));

    connect(runtimeTopAction,SIGNAL(triggered()),this,SLOT(slot_runtimeTopAction()));
    connect(runtimeDelAction,SIGNAL(triggered()),this,SLOT(slot_runtimeDelAction()));
    connect(runtimeHlAction,SIGNAL(triggered()),this,SLOT(slot_runtimeHlAction()));

    runtimePopMenu->addAction(runtimeDelAction);
    runtimePopMenu->addAction(runtimeTopAction);
    runtimePopMenu->addAction(runtimeHlAction);

    connect(ui->runtimeTableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_tblCustomContextMenuRequested(QPoint)));

    updateURI();
    fetchStockData();
}

QStockMainWindows::~QStockMainWindows()
{
    stock_data.saveUserConfig();
    delete sinaAgent;
    delete ui;
}

/*!!! TODO:  clean these code, its not gentle !!! */
void QStockMainWindows::updateRuntimeInfo()
{
    StockRuntimeDB* db = stock_data.getDB();
    StockIdDB* idb = stock_data.getIDB();
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

        item = new QTableWidgetItem(QString(info.date));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
        }

        item = new QTableWidgetItem(QString::number(info.current,'f',2));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tblWidget->setItem(cnt,col++,item);
        if(info.isHl){
            item->setBackground(view_setting.hightlightBkg);
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

        item = new QTableWidgetItem(QString::number(info.adj*100,'f',4)+"%");
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
    if(uri.isEmpty()){
        return ;
    }
    sinaAgent->fetchStockData();
}

void QStockMainWindows::updateURI()
{
    StockIdDB* idb = stock_data.getIDB();
    uri.clear();
    uri=QString("/list=");
    if(idb->isEmpty()){
        /* 默认添加上证和深圳指数 */
        idb->append("sz399001");
        idb->append("sh000001");
    }

    for(int cnt = 0; cnt < idb->count(); cnt++){
        uri = uri+idb->at(cnt)+",";
    }
    /* remove last ',' */
    uri.remove(uri.length()-1,1);
    sinaAgent->uri = uri;
}

void QStockMainWindows::on_pushButtonAddCode_clicked()
{
    QString id = ui->lineEditAddCode->text();
    if(stock_data.addId(id) == STATUS_OK){
        ui->lineEditAddCode->clear();
        fetchStockData();
    }
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
    ui->statusBar->showMessage(QString("Fetched ")+QString::number(fetchCnt)+" times");
}

void QStockMainWindows::slot_sinaReadyRead(QByteArray bytes)
{
    if(stock_data.updateInfo(bytes.data()) == STATUS_OK){
        updateRuntimeInfo();
    }else{
        ui->statusBar->showMessage("fetch stock data failed",5000);
    }
}

void QStockMainWindows::slot_sysTimeFreshed()
{
    fetchStockData();
}

void QStockMainWindows::slot_idbChanged()
{
    updateURI();
}

void QStockMainWindows::on_actionAbout_triggered()
{
    AboutDialog dlg(this);
    dlg.exec();
    dlg.setAttribute (Qt::WA_DeleteOnClose);
}

void QStockMainWindows::on_action_SaveWatchList_triggered()
{
    stock_data.saveUserConfig();
    QMessageBox::information(NULL, "Save", "Saved User Watch List to ./user.conf Succeed",
                             QMessageBox::Ok, QMessageBox::Ok);
}

void QStockMainWindows::slot_runtimeDelAction()
{
    if(lastSelRow >= 0){
        if(lastSelRow < ui->runtimeTableWidget->rowCount()){
            QTableWidgetItem* item = ui->runtimeTableWidget->item(lastSelRow,RUNTIME_COL_KEY);
            if(item){
                stock_data.removeId(item->text());
                ui->runtimeTableWidget->removeRow(lastSelRow);
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
                stock_data.topId(item->text());
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
                if(stock_data.hightlightId(item->text()) == STATUS_OK){
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
