#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QFont>
#include <QDebug>
#include <cstdlib>

const double T = 2000.0;//效果y轴lebel的运动时间
const int DIS_Y = 5;//效果y轴label的初始位置
const int ENDDIS_Y = 105;//效果y轴lebel的目标位置
const double A_Y = 2.0*(ENDDIS_Y-DIS_Y)/(T*T);//效果y轴lebel的加速度
const double V_Y = A_Y*T;//效果y轴label的初始速度

const int DIS_X = 30;//效果y轴label的初始位置
const int ENDDIS_X = 50;//效果x轴lebel的目标位置
const double A_X = 2.0*(ENDDIS_X-DIS_X)/(T*T);//效果x轴lebel的加速度
const double V_X = A_X*T;//效果x轴label的初始速度

const int FRAMERATE = 1;//定时器帧数

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setFixedSize(600,292);

    initData();
    initLayout();
    initConnect();

    operator_showTime(47640);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setUser(User user)
{
    operator_showTime(user.getWeek().day[user.getNowOfWeekDay()]);
}

void MainWidget::setNoUser()
{
    operator_showTime(0);
    operator_addSecond(0);
}

void MainWidget::operator_addSecond(int dayTimeLength)
{
    setTimeLabelStyle(dayTimeLength%60/10,lb_second_ten);
    setTimeLabelStyle(dayTimeLength%60%10,lb_second_one);

    if(dayTimeLength%60==0) operator_showTime(dayTimeLength);
}

void MainWidget::initData()
{
    labelDistanceY = DIS_Y;
    labelDistanceX = DIS_X;
    effect_timerTime = 0.0;
    effect_timeBit = new TimeBit;
    effectTimer = new QTimer(this);
    user_timer = new QTimer(this);

    for(int i=0;i<10;i++)
        s_num[i] = QString("QLabel{background:transparent;border-image:url(:image/softImage/framework/%1.png)}").arg(i);
}

void MainWidget::initLayout()
{
    lb_smallBackground = new QLabel(this);
    lb_today = new QLabel(this);
    lb_todayDate = new QLabel(this);
    lb_thisWeek = new QLabel(this);
    lb_thisWeekDate = new QLabel(this);
    lb_onLineTime = new QLabel(this);
    lb_hour_ten = new QLabel(this);
    lb_hour_one = new QLabel(this);
    lb_minute_ten = new QLabel(this);
    lb_minute_one = new QLabel(this);
    lb_second_ten = new QLabel(this);
    lb_second_one = new QLabel(this);

    lb_smallBackground->setGeometry(180,50,394,165);
    lb_today->setGeometry(55,60,55,25);
    lb_todayDate->setGeometry(55,93,115,20);
    lb_thisWeek->setGeometry(55,126,55,25);
    lb_thisWeekDate->setGeometry(55,155,70,60);
    lb_onLineTime->setGeometry(320,65,125,30);
    lb_hour_ten->setGeometry(200,105,62,94);
    lb_hour_one->setGeometry(266,105,62,94);
    lb_minute_ten->setGeometry(345,105,62,94);
    lb_minute_one->setGeometry(411,105,62,94);
    lb_second_ten->setGeometry(490,150,31,47);
    lb_second_one->setGeometry(525,150,31,47);

    QFont font;
    font.setFamily("方正兰亭黑简体");
    lb_today->setFont(font);
    lb_todayDate->setFont(font);
    lb_thisWeek->setFont(font);
    lb_thisWeekDate->setFont(font);
    lb_onLineTime->setFont(font);

    lb_today->setText("今天");
    lb_thisWeek->setText("本周");
    lb_onLineTime->setText("今日在线时长");
    lb_todayDate->setText(QDate::currentDate().toString("MM月dd日 dddd"));
    lb_thisWeekDate->setText(getStartDate().toString("MM月dd日\n")+QString("   至\n")+getEndDate().toString("MM月dd日"));

    lb_today->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#FFFFFF}");
    lb_thisWeek->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#FFFFFF}");
    lb_todayDate->setStyleSheet("QLabel{background:transparent;font-size:12px;font-weight:bold;color:#FFFFFF}");
    lb_thisWeekDate->setStyleSheet("QLabel{background:transparent;font-size:12px;font-weight:bold;color:#FFFFFF}");
    lb_onLineTime->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#FFFFFF}");
    lb_smallBackground->setStyleSheet("QLabel{border-image:url(:image/TimeBackground.png)}");
    lb_hour_ten->setStyleSheet(s_num[0]);
    lb_hour_one->setStyleSheet(s_num[0]);
    lb_minute_ten->setStyleSheet(s_num[0]);
    lb_minute_one->setStyleSheet(s_num[0]);
    lb_second_ten->setStyleSheet(s_num[0]);
    lb_second_one->setStyleSheet(s_num[0]);

    temp_hour_one = new QLabel(this);
    temp_hour_ten = new QLabel(this);
    temp_minute_one = new QLabel(this);
    temp_minute_ten = new QLabel(this);
}

