#include "loginwidget.h"
#include "ui_loginwidget.h"

// 重载自定义对象的输入
QDataStream& operator <<(QDataStream &out,User &user)
{
    out<<user.getUserName()
      <<user.getPassword()
     <<user.getRemberPassword()
    <<user.getAutoLogin()
    <<user.getHeadImageProperty()
    <<user.getPermit()
    <<user.getLastTime()
    <<user.getCloseStyle()
    <<user.getSoftStyle()
    <<user.getUpdateStyle();
    return out;
}
// 重载自定义对象的输出
QDataStream& operator >>(QDataStream &in,User &user)
{
    QString userName;
    QString password;
    bool remberPassword;
    bool autoLogin;
    int headImageProperty;
    int permit;
    QDateTime lastTime;
    int closeStyle;
    int softStyle;
    int updateStyle;
    in>>userName
            >>password
            >>remberPassword
            >>autoLogin
            >>headImageProperty
            >>permit
            >>lastTime
            >>closeStyle
            >>softStyle
            >>updateStyle;
    user.initUser(userName,password,permit);
    user.setAutoLogin(autoLogin);
    user.setRemberPassword(remberPassword);
    user.setHeadImageProperty(headImageProperty);
    user.setLastTime(lastTime);
    user.setCloseStyle(closeStyle);
    user.setSoftStyle(softStyle);
    user.setUpdateStyle(updateStyle);

    return in;
}

