#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "tool.h"
#include "user.h"

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

    void initDate();
    void initLayout();
    void initConnect();
public slots:
    void setUser(const User &user);
    void Update_setting_Button();

private:
    Ui::SettingWidget *ui;

    QLabel *lb_closeStyle;
    QLabel *lb_softStyle;

    QRadioButton *bt_selectCloseStyle_0;
    QRadioButton *bt_selectCloseStyle_1;

    QButtonGroup *gb_closeStyle;
    QHBoxLayout *hLayout_closeStyle;

    QLabel *lb_softStyleMessage;

    QPushButton *bt_submit;

    QLabel *lb_updateCycle;
    QComboBox *lb_updateCycleMessage_1;
    QComboBox *lb_updateCycleMessage_2;
    QComboBox *cb_update;

signals:
    void SignalToSettingUpdate(User);
};

#endif // SETTINGWIDGET_H
