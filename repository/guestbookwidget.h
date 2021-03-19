#ifndef GUESTBOOKWIDGET_H
#define GUESTBOOKWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <tool.h>
#include <guestbook.h>
#include <QPalette>
#include <QTextEdit>
#include <QComboBox>
#include <QAbstractItemView>
#include <QListWidgetItem>
namespace Ui {
class GuestBookWidget;
}
enum{SIGN_READ,SIGN_DELETE};
enum{TYPE_MEMBER,TYPE_PUBLIC,TYPE_PRIVATE};

class GuestBookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GuestBookWidget(QWidget *parent = 0);
    ~GuestBookWidget();

    void init();
    void initLayout();
    void initConnect();

    void setGuestBook(const GuestBook &book);
    void setEditMode(const User &user);

    void setText(const QString &text);
    void setTitle(const QString &title);

    void setSender(const User &user);

    GuestBook getGuestBook();

    QPushButton *bt_headImage;
    QPushButton *bt_read;
    QPushButton *bt_user;
    QPushButton *bt_delete;
    QTextEdit *lb_text;
    QLabel *lb_property;
    QLabel *lb_date;

    QComboBox *cb_property;
    QComboBox *cb_type;
    QPushButton *bt_more;

    int m_mode;

private:
    Ui::GuestBookWidget *ui;

    GuestBook m_book;

public slots:
    void button_delete_slot();
    void button_read_slot();
    void button_more_slot();
    void update_type_slot(int type);

signals:
    void sendGuestBook(GuestBook,int);


};

#endif // GUESTBOOKWIDGET_H
