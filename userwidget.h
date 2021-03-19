#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include "changepassword.h"
#include "user.h"
#include "repository/imagetool.h"
#include <QDebug>
#include "tipwidget.h"
#include "myserver.h"

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = 0);
    ~UserWidget();

    void initData();
    void initLayout();
    void initConnect();

    void setServer(MyServer *server);

    void setNoUser();
    User getUser() const;

    QPushButton *bt_submit;

public slots:
    void setUser(const User &user);
    void RandBuildHeadImage();
    void ChooseheadImage(const bool &type);
    void ToolChangeImage(int headImageProperty);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void bt_submit_slot();
    void bt_deleteEdit_slot();
    void bt_editUser_slot();
    void bt_changePassword_slot();
    void deleteUser();

private:
    Ui::UserWidget *ui;

    User m_user;

    QPushButton *bt_chooseHeadImage;
    QPushButton *bt_headImage;
    QPushButton *bt_editUser;
    QPushButton *bt_confirmEdit;
    QPushButton *bt_deleteEdit;
    QPushButton *bt_changePassword;

    QLabel *lb_userName;
    QLabel *lb_trueName;
    QLabel *lb_sex;
    QLabel *lb_registerTime;
    QLabel *lb_onlineTime;
    QLabel *lb_motto;
    QLabel *lb_major;
    QLabel *lb_contactWay;
    QLabel *lb_permission;
    QLabel *lb_password;
    QLabel *lb_member;

    QLineEdit *lb_e_userName;
    QLineEdit *le_trueName;
    QComboBox *cb_sex;
    QLineEdit *lb_e_registerTime;
    QLineEdit *lb_e_onlineTime;
    QLineEdit *le_motto;
    QLineEdit *le_major;
    QLineEdit *le_contactWay;
    QLineEdit *lb_e_permission;
    QComboBox *cb_member;

    MyServer *m_myServer;

    void setUnEdit();
    void setToEdit();

signals:
    void SignalToSwitchTool(int);
    void SignalToDeleteUser();
};

#endif // USERWIDGET_H
