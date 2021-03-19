#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QDebug>
#include <QCloseEvent>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include "tipwidget.h"
#include "user.h"
#include <QCheckBox>
#include <QButtonGroup>
#include <QPaintEvent>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>
#include "myserver.h"


namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = 0);
    ~RegisterWidget();

    void initData();
    void initLayout();
    void initConnect();

    void SetServer(MyServer *server);

protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::RegisterWidget *ui;

    QLineEdit *le_userName;
    QLineEdit *le_password;
    QLineEdit *le_againPassword;
    QLineEdit *le_trueName;
    QLineEdit *le_phoneNumber;

    QTextBrowser *tb_protocol;

    QCheckBox *chb_protocol;
    QCheckBox *chb_male;
    QCheckBox *chb_female;

    QButtonGroup *bg_sex;

    QPushButton *bt_register;

    MyServer *m_myServer;


    void resetLineEditText();

public slots:
    void slot_check();
    void Server_register_slot(const QString &status,const QString &message);

    void slot_protocol();

signals:
    void SignalToCloseRegister();
};

#endif // REGISTERWIDGET_H
