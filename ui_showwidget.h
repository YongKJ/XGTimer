/********************************************************************************
** Form generated from reading UI file 'showwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWWIDGET_H
#define UI_SHOWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowWidget
{
public:

    void setupUi(QWidget *ShowWidget)
    {
        if (ShowWidget->objectName().isEmpty())
            ShowWidget->setObjectName(QStringLiteral("ShowWidget"));
        ShowWidget->resize(400, 300);

        retranslateUi(ShowWidget);

        QMetaObject::connectSlotsByName(ShowWidget);
    } // setupUi

    void retranslateUi(QWidget *ShowWidget)
    {
        ShowWidget->setWindowTitle(QApplication::translate("ShowWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowWidget: public Ui_ShowWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWWIDGET_H
