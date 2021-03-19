#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QByteArray>
#include <QSystemTrayIcon>
#include <QDir>
#include <QMenu>
#include <QColor>
#include <QFileInfo>
#include "loginwidget.h"
#include "mainwidget.h"
#include "titlewidget.h"
#include "aboutwidget.h"
#include "settingwidget.h"
#include "bottomwidget.h"
#include "personwidget.h"
#include "showwidget.h"
#include "menberwidget.h"
#include "userwidget.h"
#include "user.h"
#include "repository/statuslabel.h"
#include "repository/imagetool.h"
#include <QProcess>
#include <QDesktopServices>
#include "myserver.h"
#include <QDesktopServices>

/** 【主框架】界面类：整个计时器的类
 * 注意：该类是所有界面类的入口，如无必要，非必要修改仅仅只能作为调试用途
 * 该类的主要任务有：
 * 1.作为承载其他界面的类的基本类
 * 2.调用各个界面类的接口实现本软件的功能
 * 3.仅实现必要的基础逻辑功能
 * 注意：除main外其他类文件不能包含widget.h
 */

namespace Ui {
class Widget;
}

enum{MAIN,SHOW,PERSON,MEMBER,SETTING,REGISTER,ABOUT,USER};

const int LEAST_UPDATETIME = 5;//最短更新时间间隔
const int AUTO_UPDATETIME = 10;//自动更新时间间隔

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //初始化函数，请勿随意调用
    void initData();
    void initLayout();
    void initConnect();

    void setManager(QNetworkAccessManager*manager);

    void UpdateCurrentUserFromUserWidget();
protected:
    //实现无边框三函数
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //重绘函数
    void paintEvent(QPaintEvent *event);
protected slots:
    void trayEvent(QSystemTrayIcon::ActivationReason reason);
public slots:
    /**
     * @brief 将软件的页面切换为首页界面
     */
    void show_mainWidget_slot();

    /**
     * @brief 将软件的页面切换为展示界面
     */
    void show_showWidget_slot();
    void show_personWidget_slot();
    void show_memberWidget_slot();

    //页面显示：关于界面槽，设置界面槽，注册界面槽
    void show_aboutWidget_slot();
    void show_settingWidget_slot();
    void show_registerWidget_slot();
    void show_loginWidget_slot();
    void show_trayWidget_slot();
    void show_userWidget_slot();

    void show_XGTimerWidget_slot();
    void minimize_XGTimerWidget_slot();
    void UpdatePage(const int &type);

    /**
     * @brief 关于登录，将软件设置为用户登录状态
     * @param user
     */
    void Login_setLoginUser(User user);

    /**
     * @brief 将软件设置为没有用户登录状态
     */
    void Login_setUnLoginUser();

    /**
     * @brief 运行自动登录事件
     * @param type
     * @param user
     */
    void Login_autoLoginEvent(int type = SUCCEED,User user = User());

    //更新用户信息
    void Update_UserTimer();

    void Update_UserSetting(const User &user);

    /**
     * @brief 更新软件
     */
    void Update_App();

    /**
     * @brief 接收服务返回的请求更新结果消息提示
     * @param type
     */
    void Server_updateMessage_slot(const QString &message);

    /**
     * @brief 服务器更新用户信息
     * @param type
     */
    void Server_updateUser_slot(const User &user);
    void Server_showGuestBook_slot(int type);

    /**
     * @brief 接收从服务器获取来的版本号以版本下载地址
     * @param type
     */
    void Server_updateAPP_slot(const QString &version,const QString &downloadUrl);

    /**
     * @brief 接收服务器返回的统计信息
     * @param bag
     */
    void Server_statistic_slot(const StatisticUser &bag);

    //时间槽
    void Timing_slot();
    void Timing_start_slot();
    void Timing_stop_slot();

    void Assist_trueNameButton_slot();

    //消息提示或选择框
    void ShowMenu(QPoint currentPos);
    void ShowTrayMenu();
    void ShowSystemMessage(const QString &title,const QString &text);
    void ShowHeadImage();
    void ShowStatusMessage(const QString &mes, const unsigned int &msec = 2000, const int type = 3);
    //更新的动画
    void startUpdateMovie();

    void SwitchImageTool(const int &type);
    void ShowImageTool(const int &headImageProperty);
    void CloseImageTool();
    void updateAPP(const QString &versoin,QString downloadUrl);

    /**
     * @brief 从本地网关中获取mac地址
     */
    void updateLocalMAC();

    /**
     * @brief 接收服务器的工作室mac地址，并更新
     * @param macList
     */
    void updateMac(const QList<QString>&macList);



private:
    Ui::Widget *ui;

    //实现无边框移动数据变量
    QPoint drag_beginPoint;
    bool drag_mousePressedFlag;

    StatusLabel *m_statusLabel[3];
    QLabel *lb_version;
    //当前页面标志
    int page_currentFlag;

    TitleWidget *titleWidget;
    BottomWidget *bottomWidget;
    MainWidget * mainWidget;
    ShowWidget *showWidget;
    PersonWidget *personWidget;
    MenberWidget *memberWidget;

    RegisterWidget *registerWidget;
    SettingWidget *settingWidget;
    AboutWidget *aboutWidget;
    UserWidget *userWidget;

    QVBoxLayout *vLayoutMain;

    QSystemTrayIcon *trayWidget;    
    QMenu *trayMenu;
    ImageTool *im_tool;

    //服务器
    MyServer *m_myServer;

    //计时系统-------------------------------------------------------
    QTimer *m_timer;
    int cycle_updateUserIntervalStatis;//循环周期，每5秒更新CurrentUser
    int cycle_updateServerIntervalStatis;//循环周期，每5分钟向服务器请求更新

    //当前登录的用户数据存放于此：（保证该份数据的唯一有效性)(其他user数据仅能作为临时存在的保留数据)
    User Login_currentUser;
    //记录登录状态
    bool Login_vaild;
    QString m_version;
    QString m_downLoadUrl;
    QList<QString> m_StudioMacList;
    QList<QString> m_LocalMAC;
    bool m_internet;
    bool b_isTimer;

    /**
     * @brief 是否已经获取了工作室的mac地址
     */
    bool b_alreadyGotStudioMac;

    /**
     * @brief 判断用户是否能够记录时间
     */
    bool isUserCanRecodeTimer();

signals:
    void SignalToSettingUpdate(User);

};

#endif // WIDGET_H
