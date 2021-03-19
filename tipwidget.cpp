#include "tipwidget.h"
#include "ui_tipwidget.h"



TipWidget::TipWidget(QWidget *parent,const QString &title,const QString &text,const int &type) :
    QDialog(parent),
    ui(new Ui::TipWidget)
{
    ui->setupUi(this);
    this->resize(HLINE,VLINE);

    if(parent==0)
    {
        move(Tool::ScreenCenter(this->rect()));
    }

    initData();
    initLayout();
    initConnect();
    initTip();
    setTitle(title);
    setTipText(text);
    setType(type);
    this->exec();
}

TipWidget::TipWidget(QWidget *parent, const QString &text, const int &type) :
    QDialog(parent),
    ui(new Ui::TipWidget)
{
    ui->setupUi(this);
    this->resize(402,188);

    if(parent==0)
    {
        QRect screenRect = QApplication::desktop()->screenGeometry();
        move(screenRect.x(),screenRect.y());
    }

    initData();
    initLayout();
    initConnect();
    initEdit();
    setTitle("内容编辑：");
    setEditText(text);
    setType(type);
    this->exec();
}

TipWidget::~TipWidget()
{
    delete ui;
}

void TipWidget::initData()
{
    drag_mousePressedFlag = false;
    drag_beginPoint = QPoint(0,0);
    editState = false;
}

void TipWidget::initLayout()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);

    lb_title = new QLabel(this);
    bt_close = new QPushButton(this);

    lb_title->setGeometry(20,10,width()-10*2-30*2,20);
    bt_close->setGeometry(width()-10-30,10,20,20);


    lb_title->setStyleSheet("QLabel{color:#FFF;font-size:18px;}");
    bt_close->setFlat(true);
    bt_close->setStyleSheet("QPushButton{border-image:url(:/image/softImage/system/close_2.png)}"
                            "QPushButton:hover{border-image:url(:/image/softImage/system/close_1.png)}"
                            "QPushButton:pressed{border-image:url(:/image/softImage/system/close_3.png)}");
}

void TipWidget::initConnect()
{
    connect(bt_close,SIGNAL(clicked(bool)),this,SLOT(close()));
}

bool TipWidget::isEdit()
{
    return editState;
}

QString TipWidget::getEditText()
{
    return te_edit->toPlainText();
}

void TipWidget::setEditText(QString text)
{
    te_edit->setText(text);
}

void TipWidget::initTip()
{
    lb_text = new QLabel(this);

    lb_text->setAlignment(Qt::AlignCenter);

    lb_text->setGeometry(10,height()/2-20/2,width()-10*2,20);


    lb_text->setStyleSheet("QLabel{color:#a6a6a6;font-size:16px;}");
}

void TipWidget::setTitle(const QString &title)
{
    lb_title->setText(title);
}

void TipWidget::setTipText(const QString &text)
{
    int length = text.length();

    this->resize(length*25+40,150);
    lb_text->setGeometry(10,height()/2-20/2,width()-10*2,20);
    bt_close->setGeometry(width()-10-30,10,20,20);
    lb_text->setText(text);
}

void TipWidget::initEdit()
{
    te_edit = new QTextEdit(this);
    te_edit->setGeometry(5,40,width()-12,height()-80);
    connect(te_edit,SIGNAL(textChanged()),this,SLOT(slot_maxLength()));
}

void TipWidget::setType(const int type)
{
    if (type > 10 && type < 20)
    {
        switch (type)
        {
        case 11:
            setType11();
            break;
        case 12:
            setType12();
            break;
        default:
            setTypeOther();
            break;
        }
        return;
    }
    if (type > 30 && type < 40)
    {
        switch (type)
        {
        case 31:
            setTypeOther();
            break;
        case 32:
            setType32();
            break;
        default:
            setTypeOther();
            break;
        }

        return;
    }
    setTypeOther();
}

void TipWidget::setType11()
{
    QPushButton *bt_ok = new QPushButton(this);
    bt_ok->setGeometry(width()/2-40,height()-35,80,30);
    bt_ok->setText("确认");
    bt_ok->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:15px;font-weight:bold;}"
                         "QPushButton:hover{background-color:rgb(233,164,255)}"
                         "QPushButton:pressed{background-color:#F6B56C}");
    connect(bt_ok,SIGNAL(clicked(bool)),this,SLOT(close()));
    return;
}

