/********************************************************************************
** Form generated from reading UI file 'showboardwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWBOARDWIDGET_H
#define UI_SHOWBOARDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ShowBoardWidget
{
public:

    void setupUi(QDialog *ShowBoardWidget)
    {
        if (ShowBoardWidget->objectName().isEmpty())
            ShowBoardWidget->setObjectName(QStringLiteral("ShowBoardWidget"));
        ShowBoardWidget->resize(400, 300);

        retranslateUi(ShowBoardWidget);

        QMetaObject::connectSlotsByName(ShowBoardWidget);
    } // setupUi

    void retranslateUi(QDialog *ShowBoardWidget)
    {
        ShowBoardWidget->setWindowTitle(QApplication::translate("ShowBoardWidget", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowBoardWidget: public Ui_ShowBoardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWBOARDWIDGET_H
