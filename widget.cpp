#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(600,396);
    this->setWindowTitle("计时器");
    this->setWindowIcon(QIcon(":/image/softImage/softIcon.png"));

    initData();
    initLayout();
    initConnect();

    Login_autoLoginEvent();
}
Widget::~Widget()
{
    delete ui;
}

void Widget::initLayout()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    lb_version = new QLabel(this);
    lb_version->setText(Tool::getVersionText());
    lb_version->setGeometry(520,315,80,20);

    lb_version->setStyleSheet("QLabel{background:transparent;color:#FF34B3;font-size:16px;font-weight:bold;font-family:FZLTHJW}"
                              "QLabel:hover{color:#FFFF00;font-size:18px;}");
    m_statusLabel[0] = new StatusLabel(this);
    m_statusLabel[1] = new StatusLabel(this);
    m_statusLabel[2] = new StatusLabel(this);
    m_statusLabel[1]->setGeometry(20,295,200,20);
    m_statusLabel[2]->setGeometry(20,320,200,20);
    m_statusLabel[0]->setGeometry(20,270,200,20);

    m_statusLabel[0]->setStyleSheet("QLabel{background:transparent;color:#FF34B3;font-size:14px;font-weight:bold;font-family:FZLTHJW}");
    m_statusLabel[1]->setStyleSheet("QLabel{background:transparent;color:#FF34B3;font-size:14px;font-weight:bold;font-family:FZLTHJW}");
    m_statusLabel[2]->setStyleSheet("QLabel{background:transparent;color:#FF34B3;font-size:14px;font-weight:bold;font-family:FZLTHJW}");

    trayMenu = new QMenu(this);
    trayMenu->setStyleSheet("QMenu{background:#cfcfcf}");
    m_timer = new QTimer(this);

    titleWidget = new TitleWidget(this);
    bottomWidget = new BottomWidget(this);
    settingWidget = new SettingWidget(this);
    userWidget = new UserWidget(this);
    aboutWidget = new AboutWidget(this);
    registerWidget = new RegisterWidget(this);

    mainWidget = new MainWidget(this);
    showWidget = new ShowWidget(this);
    personWidget = new PersonWidget(this);
    memberWidget = new MenberWidget(this);

    vLayoutMain = new QVBoxLayout;

    vLayoutMain->addWidget(titleWidget);
    vLayoutMain->addWidget(mainWidget);
    vLayoutMain->addWidget(showWidget);
    vLayoutMain->addWidget(personWidget);
    vLayoutMain->addWidget(memberWidget);

    vLayoutMain->addWidget(settingWidget);
    vLayoutMain->addWidget(userWidget);
    vLayoutMain->addWidget(aboutWidget);
    vLayoutMain->addWidget(registerWidget);

    vLayoutMain->addWidget(bottomWidget);

    vLayoutMain->setAlignment(titleWidget,Qt::AlignCenter|Qt::AlignTop);
    vLayoutMain->setAlignment(mainWidget,Qt::AlignCenter);
    vLayoutMain->setAlignment(showWidget,Qt::AlignCenter);
    vLayoutMain->setAlignment(personWidget,Qt::AlignCenter);
    vLayoutMain->setAlignment(memberWidget,Qt::AlignCenter);

    vLayoutMain->setAlignment(settingWidget,Qt::AlignCenter);
    vLayoutMain->setAlignment(userWidget,Qt::AlignCenter);
    vLayoutMain->setAlignment(aboutWidget,Qt::AlignCenter);
    vLayoutMain->setAlignment(registerWidget,Qt::AlignCenter);

    vLayoutMain->setAlignment(bottomWidget,Qt::AlignCenter|Qt::AlignBottom);

    vLayoutMain->setSpacing(0);
    vLayoutMain->setContentsMargins(0,0,0,0);

    showWidget->hide();
    personWidget->hide();
    memberWidget->hide();
    registerWidget->hide();
    settingWidget->hide();
    userWidget->hide();
    aboutWidget->hide();

    bottomWidget->setPushButtonFocus(bottomWidget->bt_main);
    this->setLayout(vLayoutMain);

    trayWidget = new QSystemTrayIcon();
    trayWidget->setIcon(QIcon(":image//softImage//softIcon.png"));

    trayWidget->setToolTip("信工之星 计时器");

    trayWidget->show();
    trayWidget->setContextMenu(trayMenu);

    im_tool = new ImageTool(0,1);
    ShowTrayMenu();
    ShowTrayMenu();
}
void Widget::initData()
{
    drag_mousePressedFlag = false;
    drag_beginPoint = QPoint(0,0);

    page_currentFlag = MAIN;

    Login_vaild = false;
    cycle_updateUserIntervalStatis = 0;
    cycle_updateServerIntervalStatis = 0;
    m_internet = true;
    m_myServer = new MyServer();
    b_alreadyGotStudioMac = false;
    b_isTimer = true;

}
void Widget::initConnect()
{
    connect(m_timer,SIGNAL(timeout()),this,SLOT(Timing_slot()));

    connect(titleWidget->bt_login,SIGNAL(clicked(bool)),this,SLOT(show_loginWidget_slot()));
    connect(titleWidget->bt_close,SIGNAL(clicked(bool)),this,SLOT(show_trayWidget_slot()));
    connect(titleWidget->bt_minize,SIGNAL(clicked(bool)),this,SLOT(minimize_XGTimerWidget_slot()));
    connect(titleWidget->bt_setting,SIGNAL(clicked(bool)),this,SLOT(show_settingWidget_slot()));
    connect(titleWidget,SIGNAL(rightButton(QPoint)),this,SLOT(ShowMenu(QPoint)));

    connect(bottomWidget->bt_main,SIGNAL(clicked(bool)),this,SLOT(show_mainWidget_slot()));
    connect(bottomWidget->bt_show,SIGNAL(clicked(bool)),this,SLOT(show_showWidget_slot()));
    connect(bottomWidget->bt_person,SIGNAL(clicked(bool)),this,SLOT(show_personWidget_slot()));
    connect(bottomWidget->bt_member,SIGNAL(clicked(bool)),this,SLOT(show_memberWidget_slot()));
    connect(bottomWidget->bt_about,SIGNAL(clicked(bool)),this,SLOT(show_aboutWidget_slot()));

    connect(trayWidget,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayEvent(QSystemTrayIcon::ActivationReason)));
    connect(trayWidget,SIGNAL(messageClicked()),this,SLOT(show_XGTimerWidget_slot()));

    connect(settingWidget,SIGNAL(SignalToSettingUpdate(User)),this,SLOT(Update_UserSetting(User)));
    connect(userWidget,SIGNAL(SignalToSwitchTool(int)),this,SLOT(SwitchImageTool(int)));
    connect(userWidget,SIGNAL(SignalToDeleteUser()),this,SLOT(Login_setUnLoginUser()));
    connect(im_tool,SIGNAL(SIGNALToChangeImage(int)),userWidget,SLOT(ToolChangeImage(int)));

    connect(m_myServer,SIGNAL(sLogin(User)),this,SLOT(Login_setLoginUser(User)));
    connect(m_myServer,SIGNAL(sStatistic(StatisticUser)),this,SLOT(Server_statistic_slot(StatisticUser)));
    connect(m_myServer,SIGNAL(sUpdate(QString)),this,SLOT(Server_updateMessage_slot(QString)));
    connect(m_myServer,SIGNAL(sUpdateUser(User)),this,SLOT(Server_updateUser_slot(User)));
    connect(m_myServer,SIGNAL(sRegister(QString,QString)),registerWidget,SLOT(Server_register_slot(QString,QString)));
    connect(m_myServer,SIGNAL(sMac(QList<QString>)),this,SLOT(updateMac(QList<QString>)));
    connect(m_myServer,SIGNAL(sVersion(QString,QString)),this,SLOT(Server_updateAPP_slot(QString,QString)));
}

