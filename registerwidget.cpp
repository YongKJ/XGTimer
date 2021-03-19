#include "registerwidget.h"
#include "ui_registerwidget.h"

RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    setFixedSize(600,292);

    initData();
    initLayout();
    initConnect();
    this->setMouseTracking(true);
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::initData()
{
}

void RegisterWidget::initLayout()
{

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    le_userName = new QLineEdit(this);
    le_trueName = new QLineEdit(this);
    le_password = new QLineEdit(this);
    le_againPassword = new QLineEdit(this);
    le_phoneNumber = new QLineEdit(this);
    chb_male = new QCheckBox(this);
    chb_female = new QCheckBox(this);
    chb_protocol = new QCheckBox(this);
    bt_register = new QPushButton(this);
    bg_sex = new QButtonGroup(this);
    tb_protocol = new QTextBrowser(this);

    le_userName->setGeometry(32+30,10,268,35);
    le_trueName->setGeometry(32+30,45,268,35);
    le_password->setGeometry(32+30,80,268,35);
    le_againPassword->setGeometry(32+30,115,268,35);
    le_phoneNumber->setGeometry(32+30,150,268,35);
    chb_male->setGeometry(110+32,190,50,20);
    chb_female->setGeometry(170+32,190,50,20);
    chb_protocol->setGeometry(120+32,220,100,20);
    tb_protocol->setGeometry(340,10,250,250);
    bt_register->setGeometry(32+30,height()-45,268,35);

    le_userName->setPlaceholderText("用户名");
    le_trueName->setPlaceholderText("真实姓名");
    le_password->setPlaceholderText("密码");
    le_againPassword->setPlaceholderText("再次确认密码");
    le_phoneNumber->setPlaceholderText("联系方式");
    chb_male->setText("男");
    chb_female->setText("女");
    chb_protocol->setText("注册协议");
    bt_register->setText("注册");

    le_password->setEchoMode(QLineEdit::Password);
    le_againPassword->setEchoMode(QLineEdit::Password);


    // 输入限制
    QRegExp num("[0-9]{11}");  // 正则表达式
    QRegExpValidator *numReg = new QRegExpValidator(num,this);
    le_phoneNumber->setValidator(numReg);

    QRegExp numLet("[0-9a-zA-Z@._]{18}");
    QRegExpValidator *numLetReg = new QRegExpValidator(numLet,this);
    le_userName->setValidator(numLetReg);

    QRegExp zifu("[!-~]{15}");
    QRegExpValidator *zifuReg = new QRegExpValidator(zifu,this);
    le_password->setValidator(zifuReg);
    le_againPassword->setValidator(zifuReg);

    QRegExp Hanzi1("[\u4e00-\u9fa5]{2,4}");
    QRegExpValidator *Hanzi1Reg = new QRegExpValidator(Hanzi1,this);
    le_trueName->setValidator(Hanzi1Reg);

    QRegExp Hanzi2("[\u4e00-\u9fa5]{48}");
    QRegExpValidator *Hanzi2Reg = new QRegExpValidator(Hanzi2,this);


    le_userName->setStyleSheet("QLineEdit{border:1px;background:transparent;color:#ffffff;}"
                               "QLineEdit:hover{background:non-transparent;}");
    le_trueName->setStyleSheet("QLineEdit{border:1px;background:transparent;color:#ffffff;}"
                               "QLineEdit:hover{background:non-transparent;}");
    le_password->setStyleSheet("QLineEdit{border:1px;background:transparent;color:#ffffff;}"
                               "QLineEdit:hover{background:non-transparent;}");
    le_againPassword->setStyleSheet("QLineEdit{border:1px;background:transparent;color:#ffffff;}"
                                    "QLineEdit:hover{background:non-transparent;}");
    le_phoneNumber->setStyleSheet("QLineEdit{border:1px;background:transparent;color:#ffffff;}"
                                  "QLineEdit:hover{background:non-transparent;}");

    tb_protocol->setStyleSheet("QTextBrowser{border:none;color:#FFFFFF}");

    chb_male->setStyleSheet("QCheckBox{background:transparent;color:#a6a6a6;font-size:15px;}");
    chb_female->setStyleSheet("QCheckBox{background:transparent;color:#a6a6a6;font-size:15px;}");
    chb_protocol->setStyleSheet("QCheckBox{background:transparent;color:#ffff00;font-size:12px;}");


    bt_register->setStyleSheet("QPushButton{background:transparent;background-color:rgb(212,48,48);color:#FFFFFF;font-size:16px;font-weight:bold;}"
                               "QPushButton:hover{background-color:rgb(233,164,255)}"
                               "QPushButton:pressed{background-color:#F6B56C}");
    bt_register->setFocus();
    bt_register->setDefault(true);

    bg_sex->addButton(chb_male);
    bg_sex->addButton(chb_female);

    chb_male->setChecked(true);

    tb_protocol->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tb_protocol->setFont(Tool::Font(15,false));
    tb_protocol->hide();
}

