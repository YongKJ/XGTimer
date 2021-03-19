#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class BottomWidget;
}

class BottomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BottomWidget(QWidget *parent = 0);
        ~BottomWidget();

        QPushButton *bt_main;
        QPushButton *bt_show;
        QPushButton *bt_person;
        QPushButton *bt_member;
        QPushButton *bt_about;

        void initLayout();
        void setPushButtonFocus(QPushButton *bt);
        void setPushButtonUnfocus(QPushButton *bt);

private:
    Ui::BottomWidget *ui;
};

#endif // BOTTOMWIDGET_H
