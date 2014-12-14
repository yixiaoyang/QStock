#ifndef QSTOCKMAINWINDOWS_H
#define QSTOCKMAINWINDOWS_H

#include <QMainWindow>
#include <QHttp>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QContextMenuEvent>
#include <QTableWidgetItem>

#include "Data/StockData.h"
#include "Data/HistoryDB.h"
#include "Http/QHttpAgent.h"

typedef struct _ViewSetting{
    QColor rising;
    QColor falling;
    QColor hightlightBkg;
    QColor topBkg;
    int sysTimerMsec;
}ViewSetting;

namespace Ui {
class QStockMainWindows;
}

class QStockMainWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit QStockMainWindows(QWidget *parent = 0);
    ~QStockMainWindows();
private:
    enum {
        RUNTIME_COL_NAME,
        RUNTIME_COL_KEY
    };
    void updateRuntimeInfo();
    void fetchStockData();
    void updateURI();
private slots:
    void on_pushButtonAddCode_clicked();

    /* sina http slot */
    void on_sinaHttpDone(bool);
    void on_sinaDataReadProgress(int,int);
    void on_sinaReadyRead(QByteArray);

    void onSysTimeFreshed();
    void onIdbChanged();
    void on_actionAbout_triggered();

    void on_action_SaveWatchList_triggered();

    void on_runtimeDelAction();
    void on_runtimeTopAction();
    void on_runtimeHlAction();
    void on_tblCustomContextMenuRequested(QPoint);
private:
    Ui::QStockMainWindows *ui;
    int fetchCnt;

    QString uri;

    /* DB */
    StockData stock_data;

    /* view setting*/
    ViewSetting view_setting;

    QTimer* sysTimer;

    /* httpAgent */
    QHttpAgent* sinaAgent;

    /* runtime info menu */
    QMenu *runtimePopMenu;
    QAction *runtimeDelAction;
    QAction *runtimeTopAction;
    QAction *runtimeHlAction;
    int lastSelRow;

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *);
};

#endif // QSTOCKMAINWINDOWS_H