void RegisterWidget::initConnect()
{
    connect(chb_protocol,SIGNAL(clicked(bool)),this,SLOT(slot_protocol()));

    connect(bt_register,SIGNAL(clicked(bool)),this,SLOT(slot_check()));
}

void RegisterWidget::SetServer(MyServer *server)
{
    m_myServer = server;
}

void RegisterWidget::closeEvent(QCloseEvent *event)
{
    SignalToCloseRegister();
    event->accept();
}

void RegisterWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::gray);
    painter.setPen(pen);
    painter.drawLine(le_userName->pos().x(),le_userName->pos().y()+le_userName->height(),le_userName->width()+32+30,le_userName->height()+10);
    painter.drawLine(le_trueName->pos().x(),le_trueName->pos().y()+le_trueName->height(),le_trueName->width()+32+30,le_trueName->height()+45);
    painter.drawLine(le_password->pos().x(),le_password->pos().y()+le_password->height(),le_password->width()+32+30,le_userName->height()+80);
    painter.drawLine(le_againPassword->pos().x(),le_againPassword->pos().y()+le_againPassword->height(),le_againPassword->width()+32+30,le_againPassword->height()+115);
    painter.drawLine(le_phoneNumber->pos().x(),le_phoneNumber->pos().y()+le_phoneNumber->height(),le_phoneNumber->width()+32+30,le_phoneNumber->height()+150);

    event->accept();
}

void RegisterWidget::resetLineEditText()
{
    le_trueName->clear();
    le_userName->clear();
    le_password->clear();
    le_againPassword->clear();
    le_phoneNumber->clear();
}

void RegisterWidget::slot_check()
{
    if (le_userName->text() == NULL || le_trueName->text() == NULL || le_password->text() == NULL || le_againPassword->text() == NULL || le_phoneNumber->text() == NULL)
    {
        TipWidget(this,"信息缺失！","必填信息未填完整",11);
        return;
    }
    else
    {
        if (le_againPassword->text().trimmed() != le_password->text().trimmed())
        {
            TipWidget(this,"确认密码！","两次密码不一致",11);
            le_againPassword->clear();
            le_againPassword->setFocus();
            return;
        }
        if (le_phoneNumber->text().length() != 6 && le_phoneNumber->text().length() != 11)
        {qDebug()<<"le_phoneNumber->text().length()"<<le_phoneNumber->text().length();
            TipWidget(this,"联系方式有误！","输入手机号码或校园短号",11);
            le_phoneNumber->setFocus();
            return;
        }
    }

    if (chb_protocol->isChecked() == false)
    {
        TipWidget(this,"协议未确认！","请勾选注册协议",11);
        return;
    }

    User user;
    user.initUser(le_userName->text().trimmed(),le_password->text().trimmed());
    user.setTrueName(le_trueName->text().trimmed());
    user.setNickName("未填写网名");
    user.setPhoneNumber(le_phoneNumber->text().trimmed());
    m_myServer->userRegister(user);
}

void RegisterWidget::Server_register_slot(const QString &status, const QString &message)
{
    if(status=="200")
    {
        TipWidget(this,"注册成功！!","欢迎使用计时器...",11);
    }
    else
    {
        TipWidget(this,"失败!",message,11);
    }
}

void RegisterWidget::slot_protocol()
{
//    if (chb_protocol->isChecked())
//    {
//        QFile file("registration protocol.txt");
//        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        {
//            //不能打开文件
//            return;
//        }

//        tb_protocol->setPlainText(QString(file.readAll()));//显示文件内容

//        file.close();

//        tb_protocol->show();
//    }
//    else
//    {
//        tb_protocol->close();
//    }
}
