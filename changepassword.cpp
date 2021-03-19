#include "changepassword.h"
#include "ui_changepassword.h"

ChangePassword::ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);

    setFixedSize(340,260);
    this->setWindowTitle("修改密码");
    this->setWindowIcon(QIcon(":/image/softImage/login_0.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    move(Tool::ScreenCenter(this->rect()));

    initData();
    initLayout();
    initConnect();
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::initData()
{
    m_user.init();
    drag_mousePressedFlag = false;
    drag_beginPoint = QPoint(0,0);
}

void ChangePassword::initLayout()
{
    bt_close = new QPushButton(this);
    bt_close->setGeometry(301,19,20,20);
    bt_close->setStyleSheet("QPushButton{border-image:url(:/image/softImage/system/close_2.png)}"
                            "QPushButton:hover{border-image:url(:/image/softImage/system/close_1.png)}"
                            "QPushButton:pressed{border-image:url(:/image/softImage/system/close_3.png)}");

    bt_change = new QPushButton(this);
    bt_change->setGeometry(30,210,180,30);
    bt_change->setText("确认修改");
    bt_change->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:13px;font-weight:bold;}"
                             "QPushButton:hover{background-color:#DF7DAF}"
                             "QPushButton:pressed{background-color:#F6B56C}");

    QRegExp zifu("[!-~]{15}");

    le_oldPassword = new QLineEdit(this);
    le_oldPassword->setGeometry(30,60,180,30);
    le_oldPassword->setEchoMode(QLineEdit::Password);
    le_oldPassword->setPlaceholderText("请输入旧密码");
    //le_oldPassword->setValidator(new QRegExpValidator(zifu,this));
    le_oldPassword->setStyleSheet("QLineEdit{background:#fff;color:#000;border: 1px solid #c6c6c6;border-radius: 4px; font-size:14px;font-weight:bold;}"
                                    "QLineEdit:hover{border: 2px solid #F00}"
                                    "QLineEdit:focus{border: 2px solid #F00;background:#FFC1C1;}");

    le_newPassword = new QLineEdit(this);
    le_newPassword->setGeometry(30,110,180,30);
    le_newPassword->setEchoMode(QLineEdit::Password);
    le_newPassword->setPlaceholderText("请输入新密码");
    //le_newPassword->setValidator(new QRegExpValidator(zifu,this));
    le_newPassword->setStyleSheet("QLineEdit{background:#fff;color:#000;border: 1px solid #c6c6c6;border-radius: 4px; font-size:14px;font-weight:bold;}"
                                    "QLineEdit:hover{border: 2px solid #F00}"
                                    "QLineEdit:focus{border: 2px solid #F00;background:#FFC1C1;}");

    le_correctPassword = new QLineEdit(this);
    le_correctPassword->setGeometry(30,160,180,30);
    le_correctPassword->setEchoMode(QLineEdit::Password);
    le_correctPassword->setPlaceholderText("再次输入新密码");
    //le_correctPassword->setValidator(new QRegExpValidator(zifu,this));
    le_correctPassword->setStyleSheet("QLineEdit{background:#fff;color:#000;border: 1px solid #c6c6c6;border-radius: 4px; font-size:14px;font-weight:bold;}"
                                    "QLineEdit:hover{border: 2px solid #F00}"
                                    "QLineEdit:focus{border: 2px solid #F00;background:#FFC1C1;}");

    lb_status_oldPassword = new QLabel(this);
    lb_status_oldPassword->setGeometry(215,60,110,30);
    lb_status_oldPassword->setStyleSheet("QLabel{background:transparent;color:#E0EEEE;font-size:13px;font-weight:bold;}");

    lb_status_newPassword = new QLabel(this);
    lb_status_newPassword->setGeometry(215,110,110,30);
    lb_status_oldPassword->setStyleSheet("QLabel{background:transparent;color:#E0EEEE;font-size:13px;font-weight:bold;}");

    lb_status_correctPassword = new QLabel(this);
    lb_status_correctPassword->setGeometry(215,160,110,30);
    lb_status_correctPassword->setStyleSheet("QLabel{background:transparent;color:#E0EEEE;font-size:13px;font-weight:bold;}");

    lb_image_oldPassword = new QLabel(this);
    lb_image_oldPassword->setGeometry(10,63,18,18);
    lb_image_oldPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/error.png)}");

    lb_image_newPassword = new QLabel(this);
    lb_image_newPassword->setGeometry(10,113,18,18);
    lb_image_newPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/error.png)}");

    lb_image_correctPassword = new QLabel(this);
    lb_image_correctPassword->setGeometry(10,163,18,18);
    lb_image_correctPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/error.png)}");

    bt_change->setDefault(true);
}

void ChangePassword::initConnect()
{

    connect(bt_close,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(le_oldPassword,SIGNAL(editingFinished()),this,SLOT(check_le_oldPassword()));
    connect(le_newPassword,SIGNAL(editingFinished()),this,SLOT(check_le_newPassword()));
    connect(le_correctPassword,SIGNAL(editingFinished()),this,SLOT(check_le_correctPassword()));
    connect(bt_change,SIGNAL(clicked(bool)),this,SLOT(slot_bt_change()));
    connect(le_oldPassword,SIGNAL(returnPressed()),this,SLOT(slot_bt_change()));
    connect(le_newPassword,SIGNAL(returnPressed()),this,SLOT(slot_bt_change()));
    connect(le_correctPassword,SIGNAL(returnPressed()),this,SLOT(slot_bt_change()));
}

void ChangePassword::setUser(const User &user)
{
    m_user = user;
    update();
}

void ChangePassword::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        drag_mousePressedFlag = true;
        drag_beginPoint = event->pos();
    }
}

