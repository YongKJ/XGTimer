#include "user.h"

User::User()
{
    init();
}

User::User(const QString &userName, const QString &password)
{
    init();
    initUser(userName,password);
}

User::User(const QString &userName, const QString &trueName, const int &headImageProperty, const int &permit)
{
    init();
    m_userName = userName;
    m_trueName = trueName;
    m_headImageProperty = headImageProperty;
    m_permit = permit;
}

void User::init()
{
    m_userName = "";
    m_password = "";
    m_newPassword = "";
    m_nickName = "";
    m_trueName = "";
    m_schoolName = "";
    m_schoolNumber = "";
    m_phoneNumber = "";
    m_subjectName = "";
    m_sex = 0;
    m_permit = 0;
    m_lastTime = QDateTime::currentDateTime();
    m_motto = "时间是你重要的财富";
    m_headImageProperty = 0;
    m_autoLogin = false;
    m_remberPassword = false;
    m_closeStyle = 1;
    m_softStyle = 1;
    m_updateStyle = 0;
    m_member = 0;
    memset(m_week.day,0,sizeof(m_week.day));
}
void User::initUser(const QString &userName, const QString &password, const int &permit)
{
    init();
    m_userName = userName;
    m_password = password;
    m_permit = permit;
}
void User::initPersonalMessage(const QString &schoolNumber,const QString &phoneNumber)
{
    m_schoolNumber = schoolNumber;
    m_phoneNumber = phoneNumber;
}

void User::initBaseMessage(const QString &userName, const QString &trueName, const int &headImageProperty,const int &permit)
{
    init();
    m_userName = userName;
    m_trueName = trueName;
    m_headImageProperty = headImageProperty;
    m_permit = permit;
}

void User::setUserName(const QString &userName)
{
    m_userName = userName;
}
void User::setPassword(const QString &password)
{
    m_password = password;
}

