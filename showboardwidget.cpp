#include "showboardwidget.h"
#include "ui_showboardwidget.h"

ShowBoardWidget::ShowBoardWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowBoardWidget)
{
    ui->setupUi(this);

    setFixedSize(255,288);

    getLBSum(10);

    initData();
    initLayout();
    initConnect();

    setLBText();
}

ShowBoardWidget::~ShowBoardWidget()
{
    delete ui;
}

void ShowBoardWidget::initData()
{
    drag_wheelPressedFlag = false;
    drag_mousePressedFlag = false;
    drag_beginPoint = QPoint(0,0);

    currentPosHead = QPoint(2,40*0+10);
    currentPosTail = QPoint(2,40*6+10);
}

void ShowBoardWidget::initLayout()
{
    // 无边框设置
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    for (int i = 0; i < m_LBSum; i++)
    {
        lb_labelBoard[i] = new QLabel(this);
        lb_labelBoard[i]->setGeometry(2,40*i+10,235,30);
        lb_labelBoard[i]->setStyleSheet("QLabel{background:transparent;}"
                                        "QLabel{border-image:url(:/image/softImage/framework/labelboard.png)}");
//        lb_labelBoard[i]->setAlignment(Qt::AlignCenter);
    }
}

void ShowBoardWidget::initConnect()
{

}

void ShowBoardWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        drag_wheelPressedFlag = true;
        drag_mousePressedFlag = true;
        for (int i = 0; i < m_LBSum; i++)
        {
            drag_beginPoint = event->pos();
            currentPos[i] = lb_labelBoard[i]->pos();
        }
    }
    if(event->button()==Qt::RightButton)
    {
        //暂未设计
    }
}

void ShowBoardWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(drag_mousePressedFlag)
    {
        for (int i = 0; i < m_LBSum; i++)
        {
            lb_labelBoard[i]->move(2,currentPos[i].y()+event->pos().y()-drag_beginPoint.y());
        }
    }
}

void ShowBoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    drag_mousePressedFlag = false;
    for (int i = 0; i < m_LBSum; i++)
    {
        currentPos[i] = lb_labelBoard[i]->pos();
    }

    if(currentPos[0].y() - currentPosHead.y() > 0)  //回弹效果
    {
        for (int i = 0; i < m_LBSum; i++)
        {
            lb_labelBoard[i]->move(2,40*i+10);
        }
    }
    if(currentPos[m_LBSum-1].y() - currentPosTail.y() < 0)
    {
        for (int i = m_LBSum-1,j = 6; i >= 0; i--,j--)
        {
            lb_labelBoard[i]->move(2,40*j+10);
        }
    }

    for (int i = 0; i < m_LBSum; i++)
    {
        currentPos[i] = lb_labelBoard[i]->pos();
    }

    event->accept();
}

void ShowBoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.drawPixmap(0,0,width(),height(),QPixmap(":/image/softImage/framework/TimeBackground.png"));
    painter.drawPixmap(10,1,9,288-3,QPixmap(":/image/softImage/column.png"));

    event->accept();
}

void ShowBoardWidget::wheelEvent(QWheelEvent *event)
{
    if(drag_wheelPressedFlag)
    {
        if(event->delta() > 0)  //如果滚轮往上滚
        {
            if(lb_labelBoard[m_LBSum-1]->pos() != currentPosTail)  //并且排行榜最末处于可视排行榜最后
            {
                for (int i = 0; i < m_LBSum; i++)
                {
                    lb_labelBoard[i]->move(2,currentPos[i].y()-10);
                }
            }

        }
        else  //向下滚
        {
            if(lb_labelBoard[0]->pos() != currentPosHead)  //并且排行榜第一不处于第一位置
            {
                for (int i = 0; i < m_LBSum; i++)
                {
                    lb_labelBoard[i]->move(2,currentPos[i].y()+10);
                }
            }
        }
        for (int i = 0; i < m_LBSum; i++)
        {
            currentPos[i] = lb_labelBoard[i]->pos();
        }
    }
}

void ShowBoardWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        // 鼠标双击的标签显示个人信息
    }
}

void ShowBoardWidget::getLBSum(const int num)
{
    m_LBSum = num;
}

void ShowBoardWidget::setLBText()
{
    for(int i = 0; i < m_LBSum; i++)
    {
        lb_labelBoard[i]->setText("     "+QString::number(i+1,10));
    }
}
