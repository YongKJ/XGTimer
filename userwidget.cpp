#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
    setFixedSize(600,292);

    initData();
    initLayout();
    initConnect();
}
UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::initData()
{
}

void UserWidget::initLayout()
{
    bt_headImage = new QPushButton(this);
    bt_headImage->setGeometry(20,20,150,150);
    bt_headImage->setToolTip("点击随机更改头像");

    bt_chooseHeadImage = new QPushButton(this);
    bt_chooseHeadImage->setGeometry(60,180,80,30);
    bt_chooseHeadImage->setText("选择头像");
    bt_chooseHeadImage->setStyleSheet("QPushButton{background:#c6c6c6;color:#000;font-size:14px;font-weight:bold;}"
                                      "QPushButton:hover{background:#fff582}"
                                      "QPushButton:pressed{background:#e80041}");

    bt_editUser = new QPushButton(this);
    bt_editUser->setGeometry(210,250,80,30);
    bt_editUser->setText("编辑");
    bt_editUser->setStyleSheet("QPushButton{background:rgb(212,48,48);color:#FFFFFF;font-size:13px;font-weight:bold;}"
                               "QPushButton:hover{background-color:#DF7DAF}"
                               "QPushButton:pressed{background-color:#F6B56C}");

    bt_submit = new QPushButton(this);
    bt_submit->hide();
    bt_submit->setText("提交修改");
    bt_submit->setGeometry(310,250,80,30);
    bt_submit->setStyleSheet("QPushButton{background:rgb(212,48,48);color:#FFFFFF;font-size:13px;font-weight:bold;}"
                                 "QPushButton:hover{background-color:#DF7DAF}"
                                 "QPushButton:pressed{background-color:#F6B56C}");

    bt_deleteEdit = new QPushButton(this);
    bt_deleteEdit->hide();
    bt_deleteEdit->setGeometry(400,250,80,30);
    bt_deleteEdit->setText("取消修改");
    bt_deleteEdit->setStyleSheet("QPushButton{background:#c6c6c6;color:#000;font-size:14px;font-weight:bold;}"
                             "QPushButton:hover{background:#fff582}"
                             "QPushButton:pressed{background:#e80041}");

    lb_userName = new QLabel(this);
    lb_e_userName = new QLineEdit(this);
    lb_userName->setGeometry(195,30,70,30);
    lb_e_userName->setGeometry(280,30,130,25);
    lb_userName->setText("用户:");
    lb_e_userName->setEnabled(false);
    lb_userName->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    lb_e_userName->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_trueName = new QLabel(this);
    le_trueName = new QLineEdit(this);
    lb_trueName->setGeometry(195,60,70,30);
    le_trueName->setGeometry(280,60,85,25);
    lb_trueName->setText("真实姓名:");
    le_trueName->setEnabled(false);
    lb_trueName->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    le_trueName->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_sex = new QLabel(this);
    cb_sex = new QComboBox(this);
    lb_sex->setGeometry(195,90,70,30);
    cb_sex->setGeometry(280,90,85,25);
    lb_sex->setText("性别:");
    cb_sex->addItem("男");
    cb_sex->addItem("女");
    cb_sex->setEnabled(false);
    lb_sex->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    cb_sex->setStyleSheet("QComboBox{background:transparent;color:#fff;font-size:14px;font-weight:bold;}");

    lb_registerTime = new QLabel(this);
    lb_e_registerTime = new QLineEdit(this);
    lb_registerTime->setGeometry(195,120,90,30);
    lb_e_registerTime->setGeometry(280,120,85,25);
    lb_registerTime->setText("注册时间:");
    lb_e_registerTime->setEnabled(false);
    lb_registerTime->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    lb_e_registerTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_permission = new QLabel(this);
    lb_e_permission = new QLineEdit(this);
    lb_permission->setGeometry(410,90,90,30);
    lb_e_permission->setGeometry(480,90,85,25);
    lb_permission->setText("权限:");
    lb_e_permission->setEnabled(false);
    lb_permission->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    lb_e_permission->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_onlineTime = new QLabel(this);
    lb_e_onlineTime = new QLineEdit(this);
    lb_onlineTime->setGeometry(410,120,150,30);
    lb_e_onlineTime->setGeometry(410,150,155,25);
    lb_onlineTime->setText("上一次登录时间:");
    lb_e_onlineTime->setEnabled(false);
    lb_onlineTime->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    lb_e_onlineTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_password = new QLabel(this);
    bt_changePassword = new QPushButton(this);
    lb_password->setGeometry(195,150,90,30);
    bt_changePassword->setGeometry(280,150,80,25);
    lb_password->setText("密码:");
    bt_changePassword->setText("******");
    bt_changePassword->setEnabled(false);
    lb_password->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    bt_changePassword->setStyleSheet("QPushButton{background:transparent;color:#fff;font-size:14px;font-weight:bold;}");
    bt_changePassword->setFlat(true);

    lb_motto = new QLabel(this);
    le_motto = new QLineEdit(this);
    lb_motto->setGeometry(195,210,90,30);
    le_motto->setGeometry(280,210,285,25);
    lb_motto->setText("格言:");
    le_motto->setEnabled(false);
    lb_motto->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    le_motto->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_major = new QLabel(this);
    le_major = new QLineEdit(this);
    lb_major->setGeometry(410,30,70,30);
    le_major->setGeometry(480,30,85,25);
    lb_major->setText("专业:");
    le_major->setEnabled(false);
    lb_major->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    le_major->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_contactWay = new QLabel(this);
    le_contactWay = new QLineEdit(this);
    lb_contactWay->setGeometry(410,60,70,30);
    le_contactWay->setGeometry(480,60,85,25);
    lb_contactWay->setText("联系方式:");
    le_contactWay->setEnabled(false);
    lb_contactWay->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    le_contactWay->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_member = new QLabel(this);
    cb_member = new QComboBox(this);
    lb_member->setGeometry(195,180,90,30);
    cb_member->setGeometry(280,180,230,27);
    lb_member->setText("成员:");
    cb_member->setEnabled(false);
    cb_member->addItem(QIcon(":/image/softImage/softIcon.png"),"实习成员");
    cb_member->addItem(QIcon(":/image/headImage/system/image_29.png"),"正式成员");
    lb_member->setStyleSheet("QLabel{background:transparent;color:#a6a6a6;font-size:14px;font-weight:bold;}");
    cb_member->setStyleSheet("QComboBox{background:transparent;color:#fff;font-size:14px;font-weight:bold;}");
}

