#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    setFixedSize(600,292);

    initDate();
    initLayout();
    initConnect();
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::initDate()
{

}

void SettingWidget::initLayout()
{
    lb_closeStyle = new QLabel(this);
    lb_closeStyle->setText("关闭风格 ：");

    bt_selectCloseStyle_0 = new QRadioButton("直接关闭",this);
    bt_selectCloseStyle_1 = new QRadioButton("关闭到窗口栏",this);

    gb_closeStyle = new QButtonGroup(this);
    gb_closeStyle->addButton(bt_selectCloseStyle_0,0);
    gb_closeStyle->addButton(bt_selectCloseStyle_1,1);   

    lb_softStyle = new QLabel(this);
    lb_softStyleMessage = new QLabel(this);
    lb_softStyle->setText("软件样式 ：");
    lb_softStyleMessage->setText("吴均潮黑色 V 1.1 版");

    lb_updateCycle = new QLabel(this);
    lb_updateCycle->setText("  更新 :");
    lb_updateCycle->setStyleSheet("QLabel{background:transparent;color:#e80041;font-size:20px;font-weight:bold;}"
                                  "QLabel:hover{color:#fff582}"
                                  "QLabel:pressed{}");
    lb_updateCycle->setGeometry(50,100,100,30);

    lb_updateCycleMessage_1 = new QComboBox(this);
    lb_updateCycleMessage_2 = new QComboBox(this);

    lb_updateCycleMessage_1->addItem("自动更新/10秒钟");
    lb_updateCycleMessage_2->addItem("手动更新限制/5秒钟");

    lb_updateCycleMessage_1->setFont(Tool::Font(16,false));
    lb_updateCycleMessage_1->setStyleSheet("QComboBox{background:#F5F5F5;border:0px solid gray;border-radius:3px;padding:1px 2px 1px 2px;}"
                               "QComboBox::down-arrow{image:url(:/image/softImage/details/drow_arrow_0.png);"
                               "width:10px;"
                               "height:10px;}"
                               "QComboBox:hover{border: 1px solid gray;}"
                               "QComboBox::drop-down{"
                               "width: 20px;"
                               "background:#F5F5F5;"
                               "border-radius:3px;}");
    lb_updateCycleMessage_1->view()->setStyleSheet("QAbstractItemView{background:#FFF;}");

    lb_updateCycleMessage_2->setFont(Tool::Font(16,false));
    lb_updateCycleMessage_2->setStyleSheet("QComboBox{background:#F5F5F5;border:0px solid gray;border-radius:3px;padding:1px 2px 1px 2px;}"
                               "QComboBox::down-arrow{image:url(:/image/softImage/details/drow_arrow_0.png);"
                               "width:10px;"
                               "height:30px;}"
                               "QComboBox:hover{border: 1px solid gray;}"
                               "QComboBox::drop-down{"
                               "width: 20px;"
                               "background:#F5F5F5;"
                               "border-radius:3px;}");
    lb_updateCycleMessage_2->view()->setStyleSheet("QAbstractItemView{background:#FFF;}");



    cb_update = new QComboBox(this);

    cb_update->setFont(Tool::Font(16,false));
    cb_update->setStyleSheet("QComboBox{background:#F5F5F5;border:0px solid gray;border-radius:3px;padding:1px 2px 1px 2px;}"
                               "QComboBox::down-arrow{image:url(:/image/softImage/details/drow_arrow_0.png);"
                               "width:10px;"
                               "height:20px;}"
                               "QComboBox:hover{border: 1px solid gray;}"
                               "QComboBox::drop-down{"
                               "width: 20px;"
                               "background:#F5F5F5;"
                               "border-radius:3px;}");
    cb_update->view()->setStyleSheet("QAbstractItemView{background:#FFF;}");
    cb_update->addItem("更新及时提示");
    cb_update->addItem("开发者模式，手动更新");
    cb_update->setCurrentIndex(0);




    lb_updateCycleMessage_1->setGeometry(160,100,200,30);
    lb_updateCycleMessage_2->setGeometry(160,140,200,30);
    cb_update->setGeometry(160,180,200,30);

    bt_submit = new QPushButton(this);
    bt_submit->setText("设置");

    lb_closeStyle->setGeometry(50,20,100,30);
    lb_closeStyle->setStyleSheet("QLabel{background:transparent;color:#e80041;font-size:20px;font-weight:bold;}"
                                 "QLabel:hover{color:#fff582}"
                                 "QLabel:pressed{}");
    bt_selectCloseStyle_0->setStyleSheet("QRadioButton{background:transparent;color:#e9a4ff;font-size:12px;font-weight:bold;}"
                                         "QRadioButton:hover{color:#DF7DAF}"
                                         "QRadioButton:pressed{color:#E6FF13}");
    bt_selectCloseStyle_1->setStyleSheet("QRadioButton{background:transparent;color:#e9a4ff;font-size:12px;font-weight:bold;}"
                                         "QRadioButton:hover{color:#DF7DAF}"
                                         "QRadioButton:pressed{color:#E6FF13}");
    bt_selectCloseStyle_0->setGeometry(180,20,100,30);
    bt_selectCloseStyle_1->setGeometry(280,20,150,30);

    bt_selectCloseStyle_1->setChecked(true);

    lb_softStyle->setStyleSheet("QLabel{background:transparent;color:#e80041;font-size:20px;font-weight:bold;}"
                                "QLabel:hover{color:#fff582}"
                                "QLabel:pressed{}");

    lb_softStyleMessage->setStyleSheet("QLabel{background:transparent;color:#e9a4ff;font-size:14px;font-weight:bold;}"
                                       "QLabel:hover{color:#fff582}"
                                       "QLabel:pressed{}");
    lb_softStyle->setGeometry(50,60,100,30);
    lb_softStyleMessage->setGeometry(170,60,200,30);

    bt_submit->setGeometry(430,220,80,30);
    bt_submit->setStyleSheet("QPushButton{background:#FF34B3;color:#000;font-size:14px;font-weight:bold;}"
                             "QPushButton:hover{background:#fff582}"
                             "QPushButton:pressed{background:#e80041}");

}

void SettingWidget::initConnect()
{
    connect(bt_submit,SIGNAL(clicked(bool)),this,SLOT(Update_setting_Button()));
}

void SettingWidget::setUser(const User &user)
{
    if(user.getCloseStyle()==0)
    {
        bt_selectCloseStyle_0->setChecked(true);
    }
    else
    {
        bt_selectCloseStyle_1->setChecked(true);
    }
    cb_update->setCurrentIndex(user.getUpdateStyle());
    return;
}

void SettingWidget::Update_setting_Button()
{
    User user;
    user.setCloseStyle(gb_closeStyle->checkedId());
    user.setUpdateStyle(cb_update->currentIndex());

    emit SignalToSettingUpdate(user);
}
