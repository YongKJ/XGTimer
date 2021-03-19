#include "guestbookwidget.h"

GuestBookWidget::GuestBookWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(395,90);
    init();
    initLayout();
    initConnect();
}

GuestBookWidget::~GuestBookWidget()
{
}

void GuestBookWidget::init()
{
    m_mode = 0;
}

void GuestBookWidget::initLayout()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);

    bt_headImage = new QPushButton(this);
    bt_read = new QPushButton(this);
    bt_user = new QPushButton(this);

    bt_read->setFont(Tool::Font());
    bt_user->setFont(Tool::Font());

    bt_read->setToolTip("赞");
    bt_user->setText("匿名者");

    lb_text = new QTextEdit(this);
    lb_date = new QLabel(this);
    lb_property = new QLabel(this);

    lb_text->setFont(Tool::Font(14,false));
    lb_date->setFont(Tool::Font());
    lb_property->setFont(Tool::Font(12,false));
    lb_property->setText("留言");

    lb_text->setText("内容");
    lb_date->setText("xxxx-xx-xx xx:xx:xx");
    lb_text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    bt_headImage->setGeometry(5,5,55,55);
    bt_user->setGeometry(0,65,65,23);
    bt_read->setGeometry(372,10,20,20);

    bt_headImage->setStyleSheet("QPushButton{background:transparent}");
    bt_user->setStyleSheet("QPushButton{background:transparent;color:#8DEEEE}"
                           "QPushButton:hover{color:#F00}");
    bt_read->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/softImage/details/read_0.png)}"
                           "QPushButton:hover{border-image:url(:/image/softImage/details/read_2.png)}"
                           "QPushButton:pressed{border-image:url(:/image/softImage/details/read_3.png)}");

    lb_text->setGeometry(70,5,300,70);
    lb_date->setGeometry(200,73,170,20);
    lb_property->setGeometry(75,73,100,20);

    lb_text->setStyleSheet("QTextEdit{background:transparent;border:none}");
    lb_date->setStyleSheet("QLabel{background:transparent}");
    lb_property->setStyleSheet("QLabel{background:transparent;color:#636363;}"
                               "QLabel:hover{color:#F00}");

    lb_text->setEnabled(false);
    lb_text->setAlignment(Qt::AlignTop);

    bt_delete = new QPushButton(this);
    bt_delete->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/softImage/system/close_2.png)}"
                             "QPushButton:hover{border-image:url(:/image/softImage/system/close_1.png)}"
                             "QPushButton:pressed{border-image:url(:/image/softImage/system/close_0.png)}");
    bt_delete->setGeometry(372,70,20,20);
    bt_delete->setVisible(false);

}

void GuestBookWidget::initConnect()
{
    connect(bt_read,SIGNAL(clicked(bool)),this,SLOT(button_read_slot()));
    connect(bt_delete,SIGNAL(clicked(bool)),this,SLOT(button_delete_slot()));

}

void GuestBookWidget::setGuestBook(const GuestBook &book)
{
    m_book = book;
    setSender(book.getSendUser());
    lb_text->setText(book.getText());
    lb_date->setText(book.getDateNotYear());
    lb_property->setText(book.getProertyString());

    switch(book.getProerty())
    {
    case GUEST_PUBLIC:
        lb_property->setStyleSheet("QLabel{background:transparent;color:#636363}"
                                   "QLabel:hover{color:#F00}");
        break;
    case GUEST_INFORM:
        lb_property->setStyleSheet("QLabel{background:transparent;color:#32CD32}"
                                   "QLabel:hover{color:#F00}");
        break;
    case GUEST_PLAN:
        lb_property->setStyleSheet("QLabel{background:transparent;color:#FF00FF}"
                                   "QLabel:hover{color:#F00}");
        break;
    }
}

