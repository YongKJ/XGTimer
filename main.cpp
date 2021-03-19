#include <windows.h>
#include "widget.h"
#include <QApplication>
#include <tipwidget.h>

//用于防止计时器被打开两次
bool isOnlyApplication()
{
    HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"XGTimer_20171218" );
    if  (GetLastError()  ==  ERROR_ALREADY_EXISTS)//如果已有互斥量存在则释放句柄并复位互斥量
    {
     CloseHandle(m_hMutex);
     m_hMutex  =  NULL;
      return  false;
    }
    return true;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    if(!isOnlyApplication())
    {
        TipWidget(0,"提示","不能重复打开计时器",11);
        return 0;
    }
    Widget w;
    w.show();
    return a.exec();
}
