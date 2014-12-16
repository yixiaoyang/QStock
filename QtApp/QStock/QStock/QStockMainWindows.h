#ifndef QSTOCKMAINWINDOWS_H
#define QSTOCKMAINWINDOWS_H

#include <QMainWindow>
#include <QHttp>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QMutex>
#include <QContextMenuEvent>
#include <QTableWidgetItem>
#include <QTextStream>

#include "Data/StockData.h"
#include "Data/HistoryDB.h"
#include "Http/QSinaHttpAgent.h"

typedef struct _ViewSetting{
    QColor rising;
    QColor falling;
    QColor hightlightBkg;
    QColor topBkg;
    int urlArrayCnt;
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
        RUNTIME_COL_KEY,
        RUNTIME_COL_DATE,
        RUNTIME_COL_CURRENT,
        RUNTIME_COL_OPEN,
        RUNTIME_COL_HIGH,
        RUNTIME_COL_LOW,
        RUNTIME_COL_CLOSE,
        RUNTIME_COL_VOLUME,
        RUNTIME_COL_ADJ,
        RUNTIME_COL_MAX
    };
    enum{
        STACK_WIDGET_INDEX_WATCHING,
        STACK_WIDGET_INDEX_DETAILS,
        STACK_WIDGET_INDEX_POSITIONS,
        STACK_WIDGET_INDEX_CALENDAR,
        STACK_WIDGET_INDEX_NOTES
    };
    void updateRuntimeInfo();
    void fetchStockData();
private slots:
    void on_pushButtonAddCode_clicked();

    /* sina http slot */
    void slot_sinaHttpDone(bool);
    void slot_sinaDataReadProgress(int,int);
    void slot_sinaReadyRead(QByteArray);

    void slot_sysTimeFreshed();
    void slot_idbChanged();

    void slot_runtimeDelAction();
    void slot_runtimeTopAction();
    void slot_runtimeHlAction();
    void slot_runtimeDetailAction();
    void slot_tblCustomContextMenuRequested(QPoint);

    void on_action_SaveWatchList_triggered();
    void on_pushButton_myWatching_clicked();
    void on_pushButton_detailQuotes_clicked();
    void on_pushButton_Position_clicked();
    void on_actionAbout_triggered();

private:
    Ui::QStockMainWindows *ui;
    int fetchCnt;

    /* DB */
    StockData stock_data;

    /* view setting*/
    ViewSetting view_setting;

    QTimer* sysTimer;

    /* httpAgent */
    QSinaHttpAgent* sinaAgent;

    /* runtime info menu */
    QMenu *runtimePopMenu;
    QAction *runtimeDelAction;
    QAction *runtimeTopAction;
    QAction *runtimeHlAction;
    QAction *runtimeDetailAction;
    int lastSelRow;

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // QSTOCKMAINWINDOWS_H
