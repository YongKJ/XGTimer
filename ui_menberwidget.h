/********************************************************************************
** Form generated from reading UI file 'menberwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENBERWIDGET_H
#define UI_MENBERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenberWidget
{
public:

    void setupUi(QWidget *MenberWidget)
    {
        if (MenberWidget->objectName().isEmpty())
            MenberWidget->setObjectName(QStringLiteral("MenberWidget"));
        MenberWidget->resize(400, 300);

        retranslateUi(MenberWidget);

        QMetaObject::connectSlotsByName(MenberWidget);
    } // setupUi

    void retranslateUi(QWidget *MenberWidget)
    {
        MenberWidget->setWindowTitle(QApplication::translate("MenberWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MenberWidget: public Ui_MenberWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENBERWIDGET_H