void GuestBookWidget::setEditMode(const User &user)
{
    m_mode = 1;
    cb_property = new QComboBox(this);
    GuestBook book;
    book.setSendUser(user);
    setGuestBook(book);
    lb_property->setVisible(false);
    lb_date->setVisible(false);
    bt_user->setVisible(false);
    lb_text->setEnabled(true);
    this->setFixedSize(395,90);
    lb_text->setGeometry(70,0,260,62);
    lb_text->setFont(Tool::Font(16,true));
    QPalette palette;
    palette.setColor(QPalette::Highlight,QColor(Qt::blue));
    palette.setColor(QPalette::Text,QColor(Qt::white));
    lb_text->setPalette(palette);
    bt_read->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/softImage/details/send_0.png)}"
                           "QPushButton:hover{border-image:url(:/image/softImage/details/send_2.png)}"
                           "QPushButton:pressed{border-image:url(:/image/softImage/details/send_3.png)}");
    bt_read->setGeometry(340,10,30,30);
    bt_read->setToolTip("发送");


    cb_property->setFont(Tool::Font(12,false));
    cb_property->setStyleSheet("QComboBox{background:#F5F5F5;border:0px solid gray;border-radius:3px;padding:1px 2px 1px 2px;}"
                               "QComboBox::down-arrow{image:url(:/image/softImage/details/drow_arrow_0.png);"
                               "width:10px;"
                               "height:10px;}"
                               "QComboBox:hover{border: 1px solid gray;}"
                               "QComboBox::drop-down{"
                               "width: 20px;"
                               "background:#F5F5F5;"
                               "border-radius:3px;}");

    cb_property->view()->setStyleSheet("QAbstractItemView{background:#FFF;}");
    cb_property->setGeometry(5,62,50,18);

    cb_type = new QComboBox(this);

    cb_type->setFont(Tool::Font(12,false));
    cb_type->setStyleSheet("QComboBox{background:#F5F5F5;border:0px solid gray;border-radius:3px;padding:1px 2px 1px 2px;}"
                               "QComboBox::down-arrow{image:url(:/image/softImage/details/drow_arrow_0.png);"
                               "width:10px;"
                               "height:10px;}"
                               "QComboBox:hover{border: 1px solid gray;}"
                               "QComboBox::drop-down{"
                               "width: 20px;"
                               "background:#F5F5F5;"
                               "border-radius:3px;}");
    cb_type->view()->setStyleSheet("QAbstractItemView{background:#FFF;}");
    cb_type->setGeometry(58,62,50,18);


    cb_property->setCurrentIndex(1);
    bt_more = new QPushButton(this);
    bt_more->setGeometry(60,65,15,15);
    bt_more->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/softImage/details/add_0.png)}"
                           "QPushButton:hover{border-image:url(:/image/softImage/details/add_3.png)}");

    bt_more->setVisible(true);
    connect(cb_property,SIGNAL(currentIndexChanged(int)),this,SLOT(update_type_slot(int)));
    connect(bt_more,SIGNAL(clicked(bool)),this,SLOT(button_more_slot()));
    cb_property->setCurrentIndex(0);
    button_more_slot();
}

void GuestBookWidget::setText(const QString &text)
{
    lb_text->setText(text);
}

void GuestBookWidget::setTitle(const QString &title)
{
}

void GuestBookWidget::setSender(const User &user)
{
    QString sheet = "QPushButton{border-image:url(";

    sheet += user.getHeadImagePath()+")}";

    bt_headImage->setStyleSheet(sheet);

    bt_user->setText(user.getTrueName());
    if(user.getPermit()>=3)
    {
        bt_user->setStyleSheet("QPushButton{background:transparent;color:#32CD32}"
                               "QPushButton:hover{color:#F00}");
        bt_user->setToolTip("这家伙是一个管理员");
        bt_headImage->setToolTip("这家伙是一个管理员");
    }
    if(m_mode==1)
    {
        cb_property->clear();
        cb_property->addItem("留言");
        cb_property->addItem("计划");
        if(user.getPermit()>=3) cb_property->addItem("公告");
    }
}

GuestBook GuestBookWidget::getGuestBook()
{
    GuestBook book;

    if(m_mode==0)
    {
        return m_book;
    }
    else
    {
        book = m_book;
        book.setText(lb_text->toPlainText());
        book.setProerty(cb_property->currentIndex());
        if(cb_type<=0) book.setType(0);
        else book.setType(cb_type->currentIndex());
    }
    return book;
}

void GuestBookWidget::button_delete_slot()
{
    emit sendGuestBook(m_book,SIGN_DELETE);
}

void GuestBookWidget::button_read_slot()
{
    emit sendGuestBook(m_book,SIGN_READ);
}

void GuestBookWidget::button_more_slot()
{
    if(bt_more->isVisible())
    {
        bt_more->setVisible(false);
        cb_type->setVisible(true);
    }
    else
    {
        bt_more->setVisible(true);
        cb_type->setVisible(false);
    }
}

void GuestBookWidget::update_type_slot(int type)
{
    cb_type->clear();
    switch(type)
    {
    case GUEST_PUBLIC:
        cb_type->addItem("成员");
        cb_type->addItem("全局");
        break;
    case GUEST_PLAN:
        cb_type->addItem("成员");
        cb_type->addItem("全局");
        cb_type->addItem("私有");
        break;
    case GUEST_INFORM:
        cb_type->addItem("成员");
        cb_type->addItem("全局");
        break;
    }
}
