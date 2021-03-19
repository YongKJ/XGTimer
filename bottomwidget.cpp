#include "bottomwidget.h"
#include "ui_bottomwidget.h"

BottomWidget::BottomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomWidget)
{
    ui->setupUi(this);
    setFixedSize(600,52);
    initLayout();
}

BottomWidget::~BottomWidget()
{
    delete ui;
}

void BottomWidget::initLayout()
{
    bt_main = new QPushButton(this);
    bt_show = new QPushButton(this);
    bt_person = new QPushButton(this);
    bt_member = new QPushButton(this);
    bt_about = new QPushButton(this);

    bt_main->setFlat(true);
    bt_show->setFlat(true);
    bt_person->setFlat(true);
    bt_member->setFlat(true);
    bt_about->setFlat(true);

    setPushButtonUnfocus(bt_main);
    setPushButtonUnfocus(bt_show);
    setPushButtonUnfocus(bt_person);
    setPushButtonUnfocus(bt_member);

    bt_main->setText("首页");
    bt_show->setText("展示");
    bt_person->setText("个人统计");
    bt_member->setText("全部统计");

    bt_about->setToolTip("更多信息");
    bt_about->setStyleSheet("QPushButton{border-image:url(:/image/softImage/system/about_0.png);background: transparent}"
                            "QPushButton:hover{border-image:url(:/image/softImage/system/about_2.png)}"
                            "QPushButton:pressed{border-image:url(:/image/softImage/system/about_3.png)}");

    QFont font;
    font.setFamily("方正兰亭黑简体");

    bt_main->setFont(font);
    bt_show->setFont(font);
    bt_person->setFont(font);
    bt_member->setFont(font);


    bt_main->setGeometry(10,1,120,46);
    bt_show->setGeometry(130,1,120,46);
    bt_person->setGeometry(250,1,120,46);
    bt_member->setGeometry(370,1,120,46);

    bt_about->setGeometry(555,10,30,30);
}

void BottomWidget::setPushButtonFocus(QPushButton *bt)
{
    QString styleSheet("QPushButton{background:transparent;color:#FEFF2D;font-size:20px;font-weight:bold;}"
                       "QPushButton:hover{font-size:20px}"
                       "QPushButton:pressed{color:#FF1DF4}");
    bt->setStyleSheet(styleSheet);
}
void BottomWidget::setPushButtonUnfocus(QPushButton *bt)
{
    QString styleSheet("QPushButton{background:transparent;color:#FFF;font-size:18px;font-weight:bold;font-family:FZLTHJW}"
                       "QPushButton:hover{font-size:25px}"
                       "QPushButton:pressed{color:#E6FF13}");
    bt->setStyleSheet(styleSheet);
}
