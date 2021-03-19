/********************************************************************************
** Form generated from reading UI file 'imagetool.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGETOOL_H
#define UI_IMAGETOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageTool
{
public:

    void setupUi(QWidget *ImageTool)
    {
        if (ImageTool->objectName().isEmpty())
            ImageTool->setObjectName(QStringLiteral("ImageTool"));
        ImageTool->resize(400, 300);

        retranslateUi(ImageTool);

        QMetaObject::connectSlotsByName(ImageTool);
    } // setupUi

    void retranslateUi(QWidget *ImageTool)
    {
        ImageTool->setWindowTitle(QApplication::translate("ImageTool", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageTool: public Ui_ImageTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGETOOL_H
