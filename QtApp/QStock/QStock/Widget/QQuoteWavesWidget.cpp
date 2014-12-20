#include "QQuoteWavesWidget.h"
#include "ui_qquotewaveswidget.h"

#include "includes.h"

QQuoteWavesWidget::QQuoteWavesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQuoteWavesWidget)
{
    ui->setupUi(this);

    g_getUcm()->registerFor(this,ISUBSCRIBER_ID_QSTOCK_WAVE_WIDGET,this->objectName());

    history_db = NULL;
    history_db = g_getUcm()->getHistoryDB();
    assert(history_db != NULL);

    history_items = NULL;

    if_paint_gridding = true;
    space_to_edge = 20;
    grid_date_width = 5;
    zero_point.setX(space_to_edge);
    zero_point.setY(space_to_edge);

    xCnt = 120;
    yCnt = 20;
    point_text.setX(50);
    point_text.setY(50);
    text_width = 200;
}

QQuoteWavesWidget::~QQuoteWavesWidget()
{
    g_getUcm()->unRegisterFor(this);
    delete ui;
}
int QQuoteWavesWidget::getDays() const
{
    return xCnt;
}

void QQuoteWavesWidget::setDays(int value)
{
    xCnt = value;
}

STATUS QQuoteWavesWidget::loadSymbolHistory(QString _symbol)
{
    this->symbol = _symbol;

    /* get data */
    history_items = history_db->getYahooHistoryItems(this->symbol);
    if(history_items == NULL){
        debug_print(DBG_ERROR,"getYahooHistoryItems NULL");
    }else{
        int w = this->width()-this->space_to_edge*2;
        xCnt = (w >= history_items->size()) ? history_items->size() : w;
        yCnt = 20;

        history_stats = history_db->getYahooHistoryStats(this->symbol);
    }
       update();
    return STATUS_OK;
}

STATUS QQuoteWavesWidget::loadSymbolHistory()
{
    this->symbol.clear();
    history_items = NULL;
    return STATUS_OK;
}

void QQuoteWavesWidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    if(if_paint_gridding){
        paint_gridding(&paint);
    }

    paint_history(&paint);

    paint.end();
}

void QQuoteWavesWidget::paint_gridding(QPainter *p)
{
    int w = this->width()-this->space_to_edge*2;
    int h = this->height()-this->space_to_edge*2;
    double percent = 0.0;
    int paintedDot = 0;
    int start = 0;

    QBrush b1( Qt::gray );
    QColor gridColor = QColor(Qt::gray);

    p->setPen(QPen(gridColor, 1, Qt::SolidLine, Qt::FlatCap));
    p->setBrush(b1);

    /* draw frames */
    p->drawLine( zero_point.x(), zero_point.y(), zero_point.x()+w, zero_point.y());
    p->drawLine( zero_point.x(), zero_point.y(), zero_point.x(), zero_point.y()+h);
    p->drawLine( zero_point.x()+w, zero_point.y()+h, zero_point.x(), zero_point.y()+h);
    p->drawLine( zero_point.x()+w, zero_point.y()+h, zero_point.x()+w, zero_point.y());

    /* x cnt */
    paintedDot = 0;
    while(paintedDot++ < this->xCnt){
        percent = ((double)paintedDot)/xCnt;
        start = (int)(percent * w);
        p->drawLine(zero_point.x()+start,zero_point.y(),zero_point.x()+start,zero_point.y()+grid_date_width);
        p->drawLine(zero_point.x()+start,zero_point.y()+h,zero_point.x()+start,zero_point.y()+h-grid_date_width);
    }
    /* y cnt */
    paintedDot = 0;
    while(paintedDot++ < this->yCnt){
        percent = ((double)paintedDot)/yCnt;
        start = (int)(percent * h);
        p->drawLine(zero_point.x(),zero_point.y()+h-start,zero_point.x()+grid_date_width,zero_point.y()+h-start);
        p->drawLine(zero_point.x()+w,zero_point.y()+h-start,zero_point.x()+w-grid_date_width,zero_point.y()+h-start);
    }
}

