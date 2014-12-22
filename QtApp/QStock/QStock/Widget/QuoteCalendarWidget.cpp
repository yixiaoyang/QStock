#include "QuoteCalendarWidget.h"
#include "ui_QuoteCalendarWidget.h"

QuoteCalendarWidget::QuoteCalendarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuoteCalendarWidget)
{
    ui->setupUi(this);
}

QuoteCalendarWidget::~QuoteCalendarWidget()
{
    delete ui;
}
