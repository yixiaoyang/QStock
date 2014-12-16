#ifndef QQUOTEWAVESWIDGET_H
#define QQUOTEWAVESWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QRgb>
#include <QBrush>
#include <QColor>

namespace Ui {
class QQuoteWavesWidget;
}

class QQuoteWavesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQuoteWavesWidget(QWidget *parent = 0);
    ~QQuoteWavesWidget();

    int getDays() const;
    void setDays(int value);

private:
    Ui::QQuoteWavesWidget *ui;

    /* view */
    bool if_paint_gridding;
    QPoint zero_point;

    int space_to_edge;
    int grid_date_width;

    /* data */
    int xCnt;
    /* price */
    int yCnt;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
    void paint_gridding(QPainter *p);
};

#endif // QQUOTEWAVESWIDGET_H