void QQuoteWavesWidget::paint_history(QPainter *p)
{
    QBrush bText( Qt::darkYellow );
    QBrush bPrice( Qt::darkBlue );
    QColor textColor = QColor(Qt::darkGreen);
    QColor priceColor = QColor(Qt::darkBlue);
    QColor gridColor = QColor(Qt::gray);

    int w = this->width()-this->space_to_edge*2;
    int h = this->height()-this->space_to_edge*2;
    int priceH = 0;
    int paintLastItemsCnt = 0;
    double percent = 0.00;
    int eachPriceH = 0;

    const int priceSpace = 5;
    const int textH = 12;
    QString dateStr;

    int dotX = 0;
    int dotY = 0;
    int dotLastX = 0;
    int dotLastY = 0;

    double priceDiffVal = history_stats.maxClose - history_stats.minClose;

    YahooHistoryItem item;

    if(this->symbol.isEmpty()){
        p->setBrush(bText);
        p->setPen(QPen(textColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->drawText(point_text,QString("History Data is Downloading, Please wait for a moment..."));
    }else{
        if(history_items == NULL){
            return ;
        }
#if 0
        QString statsStr("Stats maxClose ");
        statsStr = statsStr+QString::number(history_stats.maxClose);
        statsStr = statsStr+QString(",minClose ");
        statsStr = statsStr+QString::number(history_stats.minClose);

        p->setBrush(b1);
        p->setPen(QPen(textColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->drawText(point_text,QString("History Data size ")+QString::number(history_items->size()));
        p->drawText(point_text.x(),point_text.y()+20,statsStr);
#endif

        /* paint price line */
        eachPriceH = (((double)h)/yCnt);
        priceH = h - (((double)h)/yCnt)*2;
        p->setPen(QPen(textColor, 1, Qt::DashDotLine, Qt::FlatCap));
        p->drawLine(zero_point.x(),  zero_point.y()+eachPriceH,
                    zero_point.x()+w,zero_point.y()+eachPriceH);
        p->drawText(zero_point.x()+priceSpace,zero_point.y()+eachPriceH-priceSpace,
                    QString::number(history_stats.maxClose,'f',2));
        p->drawLine(zero_point.x(),  zero_point.y()+h-eachPriceH,
                    zero_point.x()+w,zero_point.y()+h-eachPriceH);
        p->drawText(zero_point.x()+priceSpace,zero_point.y()+h-eachPriceH+textH+priceSpace,
                    QString::number(history_stats.minClose,'f',2));

        /* paint dot */
        p->setPen(QPen(priceColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->setBrush(bPrice);
        paintLastItemsCnt = xCnt;
        for(int index = paintLastItemsCnt-1, count = 0; index >= 0; index--,count++){
            item = history_items->at(count);
            /* paint each dot */
            percent = 1 - (((double)count)/paintLastItemsCnt);
            dotX = zero_point.x()+(int)(percent*w);

            percent = ((item.close-history_stats.minClose)/priceDiffVal);
            dotY = zero_point.y() + h - eachPriceH - percent*(h-(eachPriceH<<1));

            if(count != 0){
                p->drawLine(dotX,dotY,dotLastX,dotLastY);
            }
            if(count % DAYS_OF_MONTH == 0){
                dateStr = item.date.toString("yyyy-MM-dd");
                p->drawText(dotX-60,zero_point.y()+h+textH, dateStr);

                p->setPen(QPen(gridColor, 1, Qt::DotLine, Qt::FlatCap));
                p->drawLine(dotX,zero_point.y(),dotX,zero_point.y()+h);
                p->setPen(QPen(priceColor, 1, Qt::SolidLine, Qt::FlatCap));
            }

            dotLastX = dotX;
            dotLastY = dotY;
        }
    }
}

QObject *QQuoteWavesWidget::getQobject()
{
    return this;
}

int QQuoteWavesWidget::handleMsg(Message &msg)
{
    return ISubscriber::handleMsg(msg);
}
