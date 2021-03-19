#include "timebit.h"
#include <QDebug>

TimeBit::TimeBit()
{
    value = true;
    data_minute_one = 0;
    data_minute_ten = 0;
    data_hour_one = 0;
    data_hour_ten = 0;
    data_timeLength = 0;
}

TimeBit::TimeBit(int timeLength)
{
    setTimeBit(timeLength);
}

TimeBit::~TimeBit()
{

}

void TimeBit::setTimeLength(int timeLength)
{
    data_timeLength = timeLength;
    if(timeLength<0 || timeLength>=99*3600+59*60)
    {
        value = false;
    }
    else
    {
        value = true;
    }

}

void TimeBit::setTimeBit(int timeLength)
{
    setTimeLength(timeLength);
    if(!isValue())
    {
        data_hour_one = 9;
        data_hour_ten = 9;
        data_minute_one = 9;
        data_minute_ten = 5;
        return;
    }

    data_hour_one = data_timeLength/3600%10;
    data_hour_ten = data_timeLength/3600/10;
    data_minute_one = data_timeLength%3600/60%10;
    data_minute_ten = data_timeLength%3600/60/10;
}

int TimeBit::getTimeLength()
{
    return data_timeLength;
}

double TimeBit::getTimeHour()
{
    return data_timeLength*1.0/3600;
}

int TimeBit::getHourTen()
{
    return data_hour_ten;
}

int TimeBit::getHourOne()
{
    return data_hour_one;
}

int TimeBit::getMinuteOne()
{
    return data_minute_one;
}

int TimeBit::getMinuteTen()
{
    return data_minute_ten;
}

bool TimeBit::isValue()
{
    return value;
}

