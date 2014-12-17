#include "DateRange.h"

DateRange::DateRange(QDate s, QDate e)
{
    eDay=e.day();
    eMonth=e.month();
    eYear=e.year();
    sDay=s.day();
    sMonth=s.month();
    sYear=s.year();
}
