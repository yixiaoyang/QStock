#include "QQuoteWavesWidget.h"
#include "ui_qquotewaveswidget.h"

QQuoteWavesWidget::QQuoteWavesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQuoteWavesWidget)
{
    ui->setupUi(this);

    if_paint_gridding = true;
    space_to_edge = 20;
    grid_date_width = 5;
    zero_point.setX(space_to_edge);
    zero_point.setY(space_to_edge);

    xCnt = 120;
    yCnt = 20;
}

QQuoteWavesWidget::~QQuoteWavesWidget()
{
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



void QQuoteWavesWidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    if(if_paint_gridding){
        paint_gridding(&paint);
    }

    paint.end();
}

void QQuoteWavesWidget::paint_gridding(QPainter *p)
{
    int w = this->width()-this->space_to_edge*2;
    int h = this->height()-this->space_to_edge*2;
    double percent = 0.0;
    int paintedDot = 0;
    int start = 0;
    int end = 0;

    QBrush b1( Qt::gray );
    QColor gridColor = QColor(QRgb(Qt::gray));

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
