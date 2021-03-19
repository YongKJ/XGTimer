#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
#include <QColor>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>
#include <QCheckBox>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QFont>
#include <QFile>
#include "registerwidget.h"
#include "tipwidget.h"
#include "tool.h"
#include <QDebug>
#include <QStandardItemModel>
#include <myserver.h>

/*【框架】登录类：
 * 最后修改日期：2018-02-06 杨容光
 * 该类的主要任务有：
 * 1.作为承载登录界面的框架
 * 2.提供登录服务的接口(所有登录的服务由此处接入）
 * 3.仅作为提供注册及设置的中转接口，对注册界面和设置界面的返回信息包不做任何检测和判断
 */

//本地数据库空间
#define LOCALSPACE 30
#define LOCALLOGINSETTINGDATABASE "XGTIMERBASE1.dat"
const int LOGINTIME = 5000;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    void initData();
    void initLayout();
    void initConnect();

    void setUnLogin();
    void setLogin(const User &user);
    void setUser(const User &user);
    User getUser() const;

    /**
     * @brief 设置服务器，用于给登录界面添加一个服务器
     * @param server
     */
    void setServer(MyServer *server);

    /*【重要接口】本地服务器接口：
     * 最后修改日期：2018-03-04
     */
    static User loadCurrentUser();

    static int saveUserSetting(const User &user);
    static User loadUserSetting(const QString &userName);

    static int setLocalDatabase(User setting[]);
    static int getLocalDatabase(User setting[]);

    static int initLoginSetting();
    static int clearLoginSetting();
    static int clearUserLoginSetting(const User &user);

    void loadComboBox();

    friend QDataStream& operator << (QDataStream &out,User &user);
    friend QDataStream& operator >> (QDataStream &in,User &user);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::LoginWidget *ui;

    bool drag_mousePressedFlag;
    QPoint drag_beginPoint;

    QTimer *myTimer;
    QProgressBar *progressBar;

    QLabel *lb_headImage;
    QComboBox *lb_userName;
    QLineEdit *lb_password;
    QPushButton *bt_login;
    QPushButton *bt_forgetPassword;
    QPushButton *bt_quickRegister;
    QPushButton *bt_close;
    QPushButton *bt_deleteLogin;
    QCheckBox *bt_rememberPassword;
    QCheckBox *bt_autoLogin;

    User Login_user;
    QStandardItemModel *m_model;

    /**
     * @brief 成功登录，更新本地的用户配置信息
     */
    void LoginUpdateUesr();

    MyServer *m_myServer;

public slots:
    void slot_login();
    void slot_deleteLogin();
    void slot_forgetPassword();
    void slot_quickRegister();

    /**
     * @brief 登录成功槽
     * @param user User数据包
     *
     */
    void slot_login_succeed(const User &user);

    /**
     * @brief 登录失败槽
     * @param message 失败信息
     */
    void slot_login_fail(const QString message);

    /**
     * @brief slot_timerOut 登录超时槽
     */
    void slot_timerOut();
    void CurrentUserChangeEvent(QString userName);
    void slot_loginView();

signals:
    void SignalToRegister();
    void SignalToUpdateAPP(QString,QString);
};

#endif // LOGINWIDGET_H
