#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QWidget>
#include <QDialog>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QLineEdit>
#include "user.h"
#include "tool.h"
#include "tipwidget.h"

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = 0);
    ~ChangePassword();

    void initData();
    void initLayout();
    void initConnect();

    void setUser(const User &user);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    bool check_le_oldPassword();
    bool check_le_newPassword();
    bool check_le_correctPassword();
    void slot_bt_change();
    void slot_changePassword_server(int type);

private:
    Ui::ChangePassword *ui;

    User m_user;

    bool drag_mousePressedFlag;
    QPoint drag_beginPoint;

    QPushButton *bt_close;
    QPushButton *bt_change;
    QLineEdit *le_oldPassword;
    QLineEdit *le_newPassword;
    QLineEdit *le_correctPassword;
    QLabel *lb_status_oldPassword;
    QLabel *lb_status_newPassword;
    QLabel *lb_status_correctPassword;
    QLabel *lb_image_oldPassword;
    QLabel *lb_image_newPassword;
    QLabel *lb_image_correctPassword;

    void setYesOldPassword();
    void setYesNewPassword();
    void setYesCorrectPassword();

    void setNoOldPassword();
    void setNoNewPassword();
    void setNoCorrectPassword();

signals:
    void SignalToDeleteLogin();

};

#endif // CHANGEPASSWORD_H
