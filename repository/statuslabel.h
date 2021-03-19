#ifndef STATUSLABEL_H
#define STATUSLABEL_H

#include <QObject>
#include <QLabel>
#include <QTimer>

class StatusLabel : public QLabel
{
        Q_OBJECT
public:
    StatusLabel(QWidget *parent = 0);
    ~StatusLabel();

    void ShowMessage(const QString &text,const unsigned int &msec = 200);
    void ShowImage(const QPixmap &image,const unsigned int &msec =200);
    void setMsec(const unsigned int &getMsec);
    int getMsec() const;
public slots:

private slots:
    void Slot_TimeOUt();
    void KeepMessage();
protected:

private:
    void initData();
    void initLayout();
    void initConnect();

    QTimer *m_timer;

signals:

};

#endif // STATUSLABEL_H