void Widget::setManager(QNetworkAccessManager *manager)
{

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        drag_mousePressedFlag = true;
        drag_beginPoint = event->pos();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(drag_mousePressedFlag)
    {


        move(event->globalPos()-drag_beginPoint);
        im_tool->setMove(QRect(pos(),size()));
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    drag_mousePressedFlag = false;
    event->accept();
}

void Widget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.drawPixmap(0,0,width(),height(),QPixmap(":/image/Background.png"));
   QPen pen(Qt::red,2,Qt::SolidLine);

   //界面红色分割线
   painter.setPen(pen);
   painter.drawLine(0,53,600,53);
   painter.drawLine(0,343,600,343);
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
void Widget::trayEvent(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
            this->show();
            break;
        case QSystemTrayIcon::DoubleClick:
            if(Login_vaild)
            {
                ShowSystemMessage("你今天已经在线了"+QString::number(Login_currentUser.getTodayTime()/60)+" 分钟",
                                  "本周在线时间:"+Login_currentUser.getWeekTimeString());
                Update_UserTimer();
            }
            else
            {
                ShowSystemMessage("用户 未登录！","计时器版本号: "+Tool::getVersionText());
            }

            break;
        default:
            break;
    }
}

//四大主要页面槽--------------------------------------------------------------------

