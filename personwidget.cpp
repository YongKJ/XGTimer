#include "personwidget.h"
#include "ui_personwidget.h"

const int DIS_Y = 50;//效果label的初始位置
const int ENDDIS_Y = 115;//效果lebel的目标位置
const double T = 2000.0;//效果lebel的运动时间
const double A_Y = 2.0*(ENDDIS_Y-DIS_Y)/(T*T);//效果lebel的加速度
const double V_Y = A_Y*T;//效果label的初始速度
const int FRAMERATE = 1;//定时器帧数
const QPoint POINT = QPoint(342,230);//柱状图起始点
const int TOTALWIDTH = 186;//柱状图总宽
const int TOTALHEIGHT = 173;//柱状图总高
const double WIDTH = TOTALWIDTH*1.0/7;//柱状图的每格宽度
const double HEIGHT = TOTALHEIGHT*1.0/11;//柱状图的每格高度
const double MAXHOUR = 11.3;//柱状图显示的最大时间（防止超过柱状图高度）
const int GAP = 5;//每个柱子的间隙
const double PAINT_V = 0.1;//画柱子的速度

PersonWidget::PersonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonWidget)
{
    ui->setupUi(this);
    setFixedSize(600,292);
    setMouseTracking(true);

    InitData();
    InitLayout();
    InitConnect();
}

PersonWidget::~PersonWidget()
{
    delete ui;
}

void PersonWidget::setUser(User user, bool isStartPaint)
{
    operator_updateShowTime(user.getWeekTime());
    setDataWeekDay(user.getWeek().day);

    if(isStartPaint)
        operator_startPaintTimer();
}

void PersonWidget::setNoUser()
{
    int week[] = {0,88880,5649,25498,30041,11100,3758,6666};
    User user;
    user.setWeek(week);
    operator_updateShowTime(user.getWeekTime());
    setDataWeekDay(week);
}

void PersonWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(25,30,548,218,QPixmap(":/image/TimeBackground_1.png"));
    painter.drawPixmap(315,38,212,205,QPixmap(":/image/DataGraph.png"));

    for(int i = 0;i < 7; i++)
    {
        if(isChosedFlag[i])
            painter.setBrush(Qt::red);
        else
            painter.setBrush(QColor(255, 160, 90));

        if(Timer_paintHeight<MAXHOUR*HEIGHT && Timer_paintHeight<data_weekDay[i].getTimeHour()*HEIGHT)
            painter.drawRect(POINT.x()+WIDTH*i , POINT.y()-Timer_paintHeight , WIDTH-GAP , Timer_paintHeight);
        else
        {
            if(data_weekDay[i].getTimeHour()>=MAXHOUR)
                painter.drawRect(POINT.x()+WIDTH*i , POINT.y()-MAXHOUR*HEIGHT , WIDTH-GAP , MAXHOUR*HEIGHT);
            else
                painter.drawRect(POINT.x()+WIDTH*i , POINT.y()-data_weekDay[i].getTimeHour()*HEIGHT , WIDTH-GAP , data_weekDay[i].getTimeHour()*HEIGHT);
        }

        if(maxValue<=data_weekDay[i].getTimeHour()&&painterTimer->isActive()) painterTimer->stop();
    }


    event->accept();
}

void PersonWidget::mouseMoveEvent(QMouseEvent *event)
{
    for(int i=0;i<7;i++) isChosedFlag[i] = false;

    if(QRect(POINT.x(),POINT.y()-TOTALHEIGHT, TOTALWIDTH, TOTALHEIGHT).contains(event->pos()))
    {
        for(int i = 0;i < 7;i++)
            if(QRect(POINT.x()+WIDTH*i,POINT.y()-TOTALHEIGHT,WIDTH-GAP,TOTALHEIGHT).contains(event->pos()))
            {
                QToolTip::showText(event->globalPos(), QString("当日在线时长：%1%2小时%3%4分钟").arg(data_weekDay[i].getHourTen()).
                                   arg(data_weekDay[i].getHourOne()).
                                   arg(data_weekDay[i].getMinuteTen()).
                                   arg(data_weekDay[i].getMinuteOne()));
                isChosedFlag[i] = true;
                break;
            }
    }
    else
    {
        QToolTip::hideText();
        event->ignore();
    }

    update();
}

void PersonWidget::InitData()
{
    myTimer = new QTimer(this);
    painterTimer = new QTimer(this);
    data_timeBit = new TimeBit;
    data_weekDay = new TimeBit[7];

    labelDistance = DIS_Y;
    Timer_paintHeight = MAXHOUR*HEIGHT;
    timerTime = 0.0;
    maxValue = 0;
    int week[] = {0,88880,5649,25498,30041,11100,3758,6666};
    setDataWeekDay(week);

    for(int i=0;i<7;i++)
        isChosedFlag[i]=false;

    for(int i=0;i<10;i++)
        s_num[i] = QString("QLabel{background:transparent;border-image:url(:image/softImage/framework/%1.png)}").arg(i);

}

void PersonWidget::InitLayout()
{
    lb_text = new QLabel(this);
    lb_hour_one = new QLabel(this);
    lb_hour_ten = new QLabel(this);
    lb_minute_ten = new QLabel(this);
    lb_minute_one = new QLabel(this);


    lb_text->setGeometry(135,85,150,20);
    lb_hour_ten->setGeometry(90,115,43,68);
    lb_hour_one->setGeometry(137,115,43,68);
    lb_minute_ten->setGeometry(192,115,43,68);
    lb_minute_one->setGeometry(239,115,43,68);

    QFont font;
    font.setFamily("方正兰亭黑简体");
    lb_text->setFont(font);
    lb_text->setText("本周在线总时长");

    lb_text->setStyleSheet("QLabel{background:transparent;font-size:14px;font-weight:bold;color:#FFFFFF}");
    lb_hour_ten->setStyleSheet(s_num[0]);
    lb_hour_one->setStyleSheet(s_num[0]);
    lb_minute_ten->setStyleSheet(s_num[0]);
    lb_minute_one->setStyleSheet(s_num[0]);

}

void PersonWidget::InitConnect()
{
    connect(painterTimer,SIGNAL(timeout()),this,SLOT(slot_painterTimeOut()));
}

void PersonWidget::operator_updateShowTime(int timeLength)
{
    data_timeBit->setTimeBit(timeLength);
    setTimeLabelStyle(data_timeBit->getHourOne(),lb_hour_one);
    setTimeLabelStyle(data_timeBit->getHourTen(),lb_hour_ten);
    setTimeLabelStyle(data_timeBit->getMinuteOne(),lb_minute_one);
    setTimeLabelStyle(data_timeBit->getMinuteTen(),lb_minute_ten);
}

void PersonWidget::setTimeLabelStyle(int time,QLabel *lb_Label)
{
    lb_Label->setStyleSheet(s_num[time]);
}

void PersonWidget::setDataWeekDay(const int* const weekDay)
{
    int max = weekDay[0];

    for(int i=1;i<=7;i++)
    {
        data_weekDay[i-1] = weekDay[i];
        if(weekDay[i]>max)
            max=weekDay[i];
    }

   maxValue = max;
}

void PersonWidget::operator_startPaintTimer()
{
    Timer_paintHeight = 0.0;
    if(!painterTimer->isActive()) painterTimer->start(1);
}

void PersonWidget::slot_painterTimeOut()
{
    Timer_paintHeight += PAINT_V;
    update();

    if(Timer_paintHeight>MAXHOUR*HEIGHT)
    {
        painterTimer->stop();
    }
}