void ChangePassword::mouseMoveEvent(QMouseEvent *event)
{
    if(drag_mousePressedFlag)
    {
        move(event->globalPos()-drag_beginPoint);
    }
}

void ChangePassword::mouseReleaseEvent(QMouseEvent *event)
{
    drag_mousePressedFlag = false;
    event->accept();
}

void ChangePassword::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/image/background_2.png"));
    painter.drawPixmap(30,18,30,30,QPixmap(m_user.getHeadImagePath(m_user.getHeadImageProperty())));

    painter.setPen(QColor(200,200,200));
    QFont font ("Microsoft YaHei",9,75);
    font.setUnderline(true);
    painter.setFont(font);

    painter.drawText(70,45,m_user.getTrueName());

    QColor color(200, 200, 200, 50);
    for(int i=0; i<4; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(4-i, 4-i, this->width()-(4-i)*2, this->height()-(4-i)*2);
        color.setAlpha(75+i*30);
        painter.setPen(color);
        painter.drawPath(path);
    }

    event->accept();
}

bool ChangePassword::check_le_oldPassword()
{
    if(m_user.getPassword()==le_oldPassword->text())
    {
        setYesOldPassword();
        lb_status_oldPassword->setText("旧密码输入正确");
        return true;
    }
    else
    {
        setNoOldPassword();
        lb_status_oldPassword->setText("旧密码输入错误");
        return false;
    }
}

bool ChangePassword::check_le_newPassword()
{
    if(le_newPassword->text().length()<6)
    {
        setNoNewPassword();
        lb_status_newPassword->setText("密码最少6位");
        return false;
    }

    if(!le_newPassword->text().contains(QRegExp("[!-~]")))
    {
        setNoNewPassword();
        lb_status_newPassword->setText("非法输入汉字空格");
        return false;
    }

    if(le_newPassword->text()==m_user.getPassword())
    {
        setNoNewPassword();
        lb_status_newPassword->setText("密码与旧密码相同");
        return false;
    }
    else
    {
        setYesNewPassword();
        lb_status_newPassword->setText("密码合法");
        return true;
    }
}

bool ChangePassword::check_le_correctPassword()
{
    if(le_newPassword->text().length()==0)
    {
        setNoCorrectPassword();
        lb_status_correctPassword->setText("未输入新密码");
        return false;
    }

    if(le_newPassword->text()==m_user.getPassword())
    {
        setNoCorrectPassword();
        lb_status_correctPassword->setText("密码与旧密码相同");
        return false;
    }
    if(le_newPassword->text()==le_correctPassword->text())
    {
        setYesCorrectPassword();
        lb_status_correctPassword->setText("密码输入一致");
        return true;
    }
    else
    {
        setNoCorrectPassword();
        lb_status_correctPassword->setText("密码输入不一致");
        return false;
    }
}

void ChangePassword::slot_bt_change()
{
    if(check_le_correctPassword()&&check_le_oldPassword()&&check_le_newPassword())
    {
        m_user.setNewPassword(le_newPassword->text());
//        PhpServer::getPhpServer()->RequestAlterPassword(m_user);
    }

}

void ChangePassword::slot_changePassword_server(int type)
{
//    if(PhpServer::getPhpServer()->getResult().toInt()==100)
//    {
//        TipWidget(this,"！！！","修改密码成功",11);
//        emit SignalToDeleteLogin();
//        close();
//        return;
//    }

//    switch(PhpServer::getPhpServer()->getReason().toInt())
//    {
//    case 404:
//        TipWidget(this,"无法连接服务器！","请检查网络状态",11);
//        break;
//    case 402:
//        TipWidget(this,"修改密码失败！","密码太短",11);
//        break;
//    default:
//        TipWidget(this,"error_"+QString::number(PhpServer::getPhpServer()->getResult().toInt())," 未知错误 ",11);
//        break;
//    }
//    PhpServer::getPhpServer()->setServerFree();
}

void ChangePassword::setYesOldPassword()
{
    lb_image_oldPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/success.png)}");
    lb_status_oldPassword->setStyleSheet("QLabel{background:transparent;color:#66CDAA;font-size:13px;font-weight:bold;}");
}

void ChangePassword::setYesNewPassword()
{
    lb_image_newPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/success.png)}");
    lb_status_newPassword->setStyleSheet("QLabel{background:transparent;color:#66CDAA;font-size:13px;font-weight:bold;}");
}

void ChangePassword::setYesCorrectPassword()
{
    lb_image_correctPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/success.png)}");
    lb_status_correctPassword->setStyleSheet("QLabel{background:transparent;color:#66CDAA;font-size:13px;font-weight:bold;}");
}

void ChangePassword::setNoOldPassword()
{
    lb_image_oldPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/error.png)}");
    lb_status_oldPassword->setStyleSheet("QLabel{background:transparent;color:#EE7600;font-size:13px;font-weight:bold;}");
}

void ChangePassword::setNoNewPassword()
{
    lb_image_newPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/error.png)}");
    lb_status_newPassword->setStyleSheet("QLabel{background:transparent;color:#EE7600;font-size:13px;font-weight:bold;}");
}

void ChangePassword::setNoCorrectPassword()
{
    lb_image_correctPassword->setStyleSheet("QLabel{background:transparent;border-image:url(:image/softImage/details/error.png)}");
    lb_status_correctPassword->setStyleSheet("QLabel{background:transparent;color:#EE7600;font-size:13px;font-weight:bold;}");
}
