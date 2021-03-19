#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>
#include "user.h"
#include "tool.h"

/*【框架】标题栏类：杨容光负责更新，若有改动，请通知。
 * 最后改动日期2018-02-06
 * 本类的主要任务有：
 * 1.作为承载标题栏界面的框架
 * 2.提供标题栏上控件的公共接口
 * 3.仅作为其他第三方界面的中转接口，不会提供任何除框架界面显示以外的服务（例如：该类不存在连接服务器的情况）
 */

namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();

    QPushButton *bt_close;
    QPushButton *bt_minize;
    QPushButton *bt_setting;
    QPushButton *bt_login;

    QLabel* lb_trueName;

    void initLayout();

public slots:
    void setNoUser();
    void setUser(const User &user);
    void SetTitleText(const QString &mes);

protected:
    void mousePressEvent(QMouseEvent*event);

private:
    Ui::TitleWidget *ui;

signals:
    void rightButton(QPoint);
};

#endif // TITLEWIDGET_H
