#include "menberwidget.h"
#include "ui_menberwidget.h"

MenberWidget::MenberWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenberWidget)
{
    ui->setupUi(this);
    setFixedSize(600,292);


    initData();
    initLayout();
    initConnect();
}

MenberWidget::~MenberWidget()
{
    delete ui;
}

void MenberWidget::initData()
{
    drag_legalSpaceFlag = false;
    drag_reachStandardFlag = false;
    drag_wheelPressedFlag = false;
    drag_mousePressedFlag = false;
    drag_beginPoint = QPoint(0,0);

    currentPosHead = QPoint(268+2,40*0+10);
    currentPosTail = QPoint(268+2,40*6+10);

    m_boardSum = 0;
    m_choiceNum = 0;
}

void MenberWidget::initLayout()
{
    lb_thisWeek = new QLabel(this);
    lb_thisWeekDate = new QLabel(this);
    lb_reachStandard = new QLabel(this);
    lb_thisTime = new QLabel(this);
    lb_totalTime = new QLabel(this);
    lb_name = new QLabel(this);
    lb_motto = new QLabel(this);

    for (int i = 0; i < /*m_boardSum*/N; i++)
    {
        lb_Board[i] = new QLabel(this);
        lb_HeadImage[i] = new QLabel(this);
        lb_Name[i] = new QLabel(this);
        lb_Time[i] = new QLabel(this);
    }

    lb_thisWeek->setGeometry(68,52,70,30);
    lb_thisWeekDate->setGeometry(68,82,70,56);
    lb_reachStandard->setGeometry(158,52,110,30);
    lb_thisTime->setGeometry(158,82,110,20);
    lb_totalTime->setGeometry(158,102,110,36);
    lb_name->setGeometry(5,150,270,30);
    lb_motto->setGeometry(5,190,270,90);

    lb_thisWeek->setText("本周");
    lb_thisWeekDate->setText(getStartDate().toString("MM月dd日\n")+QString("   至\n")+getEndDate().toString("MM月dd日\n"));
    lb_reachStandard->setText("达标否");
    lb_thisTime->setText("已累计时间");
    lb_name->setText("请登录");


    lb_name->setAlignment(Qt::AlignCenter);
    lb_motto->setAlignment(Qt::AlignCenter);

    lb_motto->setWordWrap(true);


    lb_reachStandard->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#a6a6a6}");
    lb_thisWeek->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#FFFFFF}");
    lb_thisWeekDate->setStyleSheet("QLabel{background:transparent;font-size:12px;font-weight:bold;color:#FFFFFF}");
    lb_thisTime->setStyleSheet("QLabel{background:transparent;font-size:12px;font-weight:bold;color:#FFFFFF}");
    lb_totalTime->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#00FFFF}");
    lb_name->setStyleSheet("QLabel{background:transparent;font-size:24px;font-weight:bold;color:#fff582}");
    lb_motto->setStyleSheet("QLabel{background:transparent;font-size:20px;font-weight:bold;color:#e9a4ff}");
}

void MenberWidget::initConnect()
{

}

void MenberWidget::setUser(const User &user)
{

}

void MenberWidget::setStatisticUser(const StatisticUser &bag)
{
/***
 * 返回的一周统计时间存放在User 的getTempTime()中
*/
    int length = 0;
    for(int i = 0; i < bag.statisticPeople; i++)
    {
        if(bag.user[i].getWeek().day[0]==0) continue;
        book.user[length++] = bag.user[i];
    }

    book.statisticPeople = length;

    User temp;
    for(int i = 0; i < bag.statisticPeople; i++)
    {
        for(int j = i; j < bag.statisticPeople; j++)
        {
            if(book.user[j].getTempTime() > book.user[i].getTempTime())
            {

                temp = book.user[j];
                book.user[j] = book.user[i];
                book.user[i] = temp;
            }
        }
    }

    setBoard(book);


    UpdateReachStandard();
    UpdateLeftInformation();
}

void MenberWidget::initPlace()
{
    for (int i = 0; i < m_boardSum; i++)
    {
        lb_Board[i]->move(268+2,40*i+10);
        UpdateLabelSpace(i);
    }

    m_choiceNum = 0;
}

void MenberWidget::initBoard()
{
    for (int i = 0; i < m_boardSum; i++)
    {
        lb_Board[i]->setGeometry(268+2,40*i+10,255,40);
        lb_Board[i]->setStyleSheet("QLabel{background:transparent;}"
                                   "QLabel{border-image:url(:/image/softImage/framework/labelboard.png)}");
        lb_HeadImage[i]->setStyleSheet("QLabel{background:transparent;}");
        lb_Name[i]->setStyleSheet("QLabel{background:transparent;}");
        QPalette pn;
        pn.setColor(QPalette::WindowText,Qt::gray);
        lb_Name[i]->setPalette(pn);
        lb_Time[i]->setStyleSheet("QLabel{background:transparent;}");
        QPalette pt;
        pt.setColor(QPalette::WindowText,Qt::blue);
        lb_Time[i]->setPalette(pt);
    }
}

