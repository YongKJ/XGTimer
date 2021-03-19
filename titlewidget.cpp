#include "titlewidget.h"
#include "ui_titlewidget.h"

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    setFixedSize(600,52);

    initLayout();
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::initLayout()
{
    bt_close = new QPushButton(this);
    bt_minize = new QPushButton(this);
    bt_setting = new QPushButton(this);
    bt_login = new QPushButton(this);

    bt_close->setFlat(true);
    bt_close->setStyleSheet("QPushButton{border-image:url(:/image/softImage/system/close_2.png)}"
                            "QPushButton:hover{border-image:url(:/image/softImage/system/close_1.png)}"
                            "QPushButton:pressed{border-image:url(:/image/softImage/system/close_3.png)}");
    bt_close->setToolTip("关闭");
    bt_minize->setFlat(true);
    bt_minize->setStyleSheet("QPushButton{background:transparent}"
                             "QPushButton{border-image:url(:/image/softImage/system/minize_0.png)}"
                             "QPushButton:hover{border-image:url(:/image/softImage/system/minize_1.png)}"
                             "QPushButton:pressed{border-image:url(:/image/softImage/system/minize_3.png)}");
    bt_minize->setToolTip("最小化");
    bt_setting->setFlat(true);
    bt_setting->setStyleSheet("QPushButton{border-image:url(:/image/softImage/system/setting_0.png)}"
                              "QPushButton:hover{border-image:url(:/image/softImage/system/setting_1.png)}"
                              "QPushButton:pressed{border-image:url(:/image/softImage/system/setting_3.png)}");
    bt_setting->setToolTip("设置");
    bt_login->setFlat(true);

    bt_close->setGeometry(562,19,19,19);
    bt_minize->setGeometry(515,13,30,30);
    bt_setting->setGeometry(470,14,25,25);
    bt_login->setGeometry(16,9,38,38);

    lb_trueName = new QLabel(this);

    lb_trueName->setGeometry(62,24,100,25);
    lb_trueName->setFont(Tool::Font(18,true));


    setNoUser();
}

void TitleWidget::setNoUser()
{
    lb_trueName->setStyleSheet("QLabel{background:transparent;color:#A6A6A6;}"
                           "QLabel:hover{color:#FF1DF4}"
                           "QLabel:pressed{color:#E6FF13}");

    bt_login->setStyleSheet("QPushButton{border-image:url(:/image/softImage/system/login_0.png)}"
                            "QPushButton:hover{border-image:url(:/image/softImage/system/login_1.png)}"
                            "QPushButton:pressed{border-image:url(:/image/softImage/system/login_3.png)}");

    lb_trueName->setText("请登录");
    lb_trueName->setToolTip("");
    bt_login->setToolTip("请登录");


}

void TitleWidget::setUser(const User &user)
{
    QString sheet = "QPushButton{border-image:url(";
    if(!user.isVaild())
    {

        sheet = sheet+user.getHeadImagePath()+")}";
        bt_login->setStyleSheet(sheet+"QPushButton:hover{} QPushButton:pressed{}");
        return;
    }

    bt_login->setToolTip(user.getUserName()+" 权限:"+QString::number(user.getPermit()));
    lb_trueName->setText(user.getTrueName());

    if(user.getHeadImageProperty()<1||user.getHeadImageProperty()>IMAGECOUT)
    {
        bt_login->setStyleSheet("QPushButton{border-image:url(:/image/softImage/softIcon.png)}");
    }
    else
    {
        sheet +=user.getHeadImagePath() +")}";

        bt_login->setStyleSheet(sheet+"QPushButton:hover{} QPushButton:pressed{}");
    }
    if(user.getPermit()<3)
    {
        lb_trueName->setToolTip("普通用户");
    }
    else
    {
        lb_trueName->setToolTip("这里有一名管理员");
    }
}

void TitleWidget::SetTitleText(const QString &mes)
{
    lb_trueName->setText(mes);
}

void TitleWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        if(event->pos().x()<160)
        {
            emit rightButton(QPoint(20,52));
            return;
        }
        if(event->pos().x()>460)
        {
            return ;
        }
        emit rightButton(QPoint(event->pos().x()-20,52));
    }
    if(event->button()==Qt::LeftButton)
    {
        //62,24,100,25
        if(event->pos().x()>=62&&event->pos().y()>=24&&event->pos().x()<120&&event->pos().y()<=49)
        {
            emit rightButton(QPoint(20,52));
        }
    }
    event->ignore();
}



