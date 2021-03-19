#include "tool.h"

Tool::Tool()
{

}

void Tool::sleep(const unsigned int &msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

QPoint Tool::ScreenCenter(const QRect &rect)
{
    QRect screenRect = QApplication::desktop()->screenGeometry();
    return QPoint(screenRect.width()/2-rect.width()/2,screenRect.height()/2-rect.height()/2);
}

QFont Tool::Font(const int &size, const bool &bold)
{
    QFont font;
    font.setFamily("方正兰亭黑简体");
    font.setBold(bold);
    font.setPixelSize(size);
    return font;
}

bool Tool::compareValue(const GuestBook &book1, const GuestBook &book2)
{
    if(book1.getProerty()==book2.getProerty())
    {
        return book1.getDayOfLeave()<book2.getDayOfLeave()?false:true;
    }
    return book1.getProerty()<book2.getProerty()?false:true;
}

QString Tool::getVersionText()
{
    return QString(SOFTWARE_VERSOIN).split("@").at(0);
}

QList<QString> Tool::getLocalMac()
{
    QProcess cmd_pro;
    QString cmd_str = QString("arp -a");

    cmd_pro.start("C://Windows//system32//cmd.exe",QStringList()<<"/c"<<cmd_str);
    cmd_pro.waitForStarted();
    cmd_pro.waitForFinished();
    QByteArray bytes = cmd_pro.readAllStandardOutput();
    QTextCodec * pTextC = QTextCodec::codecForName("System");

    QString result = pTextC->toUnicode(bytes).replace(QRegExp("动态"),"----");
    result = result.replace(QRegExp("[^0-9|a-z|A-Z-]"),"");
    QString pattern("([A-Fa-f0-9]{2}-){5}[A-Fa-f0-9]{2}[-]{4}");
    QRegExp rx(pattern);
    QList<QString> macs;
    int pos = 0;
    while(pos = result.indexOf(rx,pos+1),pos>=0)
    {
//        qDebug() << rx.cap();
        macs.append(rx.cap());
    }
    return macs;
}