void User::setSchoolNumber(const QString &schoolNumber)
{
    m_schoolNumber = schoolNumber;
}
void User::setPhoneNumber(const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

void User::setNickName(const QString &nickName)
{
    m_nickName = nickName;
}

void User::setTrueName(const QString &trueName)
{
    m_trueName = trueName;
}

void User::setMotto(const QString &motto)
{
    m_motto = motto;
}

void User::setSex(const int &sex)
{
    m_sex = sex;
}

void User::setClassName(const QString &className)
{
    m_className = className;
}
void User::setSubjectName(const QString &subjectName)
{
    m_subjectName = subjectName;
}
void User::setSchoolName(const QString &schoolName)
{
    m_schoolName = schoolName;
}

void User::setLastTime(const QDateTime &lastTime)
{
    m_lastTime = lastTime;
}

void User::setRegisterTime(const QDateTime &registerTime)
{
    m_registerTime = registerTime;
}

void User::setHeadImage(const QPixmap &headImage)
{
    m_headImage = headImage;
}

void User::setWeek(const Week &week)
{
    m_week = week;
}

void User::setWeek(const int day[])
{
    for(int i=1;i<8;i++)
    {
        m_week.day[i] = day[i];
    }
    m_week.day[0] = 0;
}

QString User::getUserName()const
{
    return m_userName;
}
QString User::getPassword()const
{
    return m_password;
}

QString User::getSchoolNumber()const
{
    return m_schoolNumber;
}
QString User::getPhoneNumber()const
{
    return m_phoneNumber;
}

QString User::getNickName() const
{
    return m_nickName;
}

QString User::getTrueName() const
{
    return m_trueName;
}

QString User::getMotto() const
{
    return m_motto;
}

int User::getSex() const
{
    return m_sex;
}

int User::getPermit() const
{
    return m_permit;
}

QString User::getClassName()const
{
    return m_className;
}
QString User::getSubjectName()const
{
    return m_subjectName;
}
QString User::getSchoolName()const
{
    return m_schoolName;
}

QDateTime User::getLastTime()const
{
    return m_lastTime;
}

QDateTime User::getRegisterTime() const
{
    return m_registerTime;
}

QString User::getRegisterTimeString() const
{
    return m_registerTime.toString("yyyy-MM-dd hh:mm:ss");
}

QString User::getLastTimeString() const
{
    return m_lastTime.toString("yyyy-MM-dd hh:mm:ss");
}
QPixmap User::getHeadImage()const
{
    return m_headImage;
}

int User::getNowOfWeekDay() const
{
    return QDate::currentDate().dayOfWeek();
}

int User::getWeekTime()const
{
    int total = 0;
    for(int i=1;i<=7;i++){
        total += m_week.day[i];
    }

    return total;
}

int User::getTodayTime() const
{
    return m_week.day[getNowOfWeekDay()];
}

int User::getTempTime() const
{
    return m_week.day[0];
}

QString User::getWeekTimeString()
{
    QString onlineTime;
    onlineTime = QString::number(getWeekTime()/3600)+" 小时 "+
                 QString::number(getWeekTime()%3600/60)+" 分钟 "+
                 QString::number(getWeekTime()%60)+" 秒";
    return onlineTime;
}

void User::operator_addFiveSecond()
{
    if(!isVaild())
    {
        return;
    }

    QDate date;
    int dayOfWeek = date.currentDate().dayOfWeek();

    m_week.day[dayOfWeek]+=5;

    return;
}

Week User::getWeek() const
{
    return m_week;
}

bool User::isVaild()const
{
    if(m_userName.trimmed().isEmpty())
    {
        return false;
    }
    return true;
}

bool User::getAutoLogin() const
{
    return m_autoLogin;
}

void User::setAutoLogin(const bool &autoLogin)
{
    m_autoLogin = autoLogin;
}

bool User::getRemberPassword() const
{
    return m_remberPassword;
}

int User::getCloseStyle() const
{
    return m_closeStyle;
}

int User::getSoftStyle() const
{
    return m_softStyle;
}

QString User::getHeadImagePath()const
{
    if(getHeadImageProperty()>IMAGECOUT||getHeadImageProperty()==0)
    {
        return "://image/softImage//softIcon.png";
    }
    return QString(QString(IM_HEADSYSTEM)+"image_"+QString::number(getHeadImageProperty())+".jpg");
}

QString User::getHeadImagePath(const unsigned int &property)
{
    if(property>IMAGECOUT||property==0)
    {
        return "://image/softImage//softIcon.png";
    }
    return QString(QString(IM_HEADSYSTEM)+"image_"+QString::number(property)+".jpg");
}

int User::getUpdateStyle() const
{
    return m_updateStyle;
}

void User::setUpdateStyle(const int &updateStyle)
{
    m_updateStyle = updateStyle;
}

int User::getMember() const
{
    return m_member;
}

void User::setMember(const int &member)
{
    m_member = member;
}

void User::setRemberPassword(const bool &remberPassword)
{
    m_remberPassword = remberPassword;
}

void User::setCloseStyle(const int &closeStyle)
{
   m_closeStyle = closeStyle;
}

void User::setSoftStyle(const int &softStyle)
{
    m_softStyle = softStyle;
}

void User::setUserMessage(const User &user)
{
    m_headImageProperty = user.getHeadImageProperty();
    m_subjectName = user.getSubjectName();
    m_motto = user.getMotto();
    m_phoneNumber = user.getPhoneNumber();
    m_sex = user.getSex();
    m_trueName = user.getTrueName();
    m_schoolNumber = user.getSchoolNumber();
    m_nickName = user.getNickName();
}

QString User::getNewPassword() const
{
    return m_newPassword;
}

int User::getHeadImageProperty() const
{
    return m_headImageProperty;
}

void User::setHeadImageProperty(const unsigned int &headImageProperty)
{
    m_headImageProperty = headImageProperty;
}

void User::setNewPassword(const QString &newPassword)
{
    m_newPassword = newPassword;
}
