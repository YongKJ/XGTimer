#include "showwidget.h"
#include "ui_showwidget.h"

ShowWidget::ShowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWidget)
{
    ui->setupUi(this);
    setFixedSize(600,292);

    initData();
    initLayout();
    initConnect();
}

ShowWidget::~ShowWidget()
{
    delete ui;
}

void ShowWidget::initData()
{
    m_openChat = false;
    ed_text = 0;
    m_selectStatus = SHOW_NONE;
}

void ShowWidget::initLayout()
{
    bt_inform = new QPushButton("公告",this);
    bt_chat = new QPushButton("留言区",this);
    bt_message = new QPushButton("未读消息",this);
    bt_assignment = new QPushButton("我的计划",this);

    bt_inform->setGeometry(10,5,130,50);
    bt_chat->setGeometry(10,55,130,50);
    bt_message->setGeometry(10,105,130,50);
    bt_assignment->setGeometry(10,155,130,50);

    bt_chatEdit = new QPushButton(this);
    bt_chatEdit->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/softImage/details/chat_1.png)}"
                           "QPushButton:hover{border-image:url(:/image/softImage/details/chat_3.png)}"
                           "QPushButton:pressed{border-image:url(:/image/softImage/details/chat_4.png)");
    bt_chatEdit->setGeometry(140,175,35,20);
    bt_chatEdit->setToolTip("编辑栏");

    textList = new QListWidget(this);

    textList->setStyleSheet("QListWidget{background:#F5F5F5;}");

    textList->setGeometry(180,5,400,250);
    textList->setSpacing(2);
    textList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ed_text = new GuestBookWidget(this);
    ed_text->setEditMode(User());
    ed_text->setGeometry(180,205,400,50);
    ed_text->setVisible(false);
    show_inform_slot();
}

void ShowWidget::initConnect()
{
    connect(bt_chatEdit,SIGNAL(clicked(bool)),this,SLOT(switchChatBlock()));
    connect(bt_assignment,SIGNAL(clicked(bool)),this,SLOT(show_assignment_slot()));
    connect(bt_inform,SIGNAL(clicked(bool)),this,SLOT(show_inform_slot()));
    connect(bt_chat,SIGNAL(clicked(bool)),this,SLOT(show_chat_slot()));
    connect(bt_message,SIGNAL(clicked(bool)),this,SLOT(show_NewMessage_slot()));
    connect(ed_text->bt_read,SIGNAL(clicked(bool)),this,SLOT(sendGuestBookSlot()));
    connect(textList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(CurrentItemChangeSlot(QListWidgetItem*,QListWidgetItem*)));
}

void ShowWidget::setUser(const User &user)
{
    m_user = user;
    GuestBook book;
    book.setSendUser(user);
    ed_text->setGuestBook(book);
}

void ShowWidget::setNoUser()
{
    setUser(User());
}

void ShowWidget::InsertGuestBook(const GuestBook &book, const int &position)
{
    GuestBookWidget * tempBookItem = new GuestBookWidget();
    tempBookItem->setGuestBook(book);
    QListWidgetItem *tempItem = new QListWidgetItem;

    textList->addItem(tempItem);
    textList->setItemWidget(tempItem,tempBookItem);

    tempItem->setSizeHint(QSize(395,90));

    connect(tempBookItem,SIGNAL(sendGuestBook(GuestBook,int)),this,SLOT(sendOperatorGuestBookSlot(GuestBook,int)));
}

void ShowWidget::setGuestBookList(QList<GuestBook> list)
{
    m_list.clear();
    m_list = list;

    qSort(m_list.begin(),m_list.end(),Tool::compareValue);
    switch (m_selectStatus) {
    case SHOW_INFORM:
        m_selectStatus = SHOW_NONE;
        show_inform_slot();
        break;
    case SHOW_CHAT:
        m_selectStatus = SHOW_NONE;
        show_chat_slot();
        break;
    case SHOW_MESSAGE:
        m_selectStatus = SHOW_NONE;
        show_NewMessage_slot();
        break;
    case SHOW_ASSIGNMENT:
        m_selectStatus = SHOW_NONE;
        show_assignment_slot();
        break;
    }
}

void ShowWidget::setButtonFocus(QPushButton *bt)
{
    QString styleSheet("QPushButton{background:transparent;color:#FEFF2D;font-size:20px;font-weight:bold;}"
                       "QPushButton:hover{font-size:20px}"
                       "QPushButton:pressed{color:#FF1DF4}");
    bt->setStyleSheet(styleSheet);
}

