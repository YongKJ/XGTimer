#ifndef SHOWBOARDWIDGET_H
#define SHOWBOARDWIDGET_H

#include <QDebug>

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QWheelEvent>

#define N 100

namespace Ui {
class ShowBoardWidget;
}

class ShowBoardWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ShowBoardWidget(QWidget *parent = 0);
    ~ShowBoardWidget();

    void initData();
    void initLayout();
    void initConnect();

    void getLBSum(const int num);
    void setLBText();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::ShowBoardWidget *ui;

    bool drag_wheelPressedFlag;
    bool drag_mousePressedFlag;
    QPoint drag_beginPoint;

    QLabel *lb_labelBoard[N];

    QPoint currentPos[N];

    QPoint currentPosHead;
    QPoint currentPosTail;

    int m_LBSum;
};

#endif // SHOWBOARDWIDGET_H