void Widget::show_mainWidget_slot()
{
    if(page_currentFlag==MAIN) return;
    page_currentFlag = MAIN;

    UpdatePage(page_currentFlag);
}

void Widget::show_showWidget_slot()
{
    if(page_currentFlag==SHOW) return;
    page_currentFlag = SHOW;

    UpdatePage(page_currentFlag);
}

void Widget::show_personWidget_slot()
{
    if(page_currentFlag==PERSON) return;
    page_currentFlag = PERSON;

    UpdatePage(page_currentFlag);
}
void Widget::show_memberWidget_slot()
{
    if(page_currentFlag==MEMBER) return;
    page_currentFlag = MEMBER;

    if(Login_currentUser.isVaild())
    {
        m_myServer->requestStatistic(Login_currentUser);
    }
    else
    {

    }


    UpdatePage(page_currentFlag);
}

//小型附加页面槽--------------------------------------------------------------------
void Widget::show_loginWidget_slot()
{
    if(page_currentFlag==REGISTER) show_mainWidget_slot();
    //展示头像
    if(Login_vaild){
        ShowHeadImage();
        return;
    }
    //实施登录
    Login_autoLoginEvent(AVOID);
}
void Widget::show_userWidget_slot()
{
    if(page_currentFlag==USER||!Login_vaild)return;
    page_currentFlag=USER;
    UpdatePage(page_currentFlag);
}
void Widget::show_aboutWidget_slot()
{
    if(page_currentFlag == ABOUT) return;
    page_currentFlag = ABOUT;
    UpdatePage(page_currentFlag);
}
void Widget::show_settingWidget_slot()
{
    if(page_currentFlag==SETTING) return;
    page_currentFlag = SETTING;

    settingWidget->setUser(Login_currentUser);

    UpdatePage(page_currentFlag);
}
void Widget::show_registerWidget_slot()
{
    if(page_currentFlag==REGISTER||Login_vaild) return;
    page_currentFlag = REGISTER;

    UpdatePage(page_currentFlag);
}

void Widget::show_trayWidget_slot()
{
    CloseImageTool();
    if(trayWidget->isVisible()&&Login_currentUser.getCloseStyle()==1)
    {
        hide();
    }
    else
    {
        close();
    }
}
void Widget::show_XGTimerWidget_slot()
{
    this->setWindowState(Qt::WindowActive);
    this->show();
}
void Widget::minimize_XGTimerWidget_slot()
{
    CloseImageTool();
    showMinimized();
}