void ShowWidget::setButtonUnFocus(QPushButton *bt)
{
    QString styleSheet("QPushButton{background:transparent;color:#FFE4E1;font-size:18px;font-weight:bold;font-family:FZLTHJW}"
                       "QPushButton:hover{font-size:25px}"
                       "QPushButton:pressed{color:#E6FF13}");
    bt->setStyleSheet(styleSheet);
}

void ShowWidget::switchChatBlock()
{
    if(m_openChat){
        m_openChat = false;
        textList->setGeometry(180,5,400,250);
        ed_text->setVisible(false);
    }
    else
    {
        m_openChat = true;
        textList->setGeometry(180,5,400,200);
        ed_text->setVisible(true);

    }
}

void ShowWidget::sendGuestBookSlot()
{
//    if(!m_user.isVaild()){
//        TipWidget(this,"提示","需要登录",11);
//        return ;
//    }
//    GuestBook book = ed_text->getGuestBook();
//    if(book.getText()=="")
//    {
//        TipWidget(this,"提示","不能发送空消息",11);
//        return ;
//    }
//    book.setSendUser(m_user);
//    if(!PhpServer::getPhpServer()->RequestUpdateGuestBook(book))
//    {
//        TipWidget(this,"错误","无法启用服务器",11);
//        return;
//    }
//    switchChatBlock();
//    if(ed_text!=0) ed_text->setText("");
}

void ShowWidget::sendOperatorGuestBookSlot(GuestBook book, const int &type)
{
//    if(type==SIGN_DELETE)
//    {
//        if(book.getSendUser().getPermit()>=3&&m_user.getPermit()<5&&m_user.getUserName()!=book.getSendUser().getUserName())
//        {
//            TipWidget(this,"删除失败","用户权限不足",11);
//            return;
//        }
//        if(!PhpServer::getPhpServer()->RequestUpdateGuestBook(book,2,m_user))
//        {
//            TipWidget(this,"删除失败","重复操作",11);
//            return;
//        }
//    }
}

void ShowWidget::CurrentItemChangeSlot(QListWidgetItem *current, QListWidgetItem *pervious)
{
    if(current!=NULL)
    {
        GuestBookWidget * tempCurrent = (GuestBookWidget*)textList->itemWidget(current);
        if(m_user.getPermit()>=3||tempCurrent->getGuestBook().getSendUser().getUserName()==m_user.getUserName())tempCurrent->bt_delete->setVisible(true);
    }
    if(pervious!=NULL)
    {
        GuestBookWidget * tempPervious = (GuestBookWidget*)textList->itemWidget(pervious);
        tempPervious->bt_delete->setVisible(false);
    }


}

void ShowWidget::show_inform_slot()
{
    if(m_selectStatus==SHOW_INFORM) return;
    m_selectStatus = SHOW_INFORM;
    setButtonFocus(bt_inform);
    setButtonUnFocus(bt_chat);
    setButtonUnFocus(bt_message);
    setButtonUnFocus(bt_assignment);

    textList->clear();
    foreach (GuestBook book, m_list) {
        switch(book.getProerty())
        {
        case GUEST_INFORM:
            break;
        case GUEST_PLAN:
            break;
        case GUEST_PUBLIC:
            break;
        }
        InsertGuestBook(book);
    }
}

void ShowWidget::show_assignment_slot()
{
    if(m_selectStatus==SHOW_ASSIGNMENT) return;
    m_selectStatus = SHOW_ASSIGNMENT;
    setButtonUnFocus(bt_inform);
    setButtonUnFocus(bt_chat);
    setButtonUnFocus(bt_message);
    setButtonFocus(bt_assignment);

    textList->clear();
    foreach (GuestBook book,m_list) {
        if(book.getProerty()!=GUEST_PLAN||book.getSendUser().getUserName()!=m_user.getUserName()){
            continue;
        }
        InsertGuestBook(book);
    }

}

void ShowWidget::show_NewMessage_slot()
{
    if(m_selectStatus==SHOW_MESSAGE) return;
    m_selectStatus = SHOW_MESSAGE;
    setButtonUnFocus(bt_inform);
    setButtonUnFocus(bt_chat);
    setButtonFocus(bt_message);
    setButtonUnFocus(bt_assignment);

    textList->clear();

}

void ShowWidget::show_chat_slot()
{
    if(m_selectStatus==SHOW_CHAT)return;
    m_selectStatus = SHOW_CHAT;
    setButtonUnFocus(bt_inform);
    setButtonFocus(bt_chat);
    setButtonUnFocus(bt_message);
    setButtonUnFocus(bt_assignment);

    textList->clear();

    foreach (GuestBook book,m_list) {
        if(book.getProerty()!=GUEST_PUBLIC){
            continue;
        }
        InsertGuestBook(book);
    }
}
