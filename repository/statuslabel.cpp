#include "statuslabel.h"

StatusLabel::StatusLabel(QWidget *parent):QLabel(parent)
{
    initData();
    initLayout();
    initConnect();
}

StatusLabel::~StatusLabel()
{
    if(m_timer!= 0 )
    {
        delete m_timer;
    }
}

void StatusLabel::ShowMessage(const QString &text, const unsigned int &msec)
{
    setText(text);
    m_timer->start(msec);
}

int StatusLabel::getMsec() const
{
    return m_timer->remainingTime();
}

void StatusLabel::Slot_TimeOUt()
{
    setText("");
}

void StatusLabel::KeepMessage()
{
    m_timer->stop();
}

void StatusLabel::initData()
{
}

void StatusLabel::initLayout()
{
    m_timer = new QTimer;
    m_timer->setSingleShot(true);
}

void StatusLabel::initConnect()
{
    QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(Slot_TimeOUt()));
}

void StatusLabel::setMsec(const unsigned int &msec)
{
    m_timer->setInterval(msec);
}
