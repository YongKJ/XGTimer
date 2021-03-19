#ifndef USER_H
#define USER_H

#include<QString>
#include<QTime>
#include<QPixmap>
#include<String.h>
class User;
/*
 * 【框架】用户类：杨容光负责更新，若有改动，请通知。
 * 最后更新日期：2018-02-06
 * 本类的承担的任务有：
 * 1.作为框架的接口参数，提供承载信息的数据结构
 * 2.作为特定的存储数据的数据结构
 * 3.仅提供基础逻辑性检测
 * 4.如若提供可以进行内部数据或状态修改的接口，该接口只能在外部手动调用
 */
#define IMAGECOUT 29
#define IM_SOFTSYSTEM ":/image/softImage/system/"
#define IM_SOFTDETAILS ":/image/softImage/detials/"
#define IM_SOFTFRAMEWORK ":/image/softImage/framework/"
#define IM_HEADSYSTEM ":/image/headImage/system/"
enum{ILLEGAL=-2,SLOPOVER=-1,FAIL = 0,SUCCEED = 1,AVOID = 2,STANDBY = 3};

/*
 *一周七天结构体
 *注意：星期一下标为1，星期天下标为7，有效下标1-7（待定)
 * 一周时间从星期一开始，星期天结束
 * 0为无效下标
 */
struct Week
{
    int day[8];
};

class User
{
public:
    User();
    User(const QString &userName,const QString &password);
    User(const QString &userName, const QString &trueName, const int &headImageProperty,const int &permit = 0);
    //初始化用户所有信息，将其全部初始化为初态
    void init();

    //初始化设置用户信息
    void initUser(const QString &userName,const QString &password,const int &permit = 0);
    void initPersonalMessage(const QString &schoolNumber,const QString &phoneNumber);
    void initBaseMessage(const QString &userName,const QString &trueName,const int &headImageProperty,const int &permit = 0);

    /*设置用户的核心信息--------------------------------------*/
    void setUserName(const QString &userName);
    void setPassword(const QString &password);
    /*设置用户的核心个人信息--------------------------------------*/
    void setSchoolNumber(const QString &schoolNumber);
    void setPhoneNumber(const QString &phoneNumber);
    void setTrueName(const QString &trueName);
    /*设置用户的普通个人信息--------------------------------------*/
    void setNickName(const QString &nickName);
    //设置用户个人格言
    void setMotto(const QString &motto);
    void setSex(const int &sex);

    /*设置用户的非必须个人信息--------------------------------------*/
    void setClassName(const QString &className);
    void setSubjectName(const QString &subjectName);
    void setSchoolName(const QString &schoolName);

    void setNewPassword(const QString &newPassword);
    void setHeadImage(const QPixmap &headImage);
    void setHeadImageProperty(const unsigned int &headImageProperty);
    /*设置用户状态信息，注意：该类信息为非用户个人信息--------------------------------------*/
    void setWeek(const Week &week);
    void setWeek(const int day[]);
    void setLastTime(const QDateTime &lastTime);
    void setRegisterTime(const QDateTime &registerTime);

    void setAutoLogin(const bool &autoLogin);
    void setRemberPassword(const bool &remberPassword);
    void setCloseStyle(const int &closeStyle);
    void setSoftStyle(const int &softStyle);
    //仅填入用户的个人信息
    void setUserMessage(const User &user);
    /*获取用户信息----------------------------------------------*/
    QString getUserName()const;
    QString getPassword()const;

    QString getSchoolNumber()const;
    QString getPhoneNumber()const;

    QString getNickName()const;
    QString getTrueName()const;
    QString getMotto()const;

    QString getClassName()const;
    QString getSubjectName()const;
    QString getSchoolName()const;
    //获取用户权限
    int getPermit()const;
    int getSex()const;
    QDateTime getLastTime()const;
    QDateTime getRegisterTime()const;
    QString getRegisterTimeString()const;
    QString getLastTimeString()const;
    QString getNewPassword() const;



    /*图像简易说明：-------------------------------------
     * 属性：0，使用自定义图像；非0，使用客户端自带图像
     * 使用自定义图像不上传服务器，从本地上传至headImage中,系统自带图像不加载直接使用
     */
    QPixmap getHeadImage()const;
    int getHeadImageProperty() const;

    int getNowOfWeekDay()const;

    //得到用户本周的总时间
    int getWeekTime()const;
    int getTodayTime()const;
    int getTempTime()const;
    QString getWeekTimeString();
    //给用户的时间增加五秒
    void operator_addFiveSecond();

    //得到用户一周个人信息结构体，里面存储了一周七天的时间
    Week getWeek() const;

    //判断当前用户是否有效
    bool isVaild()const;   

    bool getAutoLogin() const;
    bool getRemberPassword() const;
    int getCloseStyle()const;
    int getSoftStyle()const;
    QString getHeadImagePath() const;
    static QString getHeadImagePath(const unsigned int &property);
    int getUpdateStyle() const;
    void setUpdateStyle(const int &updateStyle);

    int getMember() const;
    void setMember(const int &member);

private:
    QString m_userName;
    QString m_password;

    QString m_nickName;
    QString m_trueName;

    QString m_motto;
    int m_sex;
    int m_permit;

    QString m_schoolNumber;
    QString m_phoneNumber;

    QString m_className;
    QString m_subjectName;
    QString m_schoolName;
    QDateTime m_registerTime;
    QDateTime m_lastTime;

    unsigned int m_headImageProperty;
    QPixmap m_headImage;


    Week m_week;

    QString m_newPassword;

    int m_member;

    //软件用户信息仓库
    bool m_autoLogin;
    bool m_remberPassword;
    int m_closeStyle;
    int m_softStyle;
    int m_updateStyle;
};

//用户统计信息包
struct StatisticUser
{
    //统计总人数
    int statisticPeople;
    //统计信息，下标从0开始
    User user[50];
};

#endif // USER_H