LoginWidget::LoginWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setFixedSize(330,396);
    this->setWindowTitle("登陆");
    this->setWindowIcon(QIcon(":/image/softImage/system/login_0.png"));
    move(Tool::ScreenCenter(this->rect()));


    initData();
    initLayout();
    initConnect();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::initData()
{
    drag_mousePressedFlag = false;
    drag_beginPoint = QPoint(0,0);
    Login_user.init();
}
void LoginWidget::initLayout()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    lb_headImage = new QLabel(this);
    lb_userName = new QComboBox(this);
    lb_password = new QLineEdit(this);
    bt_login = new QPushButton(this);
    bt_forgetPassword = new QPushButton(this);
    bt_quickRegister = new QPushButton(this);
    bt_close = new QPushButton(this);
    bt_rememberPassword = new QCheckBox(this);
    bt_autoLogin = new QCheckBox(this);
    bt_deleteLogin = new QPushButton(this);
    progressBar = new QProgressBar(this);
    myTimer = new QTimer(this);

    lb_headImage->setGeometry(90,39,155,155);
    lb_userName->setGeometry(48,234,241,30);
    lb_password->setGeometry(48,272,241,30);
    bt_login->setGeometry(48,312,241,30);
    bt_forgetPassword->setGeometry(14,352,60,25);
    bt_quickRegister->setGeometry(256,352,60,25);
    bt_close->setGeometry(291,19,20,20);
    bt_rememberPassword->setGeometry(83,352,90,25);
    bt_autoLogin->setGeometry(173,352,90,25);
    progressBar->setGeometry(0,376,330,15);
    bt_deleteLogin->setGeometry(48,312,241,30);

    lb_userName->setFont(Tool::Font(18,true));
    lb_password->setFont(Tool::Font(16,true));
    bt_login->setFont(Tool::Font(14,true));
    bt_deleteLogin->setFont(Tool::Font(14,true));
    bt_forgetPassword->setFont(Tool::Font(14,true));
    bt_quickRegister->setFont(Tool::Font(14,true));
    bt_rememberPassword->setFont(Tool::Font(14,true));
    bt_autoLogin->setFont(Tool::Font(14,true));

    bt_login->setText("登陆");
    bt_deleteLogin->setText("取消登陆");
    bt_forgetPassword->setText("忘记密码");
    bt_quickRegister->setText("快速注册");
    bt_rememberPassword->setText("记住密码");
    bt_autoLogin->setText("自动登陆");
    lb_password->setPlaceholderText("密码");

    lb_userName->setEditable(true);
    m_model = new QStandardItemModel(this);
    lb_userName->setModel(m_model);
    lb_userName->setIconSize(QSize(30,30));


    lb_password->setEchoMode(QLineEdit::Password);

    QRegExp numLet("[_0-9a-zA-Z@.]{18}");
    QRegExp zifu("[!-~]{15}");
    lb_userName->setValidator(new QRegExpValidator(numLet,this));
    lb_password->setValidator(new QRegExpValidator(zifu,this));

    bt_login->setDefault(true);

    //lb_headImage->setStyleSheet("QLabel{background:color#A0A0A0}");
    lb_headImage->setScaledContents(true);
    QPixmap pixmap("://image/softImage//softIcon.png");
    pixmap.scaled(lb_headImage->size(), Qt::KeepAspectRatio);
    lb_headImage->setPixmap(pixmap);
    lb_userName->setStyleSheet("QComboBox{background:#F5F5F5;border:0px solid gray;border-radius:3px;padding:1px 2px 1px 2px;}"
                                                          "QComboBox::down-arrow{image:url(:/image/softImage/details/drow_arrow_0.png);"
                                                          "width:10px;"
                                                          "height:10px;}"
                                                          "QComboBox:hover{border: 1px solid gray;}"
                                                          "QComboBox::drop-down{"
                                                          "width: 20px;"
                                                          "background:#F5F5F5;"
                                                          "border-radius:3px;}");
    lb_userName->view()->setStyleSheet("QAbstractItemView{background:#FFF;}");
    lb_password->setStyleSheet("QLineEdit{font-size:13px;font-weight:bold;}");
    bt_login->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:13px;font-weight:bold;}"
                            "QPushButton:hover{background-color:#DF7DAF}"
                            "QPushButton:pressed{background-color:#F6B56C}");
    bt_deleteLogin->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:13px;font-weight:bold;}"
                            "QPushButton:hover{background-color:#DF7DAF}"
                            "QPushButton:pressed{background-color:#F6B56C}");
    bt_close->setStyleSheet("QPushButton{border-image:url(:/image/softImage/system/close_2.png)}"
                            "QPushButton:hover{border-image:url(:/image/softImage/system/close_1.png)}"
                            "QPushButton:pressed{border-image:url(:/image/softImage/system/close_3.png)}");
    bt_forgetPassword->setStyleSheet("QPushButton{background:transparent;color:#A6A6A6;font-size:12px;font-weight:bold;}"
                                     "QPushButton:hover{color:#DF7DAF}"
                                     "QPushButton:pressed{color:#E6FF13}");
    bt_quickRegister->setStyleSheet("QPushButton{background:transparent;color:#A6A6A6;font-size:12px;font-weight:bold;}"
                                    "QPushButton:hover{color:#DF7DAF}"
                                    "QPushButton:pressed{color:#E6FF13}");
    bt_rememberPassword->setStyleSheet("QCheckBox{background:transparent;color:#A6A6A6;font-size:12px;font-weight:bold;}"
                                    "QCehckBox:hover{color:#DF7DAF}"
                                    "QCheckBox:pressed{color:#E6FF13}");
    bt_autoLogin->setStyleSheet("QCheckBox{background:transparent;color:#A6A6A6;font-size:12px;font-weight:bold;}"
                                    "QCehckBox:hover{color:#DF7DAF}"
                                    "QCheckBox:pressed{color:#E6FF13}");
    progressBar->setStyleSheet("QProgressBar{"
                               "border:none;"
                               "color:white;"
                               "background-color:rgb(15,18,23);"
                               "text-align:center;}"
                               "QProgressBar::chunk{background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 red,stop:1 blue);}");   
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    progressBar->setValue(0);
    progressBar->hide();
    bt_deleteLogin->hide();
}
void LoginWidget::initConnect()
{
    connect(bt_close,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(bt_quickRegister,SIGNAL(clicked(bool)),this,SLOT(slot_quickRegister()));
    connect(bt_login,SIGNAL(clicked(bool)),this,SLOT(slot_login()));
    connect(bt_deleteLogin,SIGNAL(clicked(bool)),this,SLOT(slot_deleteLogin()));

    connect(myTimer,SIGNAL(timeout()),this,SLOT(slot_timerOut()));
    connect(lb_userName,SIGNAL(editTextChanged(QString)),this,SLOT(CurrentUserChangeEvent(QString)));
}

void LoginWidget::setUnLogin()
{
    //it can't find nothing to do
}
void LoginWidget::setLogin(const User &user)
{
    if(!user.isVaild())
    {
        setUser(Login_user);
    }
    else
    {
        setUser(user);
    }
    if(user.getAutoLogin()) slot_login();
    exec();

}
void LoginWidget::setUser(const User &user)
{
    loadComboBox();
    lb_userName->setCurrentIndex(lb_userName->findText(user.getUserName()));
    lb_password->setText(user.getPassword());
    bt_rememberPassword->setChecked(user.getRemberPassword());
    bt_autoLogin->setChecked(user.getAutoLogin());
    QPixmap pixmap(user.getHeadImagePath());
    pixmap.scaled(lb_headImage->size(), Qt::KeepAspectRatio);
    lb_headImage->setPixmap(pixmap);
    Login_user = user;

}

User LoginWidget::getUser() const
{
    return Login_user;
}

void LoginWidget::setServer(MyServer *server)
{
    m_myServer = server;
    connect(m_myServer,SIGNAL(sLogin(User)),this,SLOT(slot_login_succeed(User)));
    connect(m_myServer,SIGNAL(sError(QString)),this,SLOT(slot_login_fail(QString)));
}


//本地数据库服务接口--------------------------------------------------------
User LoginWidget::loadCurrentUser()
{
    User setting[LOCALSPACE];
    if(!getLocalDatabase(setting))
    {
        return User();
    }
    int find = -1;
    QDateTime lastTime;
    for(int i=0;i<LOCALSPACE;i++)
    {
        if(!setting[i].isVaild()) continue;

        if(setting[i].getAutoLogin()==true)
        {
            return setting[i];
        }

        if(setting[i].getLastTime()>lastTime)
        {
            find = i;
            lastTime = setting[i].getLastTime();
        }
    }

    if(find==-1)
    {
        return User();
    }
    return setting[find];
}

int LoginWidget::saveUserSetting(const User &user)
{
    if(user.getUserName() == "") return AVOID;
    User setting[LOCALSPACE];
    if(SUCCEED != LoginWidget::getLocalDatabase(setting))
    {
        //当第一次使用软件没有数据库的时候，需要初始化数据库
        if(!initLoginSetting())return FAIL;
        if(SUCCEED != getLocalDatabase(setting))
        {
            return FAIL;
        }
    }
    //初始化为0，如果找不到空间，就记录在0上
    bool find = false;
    for(int i=0;i<LOCALSPACE;i++)
    {
        if(user.getAutoLogin()==true)  setting[i].setAutoLogin(false);
        if((setting[i].getUserName()==""||setting[i].getUserName()==user.getUserName())&&!find)
        {
            setting[i] = user;
            find = true;
        }
    }

    if(!find) setting[0] = user;

    if(!LoginWidget::setLocalDatabase(setting)) return FAIL;
    return SUCCEED;
}

User LoginWidget::loadUserSetting(const QString &userName)
{
    if(userName=="") return User();

    User setting[LOCALSPACE];
    if(SUCCEED!=getLocalDatabase(setting))
    {
        return User();
    }
    for(int i=0;i<30;i++)
    {
        if(userName==setting[i].getUserName())
        {
            return setting[i];
            break;
        }
    }
    return User();
}
int LoginWidget::setLocalDatabase(User setting[])
{
    QFile writeDatabaseFile(LOCALLOGINSETTINGDATABASE);
    //打开本地数据库
    if(!writeDatabaseFile.open(QIODevice::WriteOnly))
    {
        return FAIL;
    }
    writeDatabaseFile.resize(0);
    QDataStream out(&writeDatabaseFile);
    out.setVersion(QDataStream::Qt_5_6);

    for(int i=0;i<LOCALSPACE;i++) out << setting[i];
    return SUCCEED;
}
int LoginWidget::getLocalDatabase(User setting[])
{
    QFile databaseFile(LOCALLOGINSETTINGDATABASE);
    if(!databaseFile.open(QIODevice::ReadOnly))
    {
        return FAIL;
    }
    QDataStream in(&databaseFile);
    in.setVersion(QDataStream::Qt_5_6);

    for(int i=0;i<LOCALSPACE;i++)
    {
        in>>setting[i];
    }
    return SUCCEED;
}
//清空本地记录的所有信息
int LoginWidget::initLoginSetting()
{
    QFile databaseFile(LOCALLOGINSETTINGDATABASE);
    if(!databaseFile.open(QIODevice::WriteOnly)) return FAIL;
    databaseFile.resize(0);
    databaseFile.close();
    User user[LOCALSPACE];
    user[0].initUser("LocalAdmin","",1);
    user[0].setHeadImageProperty(rand()%IMAGECOUT);
    if(!setLocalDatabase(user)) return FAIL;

    return SUCCEED;
}
//清除所有用户的本地记录，保留用户名和头像
int LoginWidget::clearLoginSetting()
{
    User setting[LOCALSPACE];
    if(!getLocalDatabase(setting)) return FAIL;
    for(int i=0;i<LOCALSPACE;i++)
    {
        setting[i].setPassword("");
        setting[i].setAutoLogin(false);
        setting[i].setRemberPassword(false);
    }

    if(!setLocalDatabase(setting)) return FAIL;
    return SUCCEED;
}
//清除指定用户的本地记录，保留用户名和头像
int LoginWidget::clearUserLoginSetting(const User &user)
{
    User setting[LOCALSPACE];
    if(!getLocalDatabase(setting)) return FAIL;
    for(int i=0;i<LOCALSPACE;i++)
    {
        if(setting[i].getUserName()==user.getUserName())
        {
            setting[i].setPassword("");
            setting[i].setAutoLogin(false);
            setting[i].setRemberPassword(false);
        }
    }

    if(!setLocalDatabase(setting)) return FAIL;

    return SUCCEED;
}

void LoginWidget::loadComboBox()
{
    User setting[LOCALSPACE];
    if(!LoginWidget::getLocalDatabase(setting)) return;
    lb_userName->clear();
    for(int i=0;i<LOCALSPACE;i++)
    {
        if(setting[i].isVaild())
        {
            lb_userName->addItem(QIcon(setting[i].getHeadImagePath()),setting[i].getUserName());
        }
    }
}

//类基本事件函数
void LoginWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        drag_mousePressedFlag = true;
        drag_beginPoint = event->pos();
    }
}
void LoginWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(drag_mousePressedFlag)
    {
        move(event->globalPos()-drag_beginPoint);
    }
}
void LoginWidget::mouseReleaseEvent(QMouseEvent *event)
{
    drag_mousePressedFlag = false;
    event->accept();
}
void LoginWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/image/background_2.png"));

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

