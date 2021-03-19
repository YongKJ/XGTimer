#ifndef PERSONWIDGET_H
#define PERSONWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QToolTip>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QHelpEvent>
#include <QTimer>
#include "timebit.h"
#include "user.h"

namespace Ui {
class PersonWidget;
}

class PersonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PersonWidget(QWidget *parent = 0);
    ~PersonWidget();

    void setUser(User user,bool isStartPaint=true);
    void setNoUser();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::PersonWidget *ui;

    void InitData();
    void InitLayout();
    void InitConnect();

    void operator_updateShowTime(int timeLength);
    void operator_startPaintTimer();
    void setTimeLabelStyle(int time, QLabel *lb_Label);
    void setDataWeekDay(const int* const weekDay);
    void startMyTimer();
    void stopMyTimer();

    TimeBit *data_timeBit;//周总时长
    TimeBit *data_weekDay;//每天时长

    QTimer *myTimer;
    QTimer *painterTimer;

    QString s_num[10];
    bool isChosedFlag[7];
    int maxValue;
    double Timer_paintHeight;
    double labelDistance;
    double timerTime;

    QLabel *lb_text;
    QLabel *lb_hour_ten;
    QLabel *lb_hour_one;
    QLabel *lb_minute_ten;
    QLabel *lb_minute_one;

private slots:
    void slot_painterTimeOut();
};

#endif // PERSONWIDGET_H