void MenberWidget::setCurrentPos()
{
    for (int i = 0; i < m_boardSum; i++)
    {
        currentPos[i] = lb_Board[i]->pos();
    }
}

void MenberWidget::setBoardSum(int sum)
{
    m_boardSum = sum;
}

void MenberWidget::setBoardText(StatisticUser &user)
{
    setBoardTime(user);

    for(int i = 0; i < m_boardSum; i++)
    {
        lb_HeadImage[i]->setGeometry(lb_Board[i]->pos().x()+40,lb_Board[i]->pos().y()+6,30,30);
        QPixmap ph(user.user[i].getHeadImagePath());
        ph.scaled(lb_HeadImage[i]->size(), Qt::KeepAspectRatio);
        lb_HeadImage[i]->setScaledContents(true);
        lb_HeadImage[i]->setPixmap(ph);

        lb_Name[i]->setGeometry(lb_Board[i]->pos().x()+30,lb_Board[i]->pos().y()+6,100,30);
        lb_Name[i]->setText(user.user[i].getTrueName());

        lb_Time[i]->setGeometry(lb_Board[i]->pos().x()+190,lb_Board[i]->pos().y()+6,70,30);
        lb_Time[i]->setText(QString::number(m_Hours[i])+"时"+QString::number(m_Minute[i])+"分");
    }
}

void MenberWidget::setBoardTime(StatisticUser &user)
{
    for(int i = 0; i < m_boardSum; i++)
    {
        m_Hours[i] = user.user[i].getTempTime() / 3600;
        m_Minute[i] = user.user[i].getTempTime() % 3600 / 60;
    }
}

void MenberWidget::setBoard(StatisticUser &user)
{
    setBoardSum(user.statisticPeople);
    setBoardText(user);
    initPlace();
    initBoard();
    m_choiceNum = 0;
}

void MenberWidget::mousePressEvent(QMouseEvent *event)
{
    for (int i = 0; i < m_boardSum; i++)
    {
        setLegalSpaceFlag(event->pos());

        if (isLegalSpace() && event->pos().y() > currentPos[i].y() + 2 && event->pos().y() < currentPos[i].y() + 40-3)
        {
            m_choiceNum = i;

            UpdateReachStandard();
            UpdateLeftInformation();
        }
    }

    if(event->button()==Qt::LeftButton && isLegalSpace())
    {
        drag_wheelPressedFlag = true;
        drag_mousePressedFlag = true;
        for (int i = 0; i < m_boardSum; i++)
        {
            drag_beginPoint = event->pos();
            currentPos[i] = lb_Board[i]->pos();
        }
    }
    if(event->button()==Qt::RightButton)
    {
        //暂未设计
    }

}

void MenberWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(drag_mousePressedFlag)
    {
        for (int i = 0; i < m_boardSum; i++)
        {
            lb_Board[i]->move(268+2,currentPos[i].y()+event->pos().y()-drag_beginPoint.y());
            UpdateLabelSpace(i);
        }
    }
}

void MenberWidget::mouseReleaseEvent(QMouseEvent *event)
{
    drag_mousePressedFlag = false;
    setCurrentPos();

    eff_reboundMove(m_boardSum);  //回弹效果

    setCurrentPos();

    event->accept();
}

void MenberWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(268+10,2,9,288-2,QPixmap(":/image/softImage/framework/column.png"));

    event->accept();
}

void MenberWidget::wheelEvent(QWheelEvent *event)
{
    if(drag_wheelPressedFlag && isLegalSpace())
    {
        eff_fixationWheel(event);  // 滚轮固定效果

        setCurrentPos();
    }
}

void MenberWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        // 鼠标双击的标签显示个人信息
    }
}

int MenberWidget::getDayOfWeek(QDate date)
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

void MenberWidget::setHoursAndMinute(int time)
{
    m_hours = time / 3600;
    m_minute = time % 3600 / 60;
}

void MenberWidget::setShowNameAndMotto(int &orderNum)
{
    lb_name->setText(book.user[orderNum].getTrueName());

    QString mottoWord = book.user[orderNum].getMotto();
    int mottoLength = mottoWord.length();
    if(mottoLength <= 12) lb_motto->resize(270,30);
    if(mottoLength > 12 && mottoLength <= 24) lb_motto->resize(270,60);
    if(mottoLength > 24 && mottoLength <= 48) lb_motto->resize(270,90);

    lb_motto->setText(mottoWord);
}

