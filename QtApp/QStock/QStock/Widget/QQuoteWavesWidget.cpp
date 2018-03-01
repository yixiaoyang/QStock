#include "QQuoteWavesWidget.h"
#include "ui_qquotewaveswidget.h"

#include <QFont>
#include <QApplication>
#include <QMouseEvent>
#include "includes.h"
#include "Quote/QuoteTools.h"

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
    if_paint_quote = true;
    if_paint_kline = true;

    space_to_edge = 20;
    grid_date_width = 5;
    zero_point.setX(space_to_edge);
    zero_point.setY(space_to_edge);

    xCnt = 1;
    yCnt = 1;
    point_text.setX(50);
    point_text.setY(50);
    text_width = 200;

    last_pos_index = -1;

    _dateLimited = false;
    _daysCnt = 0;
}

QQuoteWavesWidget::~QQuoteWavesWidget()
{
    g_getUcm()->unRegisterFor(this);
    delete ui;
}

STATUS QQuoteWavesWidget::loadSymbolHistory(QString _symbol )
{
    this->symbol = _symbol;

    /* get data */
    history_items = history_db->getYahooHistoryItems(this->symbol);
    if(history_items == NULL){
        debug_print(DBG_ERROR,"getYahooHistoryItems NULL");
    }else{
        int w = this->width()-this->space_to_edge*2;
        xCnt = (w >= history_items->size()) ? history_items->size() : w;
        if(!_dateLimited)
            _daysCnt = xCnt;
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

void QQuoteWavesWidget::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    if(if_paint_gridding){
        paint_gridding(&paint);
    }
    if(if_paint_quote){
        paint_history(&paint);
    }
    paint.end();
    return QWidget::paintEvent(e);
}

void QQuoteWavesWidget::paint_gridding(QPainter *p)
{
    int w = this->width()-(this->space_to_edge<<1);
    int h = this->height()-(this->space_to_edge<<1);
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
    while(paintedDot++ <  this->_daysCnt){
        percent = ((double)paintedDot)/this->_daysCnt;
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
    static QBrush bText( Qt::darkYellow );
    static QBrush bPrice( Qt::darkBlue );
    static QColor textColor = Qt::darkGreen;
    static QColor priceColor = Qt::darkBlue;
    static QColor gridColor = Qt::gray;

    int kDotY[KDOT_MAX];

    int w = this->width()-(this->space_to_edge<<1);
    int h = this->height()-(this->space_to_edge<<1);
    int priceH = 0;
    int paintLastItemsCnt = 0;
    double percent = 0.00;
    int eachPriceH = 0;

    const int priceSpace = 15;
    const int textH = 12;
    QString dateStr;

    int dotX = 0;
    int dotY = 0;
    int dotLastX = 0;
    int dotLastY = 0;
    int cursorX = 0;
    int cursorY = 0;
    int cursorIndex = 0;

    double curMaxClose,curMinClose;
    if(this->_dateLimited){
        curMaxClose = history_stats.curMaxClose;
        curMinClose = history_stats.curMinClose;
    }else{
        curMaxClose = history_stats.maxClose;
        curMinClose = history_stats.minClose;
    }
    double priceDiffVal = curMaxClose - curMinClose;
    double price = 0.00;

    int splitDays = DAYS_OF_MONTH;

    YahooHistoryItem item;

    if(this->symbol.isEmpty()){
        p->setBrush(bText);
        p->setPen(QPen(textColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->drawText(point_text,QString("History Data is Downloading, Please wait for a moment..."));
    }else{
        if(history_items == NULL){
            return ;
        }
        /* paint price line */
        eachPriceH = (((double)h)/yCnt)+0.5;
        p->setPen(QPen(textColor, 1, Qt::DotLine, Qt::FlatCap));
        for(int line = 1; line < yCnt; line++){
            priceH = (((double)h)/yCnt)*line+0.5;
            percent = ((double)(line-1))/(yCnt-2);
            price = curMaxClose - (percent)*priceDiffVal;
            p->drawLine(zero_point.x(),  zero_point.y()+priceH,
                        zero_point.x()+w,zero_point.y()+priceH);
            p->drawText(zero_point.x()+priceSpace,zero_point.y()+priceH-priceSpace,
                        80,16,Qt::AlignLeft,
                        QString::number(price,'f',2));
            p->drawText(zero_point.x()+w-90,zero_point.y()+priceH-priceSpace,
                        80,16,Qt::AlignRight,
                        QString::number(price,'f',2));
        }
        /* paint dot */
        p->setPen(QPen(priceColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->setBrush(bPrice);
        paintLastItemsCnt = _daysCnt;

        if(_daysCnt >= 500){
            splitDays = DAYS_OF_3MONTH;
        }
        if(_daysCnt >= 2000){
            splitDays = DAYS_OF_6MONTH;
        }
        for(int index = paintLastItemsCnt-1, count = 0; index >= 0; index--,count++){
            item = history_items->at(count);

            /* paint each dot */
            percent = 1 - (((double)count)/paintLastItemsCnt);
            dotX = zero_point.x()+(int)(percent*w);

            if(if_paint_kline){
                percent = ((item.high-curMinClose)/priceDiffVal);
                kDotY[KDOT_HIGH] = zero_point.y() + h - eachPriceH - percent*(h-(eachPriceH<<1));

                percent = ((item.low-curMinClose)/priceDiffVal);
                kDotY[KDOT_LOW] = zero_point.y() + h - eachPriceH - percent*(h-(eachPriceH<<1));

                percent = ((item.close-curMinClose)/priceDiffVal);
                kDotY[KDOT_OPEN_CLOSE1] = zero_point.y() + h - eachPriceH - percent*(h-(eachPriceH<<1));

                percent = ((item.open-curMinClose)/priceDiffVal);
                kDotY[KDOT_OPEN_CLOSE2] = zero_point.y() + h - eachPriceH - percent*(h-(eachPriceH<<1));

                kDotY[KDOT_RISING] = 1;

                dotY = kDotY[KDOT_OPEN_CLOSE1];
                if(item.close < item.open){
                    kDotY[KDOT_RISING] = 0;

                    dotY = kDotY[KDOT_OPEN_CLOSE2];
                    kDotY[KDOT_OPEN_CLOSE2] = kDotY[KDOT_OPEN_CLOSE1];
                    kDotY[KDOT_OPEN_CLOSE1] = dotY;
                }
                paint_kline(p,dotX,kDotY);
            }else{
                percent = ((item.close-curMinClose)/priceDiffVal);
                dotY = zero_point.y() + h - eachPriceH - percent*(h-(eachPriceH<<1));
                if(count != 0){
                    p->drawLine(dotX,dotY,dotLastX,dotLastY);
                }
            }

            if(count % splitDays == 0){
                p->setPen(QPen(textColor, 1, Qt::SolidLine, Qt::FlatCap));
                dateStr = item.date.toString("yyyy-MM-dd");
                p->drawText(dotX-60,zero_point.y()+h+textH, dateStr);

                p->setPen(QPen(gridColor, 1, Qt::DotLine, Qt::FlatCap));
                p->drawLine(dotX,zero_point.y(),dotX,zero_point.y()+h);
                p->setPen(QPen(priceColor, 1, Qt::SolidLine, Qt::FlatCap));
            }

            dotLastX = dotX;
            dotLastY = dotY;

            if(last_pos_index == count){
                cursorIndex = count;
                cursorX = dotX;
                cursorY = dotY;
            }
        }

        if(history_items->size() > 0){
            item = history_items->at(cursorIndex);
            paint_last_quote(p,cursorX,cursorY,item);
        }
        p->setPen(QPen(priceColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->setBrush(bPrice);
    }

}

void QQuoteWavesWidget::paint_kline(QPainter *p, int dotX, int *dotYs)
{
    static QColor kLineColor = QColor(QRgb(0x000020));
    static QColor kRisingColor = Qt::red;
    static QColor kFallingColor = Qt::darkGreen;
    static QBrush kLineBrush( kLineColor );
    static QBrush kRisingBrush( kRisingColor );
    static QBrush kFallingBrush( kFallingColor );

    int w = this->width()-(this->space_to_edge<<1);
    int eachKlineW = (((double)w)/_daysCnt);

    if(eachKlineW > 2){
        eachKlineW -= 2;
    }

    p->setPen(QPen(kLineColor, 1, Qt::SolidLine, Qt::FlatCap));
    p->setBrush(kLineBrush);
    p->drawLine(dotX, dotYs[KDOT_HIGH],dotX, dotYs[KDOT_LOW]);

    if(dotYs[KDOT_RISING]){
        p->setPen(QPen(kRisingColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->setBrush(kRisingBrush);
    }else{
        p->setPen(QPen(kFallingColor, 1, Qt::SolidLine, Qt::FlatCap));
        p->setBrush(kFallingBrush);
    }

    p->drawRect(dotX-(eachKlineW>>1),dotYs[KDOT_OPEN_CLOSE1],
                eachKlineW,dotYs[KDOT_OPEN_CLOSE2]-dotYs[KDOT_OPEN_CLOSE1]);
}

void QQuoteWavesWidget::paint_last_quote(QPainter *p, int x, int y, YahooHistoryItem& item)
{
    static QBrush bText( Qt::yellow );
    static QBrush bCursor( Qt::cyan );
    static QColor textColor = Qt::yellow;
    static QColor colorCursor = Qt::black;
    static QBrush bBkg( Qt::black );
    QFont font = QApplication::font();
    static int font_size = 12;
    int old_font_size = font.pointSize();
    static int textW = 0;
    static const int textH = 30;

    QPoint last_pos(x,y);
    QString last_pos_str = QString::number(item.close,'f',2);
    int w = this->width()-(this->space_to_edge<<1);
    int h = this->height()-(this->space_to_edge<<1);

    p->setBrush(bCursor);
    p->setPen(QPen(colorCursor, 1, Qt::SolidLine, Qt::FlatCap));
    p->drawLine(zero_point.x(),zero_point.y()+last_pos.y()-space_to_edge,
                zero_point.x()+w,zero_point.y()+last_pos.y()-space_to_edge);
    p->drawLine(zero_point.x()+last_pos.x()-space_to_edge,zero_point.y(),
                zero_point.x()+last_pos.x()-space_to_edge,zero_point.y()+h);
    p->drawRect(QRect(last_pos.x()-2,last_pos.y()-2,5,5));

    p->setBackgroundMode(Qt::OpaqueMode);
    p->setBackground(bBkg);
    p->setBrush(bText);
    font.setPointSize(font_size);
    font.setBold(true);
    p->setFont(font);
    p->setPen(QPen(textColor, 1, Qt::SolidLine, Qt::FlatCap));

    textW = font_size*last_pos_str.length();
    if(last_pos.x() > w-100){
        p->drawText(last_pos.x()-textW-1,last_pos.y()-textH,
                    textW,textH,
                    Qt::AlignRight|Qt::AlignBottom,last_pos_str);
    }else{
        p->drawText(last_pos.x()+1,last_pos.y()-textH,
                    textW,textH,
                    Qt::AlignLeft|Qt::AlignBottom,last_pos_str);
    }

    p->setBackgroundMode(Qt::TransparentMode);
    font.setPointSize(old_font_size);
    font.setBold(false);
    p->setFont(font);
}

void QQuoteWavesWidget::handlemouseEvent(QMouseEvent *event)
{
    if(history_items != NULL){
        int w = this->width()-(this->space_to_edge<<1);
        int h = this->height()-(this->space_to_edge<<1);
        QPoint pos = event->pos();
        last_pos_index = -1;

        if((pos.x() >= zero_point.x() ) && (pos.y() >= zero_point.y())
                                        && (pos.x() <= zero_point.x()+w )
                                        && (pos.y() <= zero_point.y())+h ){
            if(history_items->size() > 0){
                YahooHistoryItem item;
                double percent = 1-((double)pos.x()-this->space_to_edge)/w;
                int index = percent*_daysCnt+0.5;
                if(index < history_items->size()){
                    item = history_items->at(index);
                    ui->labelQuoteHistoryInfo->setText(QuoteTools::yahooHistoryItem2InfoString(item));

                    /* record and repaint it */
                    last_pos_index = index;
                    update();
                }
            }
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

void QQuoteWavesWidget::mouseMoveEvent(QMouseEvent *event)
{
    handlemouseEvent(event);
}

void QQuoteWavesWidget::mouseReleaseEvent(QMouseEvent *)
{
    last_pos_index = -1;
    update();
}


void QQuoteWavesWidget::mousePressEvent(QMouseEvent *event)
{
    handlemouseEvent(event);
}

void QQuoteWavesWidget::viewChged(int index)
{
    switch(index){
    case WAVE_VIEW_KLINE:
        if(!if_paint_kline){
            if_paint_kline=true;
            update();
        }
        break;
    case WAVE_VIEW_TIME_INDEX:{
        if(if_paint_kline){
            if_paint_kline=false;
            update();
        }
        break;
    }
    default:
        break;
    }
}

void QQuoteWavesWidget::setDateLimited(bool enable, QDate &date)
{
    this->_dateLimited = enable;
    this->_deadDateLine = date;
    if(history_items){
        if(!enable){
            this->_daysCnt = history_items->size();
            history_stats.curMaxClose = history_stats.maxClose;
            history_stats.curMinClose = history_stats.minClose;
        }else{
            YahooHistoryItems::const_iterator it;
            _daysCnt = 0;
            history_stats.curMaxClose = -1.00;
            history_stats.curMinClose = 999999999999.00;
            for(it = history_items->begin(); it != history_items->end(); it++,_daysCnt++){
                if((*it).date < date){
                    break;
                }
                history_stats.curMaxClose = history_stats.curMaxClose <= (*it).close ? (*it).close : history_stats.curMaxClose;
                history_stats.curMinClose = history_stats.curMinClose >= (*it).close ? (*it).close : history_stats.curMinClose;
            }
        }
        update();
    }else{
        this->_daysCnt = 0;
    }
}