void LoginWidget::LoginUpdateUesr()
{
//    Login_user = PhpServer::getPhpServer()->getUser();

    User setting = LoginWidget::loadUserSetting(Login_user.getUserName());

    Login_user.setCloseStyle(setting.getCloseStyle());
    Login_user.setUpdateStyle(setting.getUpdateStyle());
    Login_user.setAutoLogin(bt_autoLogin->isChecked());
    Login_user.setRemberPassword(bt_rememberPassword->isChecked());

    if(Login_user.getRemberPassword()||Login_user.getAutoLogin())
    {
        LoginWidget::saveUserSetting(Login_user);
    }
    else
    {
        LoginWidget::clearUserLoginSetting(Login_user);
    }

}
void LoginWidget::slot_login()
{
    this->slot_loginView();
    if(lb_userName->currentText().trimmed()=="LocalAdmin")
    {
        slot_deleteLogin();
        TipWidget(this,"提示信息！","暂不支持本地用户登录",11);
    }
    else if (lb_userName->currentText().trimmed() == "" || lb_password->text().trimmed() == "")
    {
        slot_deleteLogin();
        TipWidget(this,"提示信息！","账号或密码不能为空",11);
    }
    else
    {
        User user;
        user.setUserName(lb_userName->currentText().trimmed());
        user.setPassword(lb_password->text().trimmed());
        m_myServer->login(user);      
    }
}
void LoginWidget::slot_deleteLogin()
{
    myTimer->stop();
    progressBar->setValue(0);
    bt_deleteLogin->hide();
    progressBar->hide();
    lb_password->show();
    lb_userName->show();
    bt_login->show();
    bt_forgetPassword->show();
    bt_quickRegister->show();
    bt_rememberPassword->show();
    bt_autoLogin->show();
}