void UserWidget::initConnect()
{
    connect(bt_headImage,SIGNAL(clicked(bool)),this,SLOT(RandBuildHeadImage()));
    connect(bt_chooseHeadImage,SIGNAL(clicked(bool)),this,SLOT(ChooseheadImage(bool)));
    connect(bt_submit,SIGNAL(clicked(bool)),this,SLOT(bt_submit_slot()));
    connect(bt_editUser,SIGNAL(clicked(bool)),this,SLOT(bt_editUser_slot()));
    connect(bt_deleteEdit,SIGNAL(clicked(bool)),this,SLOT(bt_deleteEdit_slot()));
    connect(bt_changePassword,SIGNAL(clicked(bool)),this,SLOT(bt_changePassword_slot()));
    connect(bt_chooseHeadImage,SIGNAL(clicked(bool)),this,SLOT(bt_editUser_slot()));
}

void UserWidget::setServer(MyServer *server)
{
    m_myServer = server;
}

void UserWidget::setNoUser()
{
    User user;
    user.init();

    setUser(user);
}

User UserWidget::getUser() const
{
    return m_user;
}

void UserWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setPen(Qt::red);
//    painter.drawLine(375,30,375,260);

    event->accept();
}

void UserWidget::bt_submit_slot()
{
    //检测数据是否合法
    if(le_motto->text().trimmed().length()>20)
    {
        TipWidget(this,"提交失败","用户信息不合法",11);
        return;
    }

    m_user.setTrueName(le_trueName->text().trimmed());
    m_user.setSex(cb_sex->currentIndex());
    m_user.setSubjectName(le_major->text().trimmed());
    m_user.setPhoneNumber(le_contactWay->text().trimmed());
    m_user.setMotto(le_motto->text().trimmed());

    m_myServer->updateUser(m_user);

    bt_editUser->show();
    bt_deleteEdit->hide();
    bt_submit->hide();
    setUnEdit();
}

