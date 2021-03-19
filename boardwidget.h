#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QEvent>
#include "tipwidget.h"

#define N 100

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QDialog
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = 0);
    ~BoardWidget();

    void initData();
    void initLayout();
    void initConnect();

    QLabel *lb_title/*[N]*/;
    QLabel *lb_text/*[N]*/;

private:
    Ui::BoardWidget *ui;


    //重绘函数
    void paintEvent(QPaintEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event);

public slots:
    void slot_test();

signals:
    void clicked2();

};

#endif // BOARDWIDGET_H
