/********************************************************************************
** Form generated from reading UI file 'tipwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPWIDGET_H
#define UI_TIPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_TipWidget
{
public:

    void setupUi(QDialog *TipWidget)
    {
        if (TipWidget->objectName().isEmpty())
            TipWidget->setObjectName(QStringLiteral("TipWidget"));
        TipWidget->resize(400, 300);

        retranslateUi(TipWidget);

        QMetaObject::connectSlotsByName(TipWidget);
    } // setupUi

    void retranslateUi(QDialog *TipWidget)
    {
        TipWidget->setWindowTitle(QApplication::translate("TipWidget", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TipWidget: public Ui_TipWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPWIDGET_H
