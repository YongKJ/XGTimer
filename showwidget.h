#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <guestbook.h>
#include <repository/guestbookwidget.h>
#include <QDebug>
#include "tipwidget.h"

namespace Ui {
class ShowWidget;
}

enum{
    SHOW_NONE,
    SHOW_INFORM,
    SHOW_CHAT,
    SHOW_MESSAGE,
    SHOW_ASSIGNMENT};

class ShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWidget(QWidget *parent = 0);
    ~ShowWidget();

    void initData();
    void initLayout();
    void initConnect();

    void setUser(const User &user);
    void setNoUser();
    void InsertGuestBook(const GuestBook &book,const int &position = 0);
    void setGuestBookList(QList<GuestBook> list);

    void setButtonFocus(QPushButton * bt);
    void setButtonUnFocus(QPushButton *bt);

    bool compareValue(const GuestBook &book1,const GuestBook &book2);




private:
    Ui::ShowWidget *ui;

    QPushButton *bt_inform;
    QPushButton *bt_chat;
    QPushButton *bt_message;
    QPushButton *bt_assignment;

    QPushButton *bt_chatEdit;

    QListWidget *textList;
    GuestBookWidget *ed_text;

    bool m_openChat;
    int m_selectStatus;
    User m_user;
    QList<GuestBook> m_list;

public slots:
    void switchChatBlock();
    void sendGuestBookSlot();
    void sendOperatorGuestBookSlot(GuestBook book,const int &type = 0);
    void CurrentItemChangeSlot(QListWidgetItem*current,QListWidgetItem*pervious);

    void show_inform_slot();
    void show_assignment_slot();
    void show_NewMessage_slot();
    void show_chat_slot();

};

#endif // SHOWWIDGET_H
