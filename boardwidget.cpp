#include "boardwidget.h"
#include "ui_boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);
    setFixedSize(151,182);

    initData();
    initLayout();
    initConnect();
}

BoardWidget::~BoardWidget()
{
    delete ui;
}

void BoardWidget::initData()
{

}

void BoardWidget::initLayout()
{
    // 无边框设置
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    lb_title = new QLabel(this);
    lb_text = new QLabel(this);

    lb_title->setGeometry(width()-130,10,120,30);
    lb_text->setGeometry(width()-120,40,100,130);

    lb_title->setAlignment(Qt::AlignCenter);
    lb_text->setAlignment(Qt::AlignCenter);

    lb_title->setWordWrap(true);
    lb_text->setWordWrap(true);

    lb_title->setStyleSheet("QLabel{background:transparent}");
    lb_text->setStyleSheet("QLabel{background:transparent}");

}

void BoardWidget::initConnect()
{
    connect(this,SIGNAL(clicked2()),this,SLOT(slot_test()));
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/image/callboard_1.png"));

    event->accept();
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
        {
            emit clicked2();
        }
    }
}

void BoardWidget::slot_test()
{
    TipWidget edit(0,lb_text->text(),32);
    if (edit.isEdit() == true)
    {
        if(edit.getEditText().length() > 30)
        {
            lb_text->setText(" "+edit.getEditText().mid(0,30)+"...");
        }
        else
        {
            lb_text->setText(" "+edit.getEditText());
        }
    }
    else
    {
        return;
    }

}
