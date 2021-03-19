#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include "user.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QVariantMap>
#include "tool.h"

#define APP_SERVER "http://localhost:8000/xgtimer/public/index.php/admin/login/i?"
#define APP_Register "http://localhost:8000/xgtimer/public/index.php/admin/register/i?"
#define APP_Index "http://localhost:8000/xgtimer/public/index.php/admin/index/i?"

class MyServer:public QObject
{
    Q_OBJECT
public:
    MyServer();

    void login(const User &user);
    void requestStatistic(const User &user);
    void updateTime(const User &user);
    void updateUser(const User &user);
    void userRegister(const User &user);
    void requestMac();

    /**
     * @brief 获取版本号
     */
    void requestVersion();

public slots:
    void answer(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    void init();

signals:
    void sError(QString);
    void sLogin(const User &user);
    void sStatistic(const StatisticUser &bag);
    void sUpdate(const QString &message);
    void sUpdateUser(const User &user);
    void sRegister(const QString&,const QString&);
    void sMac(const QList<QString>&);
    void sVersion(const QString &version,const QString &downloadUrl);
};

#endif // MYSERVER_H