void Widget::UpdatePage(const int &type)
{
    mainWidget->close();
    showWidget->close();
    personWidget->close();
    memberWidget->close();

    registerWidget->close();
    userWidget->close();
    aboutWidget->close();
    settingWidget->close();
    CloseImageTool();

    bottomWidget->setPushButtonUnfocus(bottomWidget->bt_main);
    bottomWidget->setPushButtonUnfocus(bottomWidget->bt_show);
    bottomWidget->setPushButtonUnfocus(bottomWidget->bt_member);
    bottomWidget->setPushButtonUnfocus(bottomWidget->bt_person);

    if(Login_vaild)
    {
        titleWidget->setUser(Login_currentUser);
        userWidget->setUser(Login_currentUser);
        showWidget->setUser(Login_currentUser);
        personWidget->setUser(Login_currentUser);
    }
    else
    {
        titleWidget->setNoUser();
    }

    switch(type)
    {
    case MAIN:
        mainWidget->show();
        bottomWidget->setPushButtonFocus(bottomWidget->bt_main);
        break;
    case SHOW:
        showWidget->show();
        bottomWidget->setPushButtonFocus(bottomWidget->bt_show);
        break;
    case PERSON:
        personWidget->show();
        bottomWidget->setPushButtonFocus(bottomWidget->bt_person);
        break;
    case MEMBER:
        memberWidget->show();
        bottomWidget->setPushButtonFocus(bottomWidget->bt_member);
        break;
    case REGISTER:
        registerWidget->show();
        registerWidget->SetServer(m_myServer);

        titleWidget->SetTitleText("正在注册...");
        break;
    case SETTING:
        settingWidget->show();
        titleWidget->SetTitleText("正在设置...");
        break;
    case ABOUT:
        aboutWidget->show();
        titleWidget->SetTitleText("关于计时器...");
        break;
    case USER:
        userWidget->show();
        titleWidget->SetTitleText("用户信息...");
        userWidget->setServer(m_myServer);
        break;
    default:
        break;
    }

}

//关于登录：登录方法接口
void Widget::Login_setLoginUser(User user)
{
    updateLocalMAC();
    Login_currentUser = user;
    User setting = LoginWidget::loadUserSetting(user.getUserName());
    user.setCloseStyle(setting.getCloseStyle());
    user.setUpdateStyle(setting.getUpdateStyle());
    titleWidget->setUser(user);
    mainWidget->setUser(user);
    showWidget->setUser(user);
    personWidget->setUser(user);
    Login_vaild = true;   
    ShowSystemMessage("欢迎 使用信工之星 计时器","本周在线时间："+Login_currentUser.getWeekTimeString());
    Timing_start_slot();
    ShowTrayMenu();
    show_mainWidget_slot();
    ShowStatusMessage(user.getMotto(),5000);

    //获取工作室的mac地址
    m_myServer->requestMac();


}
void Widget::Login_setUnLoginUser()
{
    Login_vaild = false;
    Timing_stop_slot();
    cycle_updateUserIntervalStatis = 0;
    cycle_updateServerIntervalStatis = 0;

    Login_currentUser.init();

    TipWidget(this,"提示","已注销用户",11);

    titleWidget->setNoUser();
    mainWidget->setNoUser();
    showWidget->setNoUser();
    personWidget->setNoUser();
    ShowTrayMenu();
    show_mainWidget_slot();

    User user = LoginWidget::loadUserSetting("LocalAdmin");
    Login_currentUser.setCloseStyle(user.getCloseStyle());
    Login_currentUser.setUpdateStyle(user.getUpdateStyle());
}
void Widget::Login_autoLoginEvent(int type, User user)
{
    //准备登陆页面
    LoginWidget *loginWidget = new LoginWidget();

    loginWidget->setServer(m_myServer);

    connect(loginWidget,SIGNAL(SignalToRegister()),this,SLOT(show_registerWidget_slot()));
    connect(loginWidget,SIGNAL(SignalToUpdateAPP(QString,QString)),this,SLOT(updateAPP(QString,QString)));
    user = LoginWidget::loadCurrentUser();
    switch(type)
    {
    case SUCCEED:
        loginWidget->setLogin(user);
        break;
    case AVOID:
        loginWidget->setUser(user);
        loginWidget->exec();
        break;
    default:
        break;
    }
    delete loginWidget;
}

