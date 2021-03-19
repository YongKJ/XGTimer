#ifndef GUESTBOOK_H
#define GUESTBOOK_H

#include "user.h"
#include <QVariantMap>


/*【框架】留言类：杨容光负责，如有更改，请通知
 * 最后更改时间：2018-02-04
 */

/*留言属性:（括号内部的功能由[自动转化接口函数verify]完成)
 * 0,公开（默认）
 * 2,公告，进管理员可以发送（非管理员自动转化为公开）
 * 4，仅个人可见，内容直接保存至本地，转移电脑将无法看到
 * 5，仅朋友可见【不推荐使用】（预留接口参数，自动转换为公开)
 */
enum{GUEST_PUBLIC,
     GUEST_PLAN,
     GUEST_INFORM,
    };

class GuestBook
{
private:
    //留言人信息
    User m_sendUser;
    User m_receiveUser;
    //留言属性
    int m_proerty;
    int m_type;
    //留言包唯一识别码，唯有同步到服务器的留言才能拥有此项属性
    long m_id;
    //留言标题和内容
    QString m_title;
    QString m_text;
    //留言时间
    QDateTime m_dayOfLeave;

    //阅读属性，仅在本地有效，不会上传服务器,（暂verify无法影响)
    int m_read;
    int m_love;

    bool m_newMessage;

public:
    GuestBook();    
    //接口：初始化全部内容，将留言包初始化为初态
    void init();
    //接口：返回数据包
    User getSendUser() const;
    User getReceiveUser() const;
    int getProerty() const;
    int getType()const;
    long getId() const;
    QString getTitle() const;
    QString getText() const;
    //日期接口
    QDateTime getDayOfLeave() const;
    QString getDateNotTimeDay();
    QString getDateNotTime();
    QString getDateNotYear() const;
    QString getDate();
    QString getProertyString()const;
    static QString PropertyString(const int &property);
    int getRead() const;
    int getLove() const;
    /*设置接口---------------------------------------*/

    void setSendUser(const User &sendUser);
    void setReceiveUser(const User &receiveUser);
    void setProerty(int proerty = GUEST_PUBLIC);
    //设置id接口：【不推荐使用】
    void setId(long id);
    void setTitle(const QString &title);
    void setText(const QString &text);
    void setType(const int &type );
    //设置留言接口1：直接设置留言的时间，不推荐使用
    void setDayOfLeave(const QDateTime &dayOfLeave);
    //设置留言接口2：自动将留言时间设置为当前的时间，推荐使用
    void setDayOfLeave();
    void setRead(const int &read);
    void setLove(const int &love);
    void setVariantMap(QVariantMap map);
    /*状态接口----------------------------------------*/

    //自动校验接口，可以检测当前留言内容并自动转化，注意：暂不支持匿名发送者
    void verify();
    bool isValid()const;
    bool isNewMessage()const;


};

#endif // GUESTBOOK_H
