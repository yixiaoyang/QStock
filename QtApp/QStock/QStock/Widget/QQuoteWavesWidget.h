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
    explicit QQuoteWavesWidget(QWidget *parent = 0);
    ~QQuoteWavesWidget();

    int getDays() const;
    void setDays(int value);

    STATUS loadSymbolHistory(QString _symbol);
    STATUS loadSymbolHistory();
private:
    Ui::QQuoteWavesWidget *ui;

    HistoryDB* history_db;
    const YahooHistoryItems* history_items;
    HisStatistics history_stats;
    QString symbol;

    /* view */
    bool if_paint_gridding;
    QPoint zero_point;

    int space_to_edge;
    int grid_date_width;
    QPoint point_text;
    int text_width;

    /* data */
    int xCnt;
    /* price */
    int yCnt;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
    void paint_gridding(QPainter *p);
    void paint_history(QPainter *p);

    // ISubscriber interface
public:
    QObject *getQobject();

protected slots:
    int handleMsg(Message &msg);
};

#endif // QQUOTEWAVESWIDGET_H
