#ifndef QUOTECALENDARWIDGET_H
#define QUOTECALENDARWIDGET_H

#include <QWidget>

namespace Ui {
class QuoteCalendarWidget;
}

class QuoteCalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuoteCalendarWidget(QWidget *parent = 0);
    ~QuoteCalendarWidget();

private slots:

private:
    Ui::QuoteCalendarWidget *ui;
};

#endif // QUOTECALENDARWIDGET_H
