#ifndef MENBERWIDGET_H
#define MENBERWIDGET_H

#include <QDebug>

#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
#include "user.h"

#define STANDARDS_HOURS 16
#define WHEEL_SPEED 15
#define N 100
#define START_DATE 5

namespace Ui {
class MenberWidget;
}

class MenberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenberWidget(QWidget *parent = 0);
    ~MenberWidget();

    void initData();
    void initLayout();
    void initConnect();

    void initPlace();
    void initBoard();


    //传入用户
    void setUser(const User &user);
    //传入用户统计包
    void setStatisticUser(const StatisticUser &bag);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::MenberWidget *ui;

    StatisticUser book;

    QPoint drag_beginPoint;
    QPoint currentPos[N];
    QPoint currentPosHead;
    QPoint currentPosTail;

    QLabel *lb_thisWeek;
    QLabel *lb_thisWeekDate;
    QLabel *lb_reachStandard;
    QLabel *lb_thisTime;
    QLabel *lb_totalTime;
    QLabel *lb_Board[N];
    QLabel *lb_Name[N];
    QLabel *lb_Time[N];
    QLabel *lb_HeadImage[N];
    QLabel *lb_name;
    QLabel *lb_motto;

    int m_choiceNum;
    int m_boardSum;

    int m_hours;
    int m_minute;
    int m_Hours[N];
    int m_Minute[N];

    bool drag_reachStandardFlag;
    bool drag_legalSpaceFlag;
    bool drag_wheelPressedFlag;
    bool drag_mousePressedFlag;

    bool isReachStandard();
    bool isLegalSpace();

    QDate getStartDate();
    QDate getEndDate();

    void setCurrentPos();

    int getDayOfWeek(QDate date);
    void setHoursAndMinute(int time);
    void setShowNameAndMotto(int &orderNum);


    void setBoard(StatisticUser &user);
    void setBoardSum(int sum);
    void setBoardText(StatisticUser &user);
    void setBoardTime(StatisticUser &user);

    void setReachStandardFlag(int &time);
    void setLegalSpaceFlag(QPoint point);

    void UpdateReachStandard();
    void UpdateLeftInformation();
    void UpdateLabelSpace(const int i);

    void eff_reboundMove(const int &sum);
    void eff_fixationWheel(QWheelEvent *event);

};

#endif // MENBERWIDGET_H
