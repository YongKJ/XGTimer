/********************************************************************************
** Form generated from reading UI file 'personwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONWIDGET_H
#define UI_PERSONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonWidget
{
public:
    QLabel *label;

    void setupUi(QWidget *PersonWidget)
    {
        if (PersonWidget->objectName().isEmpty())
            PersonWidget->setObjectName(QStringLiteral("PersonWidget"));
        PersonWidget->resize(400, 300);
        label = new QLabel(PersonWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 130, 54, 11));

        retranslateUi(PersonWidget);

        QMetaObject::connectSlotsByName(PersonWidget);
    } // setupUi

    void retranslateUi(QWidget *PersonWidget)
    {
        PersonWidget->setWindowTitle(QApplication::translate("PersonWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("PersonWidget", "\344\270\252\344\272\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PersonWidget: public Ui_PersonWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONWIDGET_H
