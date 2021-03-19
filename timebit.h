#ifndef TIMEBIT_H
#define TIMEBIT_H


class TimeBit
{
public:
    TimeBit();
    TimeBit(int timeLength);
    ~TimeBit();

    void setTimeLength(int timeLength);
    void setTimeBit(int timeLength);
    int getTimeLength();
    double getTimeHour();
    int getHourTen();
    int getHourOne();
    int getMinuteOne();
    int getMinuteTen();
    bool isValue();

private:
    bool value;
    int data_timeLength;
    int data_hour_ten;
    int data_hour_one;
    int data_minute_ten;
    int data_minute_one;
};

#endif // TIMEBIT_H