void LoginWidget::slot_timerOut()
{
    if(progressBar->value()==LOGINTIME)
    {
        slot_deleteLogin();
        //放弃数据并提示
        TipWidget(this,"登录失败！","请检查网络状态",11);
        return;
    }
    progressBar->setValue(progressBar->value()+1);
}

void LoginWidget::slot_forgetPassword()
{

}
void LoginWidget::slot_quickRegister()
{
    emit SignalToRegister();
    close();
}

void LoginWidget::slot_login_succeed(const User &user)
{
    LoginUpdateUesr();
    close();
}

void LoginWidget::slot_login_fail(const QString message)
{
    qDebug()<<"响应失败";
    slot_deleteLogin();
    TipWidget(this,"提示",message,11);
}

void LoginWidget::CurrentUserChangeEvent(QString userName)
{
    if(userName=="")
    {
        lb_userName->setCurrentIndex(-1);
        QPixmap pixmap(User::getHeadImagePath(0));
        pixmap.scaled(lb_headImage->size(), Qt::KeepAspectRatio);
        lb_headImage->setPixmap(pixmap);
    }
    if(lb_userName->findText(userName)==-1)
    {
        lb_password->clear();
    }
    else
    {
        User user = LoginWidget::loadUserSetting(userName);
        if(user.isVaild())
        {
            lb_password->setText(user.getPassword());
            QPixmap pixmap(user.getHeadImagePath());
            pixmap.scaled(lb_headImage->size(), Qt::KeepAspectRatio);
            lb_headImage->setPixmap(pixmap);
            lb_userName->setCurrentIndex(lb_userName->findText(userName));
        }
    }
}

void LoginWidget::slot_loginView()
{
    lb_password->hide();
    lb_userName->hide();
    bt_login->hide();
    bt_forgetPassword->hide();
    bt_quickRegister->hide();
    bt_rememberPassword->hide();
    bt_autoLogin->hide();
    myTimer->start(1);
    bt_deleteLogin->show();
    progressBar->show();
}
