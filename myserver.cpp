#include "myserver.h"

MyServer::MyServer()
{
    init();
}

void MyServer::login(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "username="+user.getUserName()+"&password="+user.getPassword()+"&method=user";
    var = APP_SERVER + var;
    request.setUrl(QUrl(var));
    qDebug()<<var;
    manager->get(request);

}

void MyServer::requestStatistic(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "username="+user.getUserName()+"&password="+user.getPassword()+"&method=statistic";
    var = APP_SERVER + var;
    request.setUrl(QUrl(var));
    manager->get(request);
}

void MyServer::updateTime(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "username="+user.getUserName()+"&password="+user.getPassword()+"&method=updateTime&seconds="+QString::number(user.getWeek().day[user.getNowOfWeekDay()]);
    var = APP_SERVER + var;
    request.setUrl(QUrl(var));
    manager->get(request);
}



void MyServer::updateUser(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "username="+user.getUserName()+"&password="+user.getPassword()
            +"&method=updateUser"
            +"&nickName="+user.getNickName()
            +"&trueName="+user.getTrueName()
            +"&sex="+QString::number(user.getSex())
            +"&motto="+user.getMotto()
            +"&phone="+user.getPhoneNumber()
            +"&schoolNumber="+user.getSchoolNumber()
            +"&headImage="+QString::number(user.getHeadImageProperty())
            +"&subjectName="+user.getSubjectName()
            +"&member="+QString::number(user.getMember());
    var = APP_SERVER + var;
    request.setUrl(QUrl(var));
    manager->get(request);
}

void MyServer::userRegister(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "userName="+user.getUserName()+"&password="+user.getPassword()
            +"&method=register"
            +"&trueName="+user.getTrueName()
            +"&sex="+QString::number(user.getSex())
            +"&phone="+user.getPhoneNumber();
    var = APP_Register + var;
    request.setUrl(QUrl(var));
    manager->get(request);
}

void MyServer::requestMac()
{
    QNetworkRequest request;

    QString var;
    var += "method=getStudioMac";
    var = APP_Index + var;
    request.setUrl(QUrl(var));
    manager->get(request);
}

void MyServer::requestVersion()
{
    QNetworkRequest request;

    QString var;
    var += "method=version";
    var = APP_Register + var;
    request.setUrl(QUrl(var));
    manager->get(request);
}

void MyServer::answer(QNetworkReply *reply)
{
    QByteArray byteArray;
    byteArray = reply->readAll();
    if(byteArray.isEmpty())
    {
        emit sError("请检查网络");
        reply->deleteLater();
        return;
    }
    else
    {
        QJsonDocument jsonDoc;
        jsonDoc = QJsonDocument::fromJson(byteArray);

        if(jsonDoc.isNull()) return;
        QVariantMap result = jsonDoc.toVariant().toMap();
        QString method = result["method"].toString();

        if(result["status"].toString()=="400"&&method!="register"&&method!="getStudioMac")
        {
            emit sError(result["message"].toString());
            reply->deleteLater();
            return;
        }

        if(method=="version")
        {
            emit sVersion(result["version"].toString(),result["downloadUrl"].toString());
        }
        else if(method=="register")
        {
            emit sRegister(result["status"].toString(),result["message"].toString());
        }
        else if(method=="getStudioMac")
        {
            QVariantList list = result["list"].toList();
            QList<QString>macList;
            foreach (QVariant v, list) {
                macList.append(v.toString());
            }
            emit sMac(macList);
        }
        else if(method=="user")
        {
            QVariantMap map = result["user"].toMap();
            Week week;
            User user;
            user.initUser(map["userName"].toString(),map["password"].toString(),map["permit"].toInt());
            user.initPersonalMessage(map["schoolNumber"].toString(),map["phone"].toString());
            user.setClassName(map["class"].toString());
            user.setSchoolName(map["schoolName"].toString());
            user.setSubjectName(map["profess"].toString());
            user.setSex(map["sex"].toInt());
            user.setMotto(map["motto"].toString());
            user.setTrueName(map["trueName"].toString());
            user.setNickName(map["nickName"].toString());
            user.setHeadImageProperty(map["headImage"].toInt());
            user.setMember(map["member"].toInt());
            user.setRegisterTime(QDateTime::fromString(map["createtime"].toString(),"yyyy-MM-dd hh:mm:ss"));

            QVariantList list = map["list"].toList();
            week.day[1] = list[1].toInt();
            week.day[2] = list[2].toInt();
            week.day[3] = list[3].toInt();
            week.day[4] = list[4].toInt();
            week.day[5] = list[5].toInt();
            week.day[6] = list[6].toInt();
            week.day[7] = list[0].toInt();
            week.day[0] = map["total"].toString().toInt();
            user.setWeek(week);

            emit sLogin(user);
        }
        else if(method=="statistic")
        {
            QVariantList list = result["list"].toList();
            StatisticUser bag;

            bag.statisticPeople = list.size();
            Week week;
            for(int i=0;i<bag.statisticPeople;i++)
            {
                QVariantMap map = list.at(i).toMap();
                bag.user[i].setUserName(map["userName"].toString());
                week.day[0] = map["total"].toInt();
                bag.user[i].setWeek(week);

                bag.user[i].setHeadImageProperty(map["headImage"].toInt());

                bag.user[i].setTrueName(map["trueName"].toString());
                bag.user[i].setNickName(map["nickName"].toString());

                bag.user[i].setPhoneNumber(map["phone"].toString());
                bag.user[i].setSex(map["sex"].toInt());

                bag.user[i].setMotto(map["motto"].toString());
                bag.user[i].setSubjectName(map["subjectName"].toString());

             }
            emit sStatistic(bag);
        }
        else if(method=="updateTime")
        {
            emit sUpdate(result["message"].toString());
        }
        else if(method=="updateUser")
        {
            QVariantMap map = result["user"].toMap();
            User user;
            user.initUser(map["userName"].toString(),map["password"].toString(),map["permit"].toInt());
            user.initPersonalMessage(map["schoolNumber"].toString(),map["phone"].toString());
            user.setClassName(map["class"].toString());
            user.setSchoolName(map["schoolName"].toString());
            user.setSubjectName(map["profess"].toString());
            user.setSex(map["sex"].toInt());
            user.setMotto(map["motto"].toString());
            user.setTrueName(map["trueName"].toString());
            user.setNickName(map["nickName"].toString());
            user.setHeadImageProperty(map["headImage"].toInt());
            user.setMember(map["member"].toInt());
            user.setRegisterTime(QDateTime::fromString(map["createtime"].toString(),"yyyy-MM-dd hh:mm:ss"));

            emit sUpdateUser(user);
            emit sUpdate(result["message"].toString());
        }

    }
    reply->deleteLater();
}

void MyServer::init()
{
    manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(answer(QNetworkReply*)));
}


