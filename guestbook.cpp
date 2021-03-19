#include "guestbook.h"

User GuestBook::getSendUser() const
{
    return m_sendUser;
}

void GuestBook::setSendUser(const User &sendUser)
{
    m_sendUser = sendUser;
}

User GuestBook::getReceiveUser() const
{
    return m_receiveUser;
}

void GuestBook::setReceiveUser(const User &receiveUser)
{
    m_receiveUser = receiveUser;
}

int GuestBook::getProerty() const
{
    return m_proerty;
}

int GuestBook::getType() const
{
    return m_type;
}

void GuestBook::setProerty(int proerty)
{
    m_proerty = proerty;
}

long GuestBook::getId() const
{
    return m_id;
}

void GuestBook::setId(long id)
{
    m_id = id;
}

QString GuestBook::getTitle() const
{
    return m_title;
}

void GuestBook::setTitle(const QString &title)
{
    m_title = title;
}

QString GuestBook::getText() const
{
    return m_text;
}

void GuestBook::setText(const QString &text)
{
    m_text = text;
}

void GuestBook::setType(const int &type)
{
    m_type = type;
}

QDateTime GuestBook::getDayOfLeave() const
{
    return m_dayOfLeave;
}

QString GuestBook::getDateNotTimeDay()
{
    return "";
}

QString GuestBook::getDateNotTime()
{
    return "";
}

QString GuestBook::getDateNotYear()const
{
    return m_dayOfLeave.toString("yy-MM-dd hh:mm:ss");
}

QString GuestBook::getDate()
{
    return m_dayOfLeave.toString("yyyy-MM-dd");
}

QString GuestBook::getProertyString() const
{
    switch(m_proerty)
    {
    case GUEST_PUBLIC:
        return "留言";
        break;
    case GUEST_INFORM:
        return "公告";
        break;
    case GUEST_PLAN:
        return "计划";
        break;
    }
    return "未定义";
}

QString GuestBook::PropertyString(const int &property)
{
    switch(property)
    {
    case GUEST_PUBLIC:
        return "留言";
        break;
    case GUEST_INFORM:
        return "公告";
        break;
    case GUEST_PLAN:
        return "计划";
        break;
    }
    return "未定义";
}

void GuestBook::setDayOfLeave(const QDateTime &dayOfLeave)
{
    m_dayOfLeave = dayOfLeave;
}

int GuestBook::getRead() const
{
    return m_read;
}

int GuestBook::getLove() const
{
    return m_love;
}

void GuestBook::setRead(const int  &read)
{
    m_read = read;
}

void GuestBook::setLove(const int &love)
{
    m_love = love;
}

void GuestBook::setVariantMap(QVariantMap map)
{
    setId(map["id"].toInt());
    setProerty(map["property"].toInt());
    m_sendUser.initBaseMessage(
                map["sender"].toString(),
                map["trueName"].toString(),
                map["headImage"].toInt(),
                map["permit"].toInt()
            );
    m_receiveUser.setUserName(map["receiver"].toString());
    setText(map["text"].toString());
    setTitle(map["title"].toString());
    setDayOfLeave(map["dateTime"].toDateTime());
    setRead(map["read"].toInt());
    setLove(map["love"].toInt());
    setType(map["guestType"].toInt());
}

void GuestBook::verify()
{
    //暂不支持匿名发送者
    if(!m_sendUser.isVaild()) return;
    switch (m_proerty) {
    case GUEST_PUBLIC:
        //nothing to do
        break;
    case GUEST_INFORM:
        break;
    case GUEST_PLAN:
        break;
    default:
        m_proerty = GUEST_PUBLIC;
        break;
    }
}

bool GuestBook::isValid() const
{
    if(!m_sendUser.isVaild()) return false;

    switch(m_proerty)
    {
    case GUEST_PUBLIC:
        //nothing to do
        break;
    case GUEST_INFORM:
        if(m_sendUser.getPermit()<3)
        {
            return false;
        }
        break;
    case GUEST_PLAN:
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool GuestBook::isNewMessage() const
{
    return m_newMessage;
}

GuestBook::GuestBook()
{
    init();
}

void GuestBook::init()
{
   m_sendUser.init();
   m_receiveUser.init();

    m_proerty = GUEST_PUBLIC;
    m_id = 0;

    m_title= "日常灌水";
    m_text = "";

    m_read = 0;
    m_love = 0;
    m_newMessage = true;
    m_type = 0;
}
