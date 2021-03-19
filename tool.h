#ifndef TOOL_H
#define TOOL_H

/*【非框架】工具类：存放工具函数
 * 创建者：杨容光
 * 最后更新：2018-02-06
 * 该类的主要功能：
 * 1.仅作为承载框架以外的第三方工具函数
 */

#include <QApplication>
#include <QTime>
#include <QRect>
#include <QDesktopWidget>
#include "guestbook.h"
#include <QProcess>
#include <QDebug>
#include <QTextCodec>

#define SOFTWARE_SETUP "2017-12-18"
#define SOFTWARE_VERSOIN "V 1.1.0@201-03-15"

class Tool
{
private:
    Tool();
public:
    //延迟执行
    static void sleep(const unsigned int &msec);
    //给予软件的边长返回软件出现在主窗口中央的坐标
    static QPoint ScreenCenter(const QRect &rect);
    static QFont Font(const int &size = 14,const bool &bold=true);
    static bool compareValue(const GuestBook &book1, const GuestBook &book2);
    static QString getVersionText();
    static QList<QString> getLocalMac();
};

#endif // TOOL_H