void MenberWidget::UpdateReachStandard()
{
    setHoursAndMinute(book.user[m_choiceNum].getTempTime());

    setReachStandardFlag(m_hours);

    if(isReachStandard())
    {
        lb_reachStandard->setText("已达标");
        lb_reachStandard->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#00FFFF}");
        lb_totalTime->setText(QString::number(m_hours)+"时"+QString::number(m_minute)+"分");
    }
    else
    {
        lb_reachStandard->setText("未达标");
        lb_reachStandard->setStyleSheet("QLabel{background:transparent;font-size:18px;font-weight:bold;color:#FF0000}");
        lb_totalTime->setText(QString::number(m_hours)+"时"+QString::number(m_minute)+"分");
    }
}

void MenberWidget::UpdateLeftInformation()
{
    setShowNameAndMotto(m_choiceNum);
}

void MenberWidget::UpdateLabelSpace(const int i)
{
    lb_HeadImage[i]->move(lb_Board[i]->pos().x()+40,lb_Board[i]->pos().y()+6);
    lb_Name[i]->move(lb_Board[i]->pos().x()+70,lb_Board[i]->pos().y()+6);
    lb_Time[i]->move(lb_Board[i]->pos().x()+190,lb_Board[i]->pos().y()+6);
}

void MenberWidget::setReachStandardFlag(int &time)
{
    if(time >= STANDARDS_HOURS)
    {
        drag_reachStandardFlag = true;
    }
    else
    {
        drag_reachStandardFlag = false;
    }
}

void MenberWidget::setLegalSpaceFlag(QPoint point)
{
    if(point.y() > 0 && point.y() < this->height() + 27 && point.x() > 300 && point.x() < 524)
    {
        drag_legalSpaceFlag = true;
    }
    else
    {
        drag_legalSpaceFlag = false;
    }
}

bool MenberWidget::isReachStandard()
{
    return drag_reachStandardFlag;
}

bool MenberWidget::isLegalSpace()
{
    return drag_legalSpaceFlag;
}

QDate MenberWidget::getStartDate()
{
    QDate currentDate = QDate::currentDate();
    int dayOfWeek = getDayOfWeek(currentDate);

    if(dayOfWeek>=START_DATE)
        return currentDate.addDays(START_DATE-dayOfWeek);
    else
        return currentDate.addDays(-(7-START_DATE)-dayOfWeek);

}

QDate MenberWidget::getEndDate()
{
    return getStartDate().addDays(6);
}

void MenberWidget::eff_reboundMove(const int &sum)
{
    if (m_boardSum <= 0)
    {
        return;
    }

    if(currentPos[0].y() - currentPosHead.y() > 0)
    {
        initPlace();
    }

    if(sum <= 7)
    {
        if(currentPos[m_boardSum-1].y() - currentPosTail.y() < 0)
        {
            for (int i = 0; i < m_boardSum; i++)
            {
                lb_Board[i]->move(268+2,40*i+10);
                UpdateLabelSpace(i);
            }
        }
    }
    else
    {
        if(currentPos[m_boardSum-1].y() - currentPosTail.y() < 0)
        {
            for (int i = m_boardSum-1,j = 6; i >= 0; i--,j--)
            {
                lb_Board[i]->move(268+2,40*j+10);
                UpdateLabelSpace(i);
            }
        }
    }
}

void MenberWidget::eff_fixationWheel(QWheelEvent *event)
{
    if (m_boardSum <= 0)
    {
        return;
    }

    if(event->delta() < 0)  //如果滚轮往下滚
    {
        if (m_boardSum >= 7)
        {
            if(lb_Board[m_boardSum-1]->pos().y() > currentPosTail.y())  //并且排行榜最末不处于可视排行榜最后
            {
                for (int i = 0; i < m_boardSum; i++)
                {
                    lb_Board[i]->move(268+2,currentPos[i].y()-WHEEL_SPEED);
                    UpdateLabelSpace(i);
                }
            }
        }
        else
        {
            //不允许滚动
        }
    }
    else  //向上滚
    {
        if(lb_Board[0]->pos().y() < currentPosHead.y())  //并且排行榜第一不处于可视排行榜第一位置
        {
            for (int i = 0; i < m_boardSum; i++)
            {
                lb_Board[i]->move(268+2,currentPos[i].y()+WHEEL_SPEED);
                UpdateLabelSpace(i);
            }
        }
    }
}