void UserWidget::bt_deleteEdit_slot()
{
    setUser(m_user);
    bt_editUser->show();
    bt_submit->hide();
    bt_deleteEdit->hide();
    setUnEdit();
}

void UserWidget::bt_editUser_slot()
{
    bt_editUser->hide();
    bt_submit->show();
    bt_deleteEdit->show();
    setToEdit();
}

void UserWidget::bt_changePassword_slot()
{
    ChangePassword *m_changePassword = new ChangePassword;
    connect(m_changePassword,SIGNAL(SignalToDeleteLogin()),this,SLOT(deleteUser()));
    m_changePassword->setUser(m_user);
    m_changePassword->exec();

    delete m_changePassword;
}

void UserWidget::deleteUser()
{
    emit SignalToDeleteUser();
}

void UserWidget::setUnEdit()
{
    lb_e_userName->setEnabled(false);
    lb_e_userName->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    le_trueName->setEnabled(false);
    le_trueName->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    cb_sex->setEnabled(false);
    cb_sex->setStyleSheet("QComboBox{background:transparent;color:#fff;font-size:14px;font-weight:bold;}");

    lb_e_registerTime->setEnabled(false);
    lb_e_registerTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_e_permission->setEnabled(false);
    lb_e_permission->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_e_onlineTime->setEnabled(false);
    lb_e_onlineTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    bt_changePassword->setText("******");
    bt_changePassword->setEnabled(false);
    bt_changePassword->setStyleSheet("QPushButton{background:transparent;color:#fff;font-size:14px;font-weight:bold;}");
    bt_changePassword->setFlat(true);

    le_motto->setEnabled(false);
    le_motto->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    le_major->setEnabled(false);
    le_major->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    le_contactWay->setEnabled(false);
    le_contactWay->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    lb_e_onlineTime->setEnabled(false);
    lb_e_onlineTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border-width:0;border-style:outset}");

    cb_member->setEnabled(false);
    cb_member->setStyleSheet("QComboBox{background:transparent;color:#fff;font-size:14px;font-weight:bold;}");

}

