/********************************************************************************
** Form generated from reading UI file 'boardwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARDWIDGET_H
#define UI_BOARDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_BoardWidget
{
public:

    void setupUi(QDialog *BoardWidget)
    {
        if (BoardWidget->objectName().isEmpty())
            BoardWidget->setObjectName(QStringLiteral("BoardWidget"));
        BoardWidget->resize(400, 300);

        retranslateUi(BoardWidget);

        QMetaObject::connectSlotsByName(BoardWidget);
    } // setupUi

    void retranslateUi(QDialog *BoardWidget)
    {
        BoardWidget->setWindowTitle(QApplication::translate("BoardWidget", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BoardWidget: public Ui_BoardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARDWIDGET_H
