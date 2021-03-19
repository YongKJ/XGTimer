/********************************************************************************
** Form generated from reading UI file 'callboardwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALLBOARDWIDGET_H
#define UI_CALLBOARDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CallBoardWidget
{
public:

    void setupUi(QWidget *CallBoardWidget)
    {
        if (CallBoardWidget->objectName().isEmpty())
            CallBoardWidget->setObjectName(QStringLiteral("CallBoardWidget"));
        CallBoardWidget->resize(400, 300);

        retranslateUi(CallBoardWidget);

        QMetaObject::connectSlotsByName(CallBoardWidget);
    } // setupUi

    void retranslateUi(QWidget *CallBoardWidget)
    {
        CallBoardWidget->setWindowTitle(QApplication::translate("CallBoardWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CallBoardWidget: public Ui_CallBoardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLBOARDWIDGET_H