void TipWidget::setType12()
{
    QPushButton *bt_ok = new QPushButton(this);
    bt_ok->setGeometry(width()/2+2,height()-35,80,30);
    bt_ok->setText("确认");
    bt_ok->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:15px;font-weight:bold;}"
                         "QPushButton:hover{background-color:rgb(233,164,255)}"
                         "QPushButton:pressed{background-color:#F6B56C}");
    //        connect(bt_ok,SIGNAL(clicked(bool)),this,SLOT(close()));
    QPushButton *bt_no = new QPushButton(this);
    bt_no->setGeometry(width()/2-83,height()-35,80,30);
    bt_no->setText("取消");
    bt_no->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:15px;font-weight:bold;}"
                         "QPushButton:hover{background-color:rgb(233,164,255)}"
                         "QPushButton:pressed{background-color:#F6B56C}");
    connect(bt_no,SIGNAL(clicked(bool)),this,SLOT(close()));
    return;
}

void TipWidget::setType32()
{
    QPushButton *bt_ok = new QPushButton(this);
    bt_ok->setGeometry(width()/2+2,height()-35,80,30);
    bt_ok->setText("确认");
    bt_ok->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:15px;font-weight:bold;}"
                         "QPushButton:hover{background-color:rgb(233,164,255)}"
                         "QPushButton:pressed{background-color:#F6B56C}");
    connect(bt_ok,SIGNAL(clicked(bool)),this,SLOT(slot_editYes()));
    QPushButton *bt_no = new QPushButton(this);
    bt_no->setGeometry(width()/2-83,height()-35,80,30);
    bt_no->setText("取消");
    bt_no->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:15px;font-weight:bold;}"
                         "QPushButton:hover{background-color:rgb(233,164,255)}"
                         "QPushButton:pressed{background-color:#F6B56C}");
    connect(bt_no,SIGNAL(clicked(bool)),this,SLOT(close()));
    return;
}

void TipWidget::setTypeOther()
{
    lb_text = new QLabel(this);
    lb_text->setStyleSheet("QLabel{background:transparent};font-size:15px;");
    lb_text->setAlignment(Qt::AlignCenter);
    lb_text->setGeometry(10,height()/2-20/2,width()-10*2,20);

    lb_title->setText("暂无此类型窗口！");
    lb_text->setText("请检查窗口类型是否写错");

    QPushButton *bt_ok = new QPushButton(this);
    bt_ok->setGeometry(width()/2-40,height()-35,80,30);
    bt_ok->setText("好的");
    bt_ok->setStyleSheet("QPushButton{background-color:rgb(212,48,48);color:#FFFFFF;font-size:15px;font-weight:bold;}"
                         "QPushButton:hover{background-color:rgb(233,164,255)}"
                         "QPushButton:pressed{background-color:#F6B56C}");
    connect(bt_ok,SIGNAL(clicked(bool)),this,SLOT(close()));
    return;
}

void TipWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        drag_mousePressedFlag = true;
        drag_beginPoint = event->pos();
    }
}

void TipWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(drag_mousePressedFlag)
    {
        move(event->globalPos()-drag_beginPoint);
    }
}

void TipWidget::mouseReleaseEvent(QMouseEvent *event)
{
    drag_mousePressedFlag = false;
    event->accept();
}

void TipWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/image/background_2.png"));
    painter.drawPixmap(0,0,width(),40,QPixmap(":/image/TimeBackground.png"));
    painter.drawPixmap(0,height()-40,width(),40,QPixmap(":/image/TimeBackground.png"));
    QPen pen(Qt::white,3,Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRect(0,0,width()-3,height()-3);

    event->accept();
}

void TipWidget::slot_editYes()
{
    editState = true;
    close();
}

void TipWidget::slot_editNo()
{
    editState = false;
    close();
}

void TipWidget::slot_maxLength()
{
    QString textContent = te_edit->toPlainText();
    int length = textContent.count();
    int maxLength = MAXLENGTH; // 最大字符数
    if(length > maxLength)
    {
        int position = te_edit->textCursor().position();
        QTextCursor textCursor = te_edit->textCursor();
        textContent.remove(position - (length - maxLength), length - maxLength);
        te_edit->setText(textContent);
        textCursor.setPosition(position - (length - maxLength));
        te_edit->setTextCursor(textCursor);
    }
}
