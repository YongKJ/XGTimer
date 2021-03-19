#ifndef IMAGETOOL_H
#define IMAGETOOL_H

#include <QDialog>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLabel>
#include <QColor>
#include <QPainter>
#include <QListWidget>
#include "user.h"

namespace Ui {
class ImageTool;
}

class ImageTool : public QDialog
{
    Q_OBJECT

public:
    explicit ImageTool(QWidget *parent = 0,const int &getType = 0);
    ~ImageTool();
    void initData();
    void setImage(const QString &path);
    void setImage(const int &headImageProperty);

    void AddListItem();

    void initTypeStyle(const int &getType);


    int getType() const;

public slots:
    void setMove(const QRect &rect);


protected:
    void paintEvent(QPaintEvent*event);
    void mousePressEvent(QMouseEvent*event);
    void leaveEvent(QEvent *event);

private:
    Ui::ImageTool *ui;
    QLabel *m_imageMessage;
    int m_type;

    QListWidget *m_listWidget;


    void setType(const int &Type);

    /*类型0---------------------------------------------------*/
    void initLayoutType_0();
    void initConnectType_0();

    /*类型1-----------------------------------------------------*/
    void initLayoutType_1();
    void initConnectType_1();

private slots:
    void ChangeImage(int headImageProperty);

signals:
    void SIGNALToChangeImage(int);



};

#endif // IMAGETOOL_H