void UserWidget::setToEdit()
{
    bt_changePassword->setText("修改密码");
    bt_changePassword->setFlat(false);
    bt_changePassword->setEnabled(true);
    bt_changePassword->setStyleSheet("QPushButton{background:#c6c6c6;color:#000;font-size:14px;font-weight:bold;}"
                                     "QPushButton:hover{background:#fff582}"
                                     "QPushButton:pressed{background:#e80041}");

    cb_sex->setEnabled(true);
    cb_sex->setStyleSheet("QComboBox{background:#FFF;border:1px solid gray;border-radius:3px;padding:1px 2px 1px 2px;}"
                          "QComboBox:hover{border: 2px solid #F00;}"
                          "QComboBox::drop-down{subcontrol-origin: padding;subcontrol-position: top right;width: 20px;}");
    cb_sex->view()->setStyleSheet("QAbstractItemView{background:#FFF;}");

    lb_e_userName->setEnabled(false);
    lb_e_userName->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border:0;border-bottom:2px solid #c6c6c6;}");

    le_trueName->setEnabled(true);
    le_trueName->setStyleSheet("QLineEdit{background:#fff;color:#000;border: 1px solid #c6c6c6;border-radius: 4px; font-size:14px;font-weight:bold;}"
                               "QLineEdit:hover{border: 2px solid #F00;background:#FFC1C1;}"
                               "QLineEdit:focus{border: 2px solid #F00;background:#FFC1C1;}");

    lb_e_registerTime->setEnabled(false);
    lb_e_registerTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border:0;border-bottom:2px solid #c6c6c6;}");

    lb_e_permission->setEnabled(false);
    lb_e_permission->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border:0;border-bottom:2px solid #c6c6c6;}");

    lb_e_onlineTime->setEnabled(false);
    lb_e_onlineTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border:0;border-bottom:2px solid #c6c6c6;}");

    le_motto->setEnabled(true);
    le_motto->setStyleSheet("QLineEdit{background:#fff;color:#000;border: 1px solid #c6c6c6;border-radius: 4px; font-size:14px;font-weight:bold;}"
                            "QLineEdit:hover{border: 2px solid #F00;background:#FFC1C1;}"
                            "QLineEdit:focus{border: 2px solid #F00;background:#FFC1C1;}");

    le_major->setEnabled(true);
    le_major->setStyleSheet("QLineEdit{background:#fff;color:#000;border: 1px solid #c6c6c6;border-radius: 4px; font-size:14px;font-weight:bold;}"
                            "QLineEdit:hover{border: 2px solid #F00;background:#FFC1C1;}"
                            "QLineEdit:focus{border: 2px solid #F00;background:#FFC1C1;}");

    le_contactWay->setEnabled(true);
    le_contactWay->setStyleSheet("QLineEdit{background:#fff;color:#000;border: 1px solid #c6c6c6;border-radius: 4px; font-size:14px;font-weight:bold;}"
                                 "QLineEdit:hover{border: 2px solid #F00;background:#FFC1C1;}"
                                 "QLineEdit:focus{border: 2px solid #F00;background:#FFC1C1;}");

    lb_e_onlineTime->setEnabled(false);
    lb_e_onlineTime->setStyleSheet("QLineEdit{background:transparent;color:#fff;font-size:14px;font-weight:bold;border:0;border-bottom:2px solid #c6c6c6;}");

}

void UserWidget::RandBuildHeadImage()
{
    QString sheet = "QPushButton{border-image:url(";
    sheet = sheet+User::getHeadImagePath(rand()%(IMAGECOUT+1))+")}";
    bt_headImage->setStyleSheet(sheet);
}

void UserWidget::ChooseheadImage(const bool &type)
{
    emit SignalToSwitchTool(7);
}

void UserWidget::ToolChangeImage(int headImageProperty)
{
    QString sheet = "QPushButton{border-image:url(";
    sheet = sheet+User::getHeadImagePath(headImageProperty)+")}";
    bt_headImage->setStyleSheet(sheet);
    m_user.setHeadImageProperty(headImageProperty);
}

void UserWidget::setUser(const User &user)
{
    QString sheet = "QPushButton{border-image:url(:/image/headImage/image_";
    sheet = sheet+QString::number(user.getHeadImageProperty())+".jpg)}";
    bt_headImage->setStyleSheet(sheet);
    m_user = user;

    lb_e_userName->setText(user.getUserName());
    le_trueName->setText(user.getTrueName());
    cb_sex->setCurrentIndex(user.getSex());
    lb_e_registerTime->setText(user.getRegisterTimeString().mid(0,10));
    le_motto->setText(user.getMotto());
    le_major->setText(user.getSubjectName());
    lb_e_permission->setText(QString("%1").arg(user.getPermit()));
    le_contactWay->setText(user.getPhoneNumber());
    lb_e_onlineTime->setText(user.getLastTimeString());
    cb_member->setCurrentIndex(user.getMember());
}