void MainWidget::initConnect()
{
    connect(effectTimer,SIGNAL(timeout()),this,SLOT(effect_TimeOut()));
}

int MainWidget::getDayOfWeek(QDate date)
{
    int m = date.toString("MM").toInt();//m是月数
    int d = date.toString("dd").toInt();//d是日数
    int y = date.toString("yy").toInt();//y是已知公元年份的后两位数字
    int C = (date.toString("yyyy").toInt())/100;//C是公元年份的前两位数字

    switch(m)
    {
    case 1:
        m=13;break;
    case 2:
        m=14;break;
    default:
        break;
    }

    int weekDay = C/4-2*C+y+y/4+26*(m+1)/10+d-1;//星期数
    while(weekDay>7)
    {
        weekDay=weekDay-7;
    }

    return weekDay;
}

QDate MainWidget::getStartDate()
{
    QDate currentDate = QDate::currentDate();
    int dayOfWeek = getDayOfWeek(currentDate);

    if(dayOfWeek>=START_DATE)
        return currentDate.addDays(START_DATE-dayOfWeek);
    else
        return currentDate.addDays(-(7-START_DATE)-dayOfWeek);

}

QDate MainWidget::getEndDate()
{
//    QDate currentDate = QDate::currentDate();
//    int dayOfWeek = getDayOfWeek(currentDate);

//    if(dayOfWeek>END_DATE)
//        return currentDate.addDays((7-END_DATE)+(8-dayOfWeek));
//    else
//        return currentDate.addDays(END_DATE-dayOfWeek);
    return getStartDate().addDays(6);
}

void MainWidget::setTimeLabelStyle(int num,QLabel *lb_Label)
{
    lb_Label->setStyleSheet(s_num[num]);
}

void MainWidget::operator_showTime(int timeLength)
{   
    TimeBit *tempTimeBit = new TimeBit(timeLength);

//    if(!tempTimeBit->isValue())
//    {
//        delete tempTimeBit;
//        return;
//    }

    labelDistanceY = DIS_Y;
    labelDistanceX = DIS_X;

    temp_hour_ten->setGeometry(270+DIS_X,labelDistanceY,62,94);
    temp_hour_one->setGeometry(336+DIS_X,labelDistanceY,62,94);
    temp_minute_ten->setGeometry(415+DIS_X,labelDistanceY,62,94);
    temp_minute_one->setGeometry(481+DIS_X,labelDistanceY,62,94);

    setTimeLabelStyle(tempTimeBit->getHourOne(),temp_hour_one);
    setTimeLabelStyle(tempTimeBit->getHourTen(),temp_hour_ten);
    setTimeLabelStyle(tempTimeBit->getMinuteOne(),temp_minute_one);
    setTimeLabelStyle(tempTimeBit->getMinuteTen(),temp_minute_ten);

    temp_hour_ten->show();
    temp_hour_one->show();
    temp_minute_ten->show();
    temp_minute_one->show();
    if(effect_timeBit->getHourOne() == tempTimeBit->getHourOne()) temp_hour_one->hide();
    if(effect_timeBit->getHourTen() == tempTimeBit->getHourTen()) temp_hour_ten->hide();
    if(effect_timeBit->getMinuteOne() == tempTimeBit->getMinuteOne()) temp_minute_one->hide();
    if(effect_timeBit->getMinuteTen() == tempTimeBit->getMinuteTen()) temp_minute_ten->hide();

    effect_timeBit->setTimeBit(timeLength);
    effectTimer->start(FRAMERATE);

    delete tempTimeBit;
}

void MainWidget::effect_TimeOut()
{
    effect_timerTime = effect_timerTime+FRAMERATE*1.0/1000;
    labelDistanceY += V_Y*effect_timerTime - (A_Y*effect_timerTime*effect_timerTime)/2;
    labelDistanceX += V_X*effect_timerTime - (A_X*effect_timerTime*effect_timerTime)/2;

    if(labelDistanceY >= ENDDIS_Y)
    {
        effect_timerTime = 0.0;
        if(effectTimer->isActive()) effectTimer->stop();

        temp_hour_ten->hide();
        temp_hour_one->hide();
        temp_minute_ten->hide();
        temp_minute_one->hide();

        setTimeLabelStyle(effect_timeBit->getHourOne(),lb_hour_one);
        setTimeLabelStyle(effect_timeBit->getHourTen(),lb_hour_ten);
        setTimeLabelStyle(effect_timeBit->getMinuteOne(),lb_minute_one);
        setTimeLabelStyle(effect_timeBit->getMinuteTen(),lb_minute_ten);

        return;
    }

    temp_hour_ten->setGeometry(250-labelDistanceX,labelDistanceY,62,94);
    temp_hour_one->setGeometry(316-labelDistanceX,labelDistanceY,62,94);
    temp_minute_ten->setGeometry(395-labelDistanceX,labelDistanceY,62,94);
    temp_minute_one->setGeometry(461-labelDistanceX,labelDistanceY,62,94);
}
