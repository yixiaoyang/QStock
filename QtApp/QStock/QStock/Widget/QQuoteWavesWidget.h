#ifndef QQUOTEWAVESWIDGET_H
#define QQUOTEWAVESWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QRgb>
#include <QBrush>
#include <QColor>


#include "Ucm/ucm.h"
#include "Ucm/isubscriber.h"
#include "Data/HistoryDB.h"

#include <QVector>

namespace Ui {
class QQuoteWavesWidget;
}

class QQuoteWavesWidget : public QWidget, public ISubscriber
{
    Q_OBJECT

public:
    enum{
        KDOT_HIGH,
        KDOT_OPEN_CLOSE1,
        KDOT_OPEN_CLOSE2,
        KDOT_LOW,
        KDOT_RISING,
        KDOT_MAX
    };

    explicit QQuoteWavesWidget(QWidget *parent = 0);
    ~QQuoteWavesWidget();

    STATUS loadSymbolHistory(QString _symbol);
    STATUS loadSymbolHistory();
    void viewChged(int index);
    void setDateLimited(bool enable,QDate& date);
private:
    Ui::QQuoteWavesWidget *ui;

    HistoryDB* history_db;
    const YahooHistoryItems* history_items;
    HisStatistics history_stats;
    QString symbol;

    /* view */
    bool if_paint_gridding;
    bool if_paint_quote;
    bool if_paint_kline;

    QPoint zero_point;

    bool _dateLimited;
    QDate _deadDateLine;
    int _daysCnt;

    int space_to_edge;
    int grid_date_width;
    QPoint point_text;
    int text_width;

    int last_pos_index;

    /* data */
    int xCnt;
    /* price */
    int yCnt;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
    void paint_gridding(QPainter *p);
    void paint_history(QPainter *p);
    void paint_kline(QPainter *p, int dotX, int *dotYs);
    void paint_last_quote(QPainter *p, int x, int y, YahooHistoryItem &item);
    void handlemouseEvent(QMouseEvent *);

    // ISubscriber interface
public:
    QObject *getQobject();

protected slots:
    int handleMsg(Message &msg);

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};


#endif // QQUOTEWAVESWIDGET_H
