#include "imagetool.h"
#include "ui_imagetool.h"

ImageTool::ImageTool(QWidget *parent, const int &type) :
    QDialog(parent),
    ui(new Ui::ImageTool)
{
    ui->setupUi(this);
    initData();
    initTypeStyle(type);
    setType(type);
}

ImageTool::~ImageTool()
{
    delete ui;
}

void ImageTool::initData()
{

}
void ImageTool::initTypeStyle(const int &type)
{
    switch(type)
    {
    case 0:
        //设置界面大小
        this->setFixedSize(200,200);
        initLayoutType_0();
        initConnectType_0();
        break;
    case 1:
        this->resize(100,396);
        initLayoutType_1();
        initConnectType_1();
        AddListItem();
        break;
    }
}

void ImageTool::setImage(const QString &path)
{
    if(getType()==0)
    {
        QPixmap pixmap(path);
        pixmap.scaled(m_imageMessage->size(), Qt::KeepAspectRatio);
        m_imageMessage->setPixmap(pixmap);
    }
}

void ImageTool::setImage(const int &headImageProperty)
{
    if(getType()==1)
    {
        m_listWidget->setCurrentRow(headImageProperty);
    }
}

void ImageTool::setMove(const QRect &rect)
{
    this->move(QPoint(rect.x()-105,rect.y()));
}

void ImageTool::AddListItem()
{
    for(int i=0;i<IMAGECOUT;i++)
    {
        QListWidgetItem * item = new QListWidgetItem(QIcon(User::getHeadImagePath(i)),NULL);
        m_listWidget->addItem(item);
    }

}

int ImageTool::getType() const
{
    return m_type;
}

void ImageTool::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color(200, 200, 200, 50);
    for(int i=0; i<4; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(4-i, 4-i, this->width()-(4-i)*2, this->height()-(4-i)*2);
        color.setAlpha(75+i*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
    painter.end();

    event->accept();
}
//保护事件------------------------------------------
void ImageTool::mousePressEvent(QMouseEvent *event)
{
    close();
}

void ImageTool::leaveEvent(QEvent *event)
{
    if(getType()==0) close();

}

void ImageTool::setType(const int &Type)
{
    m_type = Type;
}

void ImageTool::initLayoutType_0()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setPalette(QPalette(QColor(255,255,255)));
    m_imageMessage = new QLabel(this);
    m_imageMessage->setGeometry(0,0,200,200);
    m_imageMessage->setScaledContents(true);
}
void ImageTool::initConnectType_0()
{

}

void ImageTool::initLayoutType_1()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setPalette(QPalette(QColor(0,0,0)));

    m_listWidget = new QListWidget(this);
    m_listWidget->setGeometry(4,4,86,388);
    m_listWidget->setStyleSheet("QListWidget{"
                                "background:transparent;}");
    m_listWidget->setSpacing(4);
    m_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWidget->setViewMode(QListView::IconMode);
    m_listWidget->setIconSize(QSize(70,70));
    m_listWidget->setDragEnabled(false);
}
void ImageTool::initConnectType_1()
{
    connect(m_listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ChangeImage(int)));
}

void ImageTool::ChangeImage(int headImageProperty)
{
    emit SIGNALToChangeImage(headImageProperty);
}