void Widget::Update_UserTimer()
{
    if(cycle_updateServerIntervalStatis<=LEAST_UPDATETIME)
    {
        ShowStatusMessage("请勿频繁更新!");
        return;
    }

    //更新数据的时间间隔重置
    cycle_updateServerIntervalStatis = 0;
    m_myServer->updateTime(Login_currentUser);
}

void Widget::Update_UserSetting(const User &user)
{
    Login_currentUser.setCloseStyle(user.getCloseStyle());
    Login_currentUser.setUpdateStyle(user.getUpdateStyle());
    Login_currentUser.setMember(user.getMember());
    User tempUser;
    if(!Login_vaild)
    {
        tempUser = LoginWidget::loadUserSetting("LocalAdmin");
        tempUser.setCloseStyle(user.getCloseStyle());
        tempUser.setUpdateStyle(user.getUpdateStyle());
    }
    else
    {
        tempUser = Login_currentUser;
    }
    if(LoginWidget::saveUserSetting(tempUser)==SUCCEED)
    {
        ShowSystemMessage("计时器设置 成功！","日志时间："+QTime::currentTime().toString());
    }
    else
    {
        ShowSystemMessage("计时器设置 失败!","未知原因...\n已上传错误到数据库");
    }
}

void Widget::Update_App()
{
    m_myServer->requestVersion();
}

void Widget::Server_updateMessage_slot(const QString &message)
{
    ShowStatusMessage(message);
}

void Widget::Server_updateUser_slot(const User &user)
{
   ShowStatusMessage("个人信息更新成功...");
   Login_currentUser.setUserMessage(user);
   UpdateCurrentUserFromUserWidget();
   //更新本地数据库信息
   LoginWidget::saveUserSetting(Login_currentUser);
   show_mainWidget_slot();
   ShowSystemMessage("个人信息更新 成功","日志时间："+QTime::currentTime().toString());

}

void Widget::Server_showGuestBook_slot(int type)
{
//    if(type != PHP_GUESTBOOK) return;

//    if(PhpServer::getPhpServer()->getResult().toInt()==100)
//    {
//        showWidget->setGuestBookList(PhpServer::getPhpServer()->getGuestBookList());
//        ShowStatusMessage("留言信息更新成功...");
//        PhpServer::getPhpServer()->setServerFree();
//        return;
//    }
//    switch(PhpServer::getPhpServer()->getReason().toInt())
//    {
//    case 404:
//       TipWidget(this,"无法连接服务器！","请检查网络状态",11);
//       break;
//    case 401:
//        TipWidget(this,"提示","没有权限访问服务器",11);
//        break;
//    default:
//       TipWidget(this,"error_"+QString::number(PhpServer::getPhpServer()->getReason().toInt())," 未知错误 ",11);
//       break;
//    }
//    PhpServer::getPhpServer()->setServerFree();
}

void Widget::Server_updateAPP_slot(const QString &version, const QString &downloadUrl)
{

    qDebug()<<version<<" "<<downloadUrl;
    if(version==Tool::getVersionText())
    {
        ShowStatusMessage("当前为最新版本");
    }
    else
    {
        QMessageBox::StandardButton rb = QMessageBox::question(this,"提示","发现新版本"+version,QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb==QMessageBox::Yes){
            QDesktopServices::openUrl(QUrl(downloadUrl));
        }
    }



//        QString currentDir = QDir::currentPath();
//        QString downloadFilePath = currentDir+"/Timer"+m_version+".exe";
//        QProcess process;
//        process.startDetached(downloadFilePath,QStringList());
//        close();
//    }
}

void Widget::Server_statistic_slot(const StatisticUser &bag)
{
    if(memberWidget==NULL)
    {
        return;
    }
    else
    {
        memberWidget->setStatisticUser(bag);
    }
}

