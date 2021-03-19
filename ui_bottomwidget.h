/********************************************************************************
** Form generated from reading UI file 'bottomwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOTTOMWIDGET_H
#define UI_BOTTOMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BottomWidget
{
public:

    void setupUi(QWidget *BottomWidget)
    {
        if (BottomWidget->objectName().isEmpty())
            BottomWidget->setObjectName(QStringLiteral("BottomWidget"));
        BottomWidget->resize(400, 300);

        retranslateUi(BottomWidget);

        QMetaObject::connectSlotsByName(BottomWidget);
    } // setupUi

    void retranslateUi(QWidget *BottomWidget)
    {
        BottomWidget->setWindowTitle(QApplication::translate("BottomWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BottomWidget: public Ui_BottomWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOTTOMWIDGET_H
