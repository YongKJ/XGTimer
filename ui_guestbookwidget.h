/********************************************************************************
** Form generated from reading UI file 'guestbookwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUESTBOOKWIDGET_H
#define UI_GUESTBOOKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuestBookWidget
{
public:

    void setupUi(QWidget *GuestBookWidget)
    {
        if (GuestBookWidget->objectName().isEmpty())
            GuestBookWidget->setObjectName(QStringLiteral("GuestBookWidget"));
        GuestBookWidget->resize(400, 300);

        retranslateUi(GuestBookWidget);

        QMetaObject::connectSlotsByName(GuestBookWidget);
    } // setupUi

    void retranslateUi(QWidget *GuestBookWidget)
    {
        GuestBookWidget->setWindowTitle(QApplication::translate("GuestBookWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GuestBookWidget: public Ui_GuestBookWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUESTBOOKWIDGET_H