void Widget::Timing_slot()
{
    if(!b_alreadyGotStudioMac)
    {
        m_myServer->requestMac();
    }

    if(!isUserCanRecodeTimer())
    {
        if(b_isTimer==true)
        {
            ShowSystemMessage("提示","计时器已经不能正常提交时间啦");
            ShowStatusMessage("非工作室网络或者网络不通畅，不能计时",2000,1);
        }
        b_isTimer = false;
    }
    else
    {
        if(b_isTimer==false) ShowSystemMessage("提示","计时器开始正常计时啦");
        b_isTimer = true;
    }

    //同步服务器时间
    cycle_updateServerIntervalStatis++;

    if(cycle_updateServerIntervalStatis%10==0)
    {
        updateLocalMAC();
    }


    if(b_isTimer)
    {
        //同步本地用户时间
        cycle_updateUserIntervalStatis++;

        //同步界面时间
        mainWidget->operator_addSecond(Login_currentUser.getWeek().day[Login_currentUser.getNowOfWeekDay()]+cycle_updateUserIntervalStatis);
    }

    if(b_isTimer&&cycle_updateUserIntervalStatis%5==0)
    {
        Login_currentUser.operator_addFiveSecond();
        cycle_updateUserIntervalStatis=0;
    }

    //如果服务器更新时间
    if(b_isTimer&&cycle_updateServerIntervalStatis>=AUTO_UPDATETIME)
    {
        //自动更新操作
        Update_UserTimer();

    }
}

void Widget::Timing_start_slot()
{
    if(!Login_vaild)
    {
        Timing_stop_slot();
        ShowStatusMessage("用户未登录");
    }
    else
    {
        m_timer->start(1000);
    }
}

void Widget::Timing_stop_slot()
{
    m_timer->stop();
}

void Widget::Assist_trueNameButton_slot()
{
    if(Login_vaild)
    {
        show_userWidget_slot();
    }
    else
    {
        show_loginWidget_slot();
    }
}

//展示右键菜单页面
void Widget::ShowMenu(QPoint currentPos)
{
    QMenu *menu = new QMenu;
    menu->setStyleSheet("QMenu{background:#cfcfcf}");

    if(Login_vaild)
    {
        menu->addAction(QIcon(":/image/softImage/system/userMessage_2.png"),"个人资料",this,SLOT(show_userWidget_slot()));
        if(m_timer->remainingTime()<=0) menu->addAction(QIcon(":/image/softImage/softIcon_1.png"),"启动计时",this,SLOT(Timing_start_slot()));
        menu->addAction(QIcon(":/image/softImage/system/update_2.png"),"检查更新",this,SLOT(Update_App()));
        menu->addAction(QIcon(":/image/softImage/system/setting_2.png"),"设置",this,SLOT(show_settingWidget_slot()));
        menu->addAction(QIcon(":/image/softImage/system/about_2.png"),"关于",this,SLOT(show_aboutWidget_slot()));
        menu->addAction(QIcon(":/image/softImage/system/logout_2.png"),"注销",this,SLOT(Login_setUnLoginUser()));
    }
    else
    {
        menu->addAction(QIcon(":/image/softImage/system/login_2.png"),"登录",this,SLOT(show_loginWidget_slot()));
        menu->addAction(QIcon(":/image/softImage/system/register_2.png"),"快速注册",this,SLOT(show_registerWidget_slot()));
        menu->addAction(QIcon(":/image/softImage/system/update_2.png"),"检查更新",this,SLOT(Update_App()));
        menu->addAction(QIcon(":/image/softImage/system/setting_2.png"),"设置",this,SLOT(show_settingWidget_slot()));
        menu->addAction(QIcon(":/image/softImage/system/about_2.png"),"关于",this,SLOT(show_aboutWidget_slot()));
    }
    menu->exec(pos()+currentPos);
    delete menu;
}

