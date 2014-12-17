#ifndef DATERANGE_H
#define DATERANGE_H

#include <QDate>

class DateRange
{
public:
    short sDay;
    short sMonth;
    short sYear;
    short eDay;
    short eMonth;
    short eYear;
    DateRange(QDate s, QDate e);
};

#endif // DATERANGE_H
