#ifndef TIPWIDGET_H
#define TIPWIDGET_H

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include "tool.h"

#define HLINE 250
#define VLINE 150
#define MAXLENGTH 200

namespace Ui {
class TipWidget;
}

class TipWidget : public QDialog
{
    Q_OBJECT

public:
//    explicit TipWidget(QWidget *parent = 0);
    TipWidget(QWidget *parent, const QString &title, const QString &text, const int &type);
    TipWidget(QWidget *parent, const QString &text, const int &type);
    ~TipWidget();

    bool editState;

    void initData();
    void initLayout();
    void initConnect();

    bool isEdit();
    QString getEditText();
    void setEditText(QString text);

private:
    Ui::TipWidget *ui;

    QLabel *lb_title;
    QLabel *lb_text;
    QPushButton *bt_close;
    QTextEdit *te_edit;

    //实现无边框移动数据变量
    QPoint drag_beginPoint;
    bool drag_mousePressedFlag;


    void initTip();
    void initEdit();
    void setTitle(const QString &title);
    void setTipText(const QString &text);

    void setType(const int type);
    void setType11();
    void setType12();
    void setType32();
    void setTypeOther();

protected:
    //实现无边框三函数
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //重绘函数
    void paintEvent(QPaintEvent *event);

public slots:
    void slot_editYes();
    void slot_editNo();
    void slot_maxLength();

};

#endif // TIPWIDGET_H
