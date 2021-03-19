#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QTimer>
#include "timebit.h"
#include "user.h"

#define START_DATE 5
//#define END_DATE 4

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void setUser(User user);
    void setNoUser();

    void operator_addSecond(int dayTimeLength);
    void operator_showTime(int timeLength);

private:
    Ui::MainWidget *ui;

    void initData();
    void initLayout();
    void initConnect();

    int getDayOfWeek(QDate date);
    QDate getStartDate();
    QDate getEndDate();
    void setTimeLabelStyle(int num, QLabel *lb_Label);

    QString s_num[10];

    TimeBit *effect_timeBit;//目标效果时间
    double labelDistanceY;//效果label的y轴位置
    double labelDistanceX;//效果label的x轴位置
    double effect_timerTime;//效果计时器时间
    QTimer *effectTimer;//动态效果计时器

    QTimer *user_timer;

    QLabel *lb_today;
    QLabel *lb_thisWeek;
    QLabel *lb_todayDate;
    QLabel *lb_thisWeekDate;
    QLabel *lb_onLineTime;
    QLabel *lb_hour_ten;
    QLabel *lb_hour_one;
    QLabel *lb_minute_ten;
    QLabel *lb_minute_one;
    QLabel *lb_second_ten;
    QLabel *lb_second_one;
    QLabel *lb_smallBackground;

    QLabel *temp_minute_one;
    QLabel *temp_minute_ten;
    QLabel *temp_hour_one;
    QLabel *temp_hour_ten;


private slots:
    void effect_TimeOut();

};

#endif // MAINWIDGET_H