void Widget::ShowTrayMenu()
{
    trayMenu->clear();

    if(Login_vaild)
    {
        trayMenu->addAction(QIcon(":/image/softImage/system/userMessage_2.png"),"个人资料",this,SLOT(show_userWidget_slot()));
        trayMenu->addAction(QIcon(":/image/softImage/system/update_2.png"),"更新",this,SLOT(Update_UserTimer()));
        trayMenu->addAction(QIcon(":/image/softImage/system/setting_2.png"),"设置",this,SLOT(show_settingWidget_slot()));
        trayMenu->addAction(QIcon(":/image/softImage/system/about_2.png"),"关于",this,SLOT(show_aboutWidget_slot()));
        trayMenu->addAction(QIcon(":/image/softImage/system/logout_2.png"),"注销",this,SLOT(Login_setUnLoginUser()));
    }
    else
    {
        trayMenu->addAction(QIcon(":/image/softImage/system/login_2.png"),"登录",this,SLOT(show_loginWidget_slot()));
        trayMenu->addAction(QIcon(":/image/softImage/system/register_2.png"),"快速注册",this,SLOT(show_registerWidget_slot()));
        trayMenu->addAction(QIcon(":/image/softImage/system/setting_2.png"),"设置",this,SLOT(show_settingWidget_slot()));
        trayMenu->addAction(QIcon(":/image/softImage/system/about_2.png"),"关于",this,SLOT(show_aboutWidget_slot()));
    }
    trayMenu->addAction(QIcon(":/image/softImage/softIcon_2.png"),"显示主程序",this,SLOT(show_XGTimerWidget_slot()));
    trayMenu->addAction(QIcon(":/image/softImage/system/leave_2.png"),"退出",this,SLOT(close()));

}

void Widget::ShowSystemMessage(const QString &title, const QString &text)
{
    trayWidget->showMessage(title,text,QSystemTrayIcon::Information,200);
}

void Widget::ShowHeadImage()
{
    ImageTool *tool = new ImageTool(0,0);
    tool->setImage(Login_currentUser.getHeadImagePath());
    tool->move(pos()-QPoint(40,40));
    tool->exec();
    delete tool;
}
void Widget::ShowStatusMessage(const QString &mes,const unsigned int &msec,const int type)
{
    if(type>=0&&type<3)
    {
        m_statusLabel[type]->ShowMessage(mes,msec);
        return;
    }
    int find =page_currentFlag==SHOW?1:0;
    int i =page_currentFlag==SHOW?1:0;
    for(;i<3;i++)
    {

        if(m_statusLabel[i]->getMsec()==-1)
        {
            find=i;
            break;
        }
    }
    m_statusLabel[find]->ShowMessage(mes,msec);
}
//？？？
void Widget::startUpdateMovie()
{

}
void Widget::SwitchImageTool(const int &type)
{
    if(im_tool->isVisible())
    {
        CloseImageTool();
    }
    else
    {
        switch(type)
        {
        case USER:
            ShowImageTool(userWidget->getUser().getHeadImageProperty());
            break;
        }
    }
}
void Widget::ShowImageTool(const int &headImageProperty)
{

    im_tool->setMove(QRect(pos(),size()));
    if(headImageProperty>=0)im_tool->setImage(headImageProperty);
    im_tool->show();
}
void Widget::CloseImageTool()
{
    im_tool->close();
}

void Widget::updateAPP(const QString &versoin, QString downloadUrl)
{
//    m_version = versoin;
//    m_downLoadUrl = downloadUrl;
//    if(versoin==Tool::getVersionText()||versoin==""||Login_currentUser.getUpdateStyle()!=0) return;
//    if(!PhpServer::getPhpServer()->RequestDownloadLeastAPP(versoin,downloadUrl))
//    {
//        //服务器无法更新
//    }
//    else
//    {
//        ShowStatusMessage("正在下载更新包...");
//    }
}

void Widget::updateLocalMAC()
{
    m_LocalMAC = Tool::getLocalMac();
}

void Widget::updateMac(const QList<QString> &macList)
{
    m_StudioMacList=macList;
    b_alreadyGotStudioMac = true;
}

bool Widget::isUserCanRecodeTimer()
{
    //对于权限大于5的用户不作判断
    if(Login_currentUser.getPermit()>5)
    {
        return true;
    }

    foreach (QString studio, m_StudioMacList) {
        foreach (QString local, m_LocalMAC) {
            if(studio+"----"==local)
            {
                return true;
            }
        }
    }
    return false;
}

void Widget::UpdateCurrentUserFromUserWidget()
{
    Login_currentUser.setHeadImageProperty(userWidget->getUser().getHeadImageProperty());
}




