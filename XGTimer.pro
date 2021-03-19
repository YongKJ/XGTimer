#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T16:47:45
#
#-------------------------------------------------

QT       += core gui
QT       += network
RC_ICONS +=Timer.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XGTimer
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        widget.cpp \
    mainwidget.cpp \
    titlewidget.cpp \
    showwidget.cpp \
    personwidget.cpp \
    menberwidget.cpp \
    user.cpp \
    registerwidget.cpp \
    loginwidget.cpp \
    timebit.cpp \
    tipwidget.cpp \
    boardwidget.cpp \
    guestbook.cpp \
    bottomwidget.cpp \
    tool.cpp \
    settingwidget.cpp \
    aboutwidget.cpp \
    userwidget.cpp \
    showboardwidget.cpp \
    repository/statuslabel.cpp \
    repository/imagetool.cpp \
    repository/guestbookwidget.cpp \
    changepassword.cpp \
    myserver.cpp

HEADERS += \
        widget.h \
    mainwidget.h \
    titlewidget.h \
    showwidget.h \
    personwidget.h \
    menberwidget.h \
    user.h \
    registerwidget.h \
    loginwidget.h \
    timebit.h \
    tipwidget.h \
    boardwidget.h \
    guestbook.h \
    bottomwidget.h \
    tool.h \
    settingwidget.h \
    aboutwidget.h \
    userwidget.h \
    showboardwidget.h \
    repository/statuslabel.h \
    repository/imagetool.h \
    repository/guestbookwidget.h \
    changepassword.h \
    myserver.h

FORMS += \
    repository/imagetool.ui \
    repository/guestbookwidget.ui \
    changepassword.ui

RESOURCES += \
    image.qrc

DISTFILES += \
    image/close_1.png \
    image/close_2.png \
    image/close_3.png \
    image/DataGraph.png \
    image/headImage/image_1.jpg \
    image/headImage/image_10.jpg \
    image/headImage/image_11.jpg \
    image/headImage/image_12.jpg \
    image/headImage/image_13.jpg \
    image/headImage/image_14.jpg \
    image/headImage/image_15.jpg \
    image/headImage/image_16.jpg \
    image/headImage/image_17.jpg \
    image/headImage/image_18.jpg \
    image/headImage/image_19.jpg \
    image/headImage/image_2.jpg \
    image/headImage/image_20.jpg \
    image/headImage/image_21.jpg \
    image/headImage/image_22.jpg \
    image/headImage/image_3.jpg \
    image/headImage/image_4.jpg \
    image/headImage/image_5.jpg \
    image/headImage/image_6.jpg \
    image/headImage/image_7.jpg \
    image/headImage/image_8.jpg \
    image/headImage/image_9.jpg \
    image/headImage/image_0.png \
    image/headImage/image_23.png \
    image/softImage/system/about_0.png \
    image/softImage/system/about_1.png \
    image/softImage/system/about_2.png \
    image/softImage/system/about_3.png \
    image/softImage/system/login_0.png \
    image/softImage/system/login_1.png \
    image/softImage/system/login_2.png \
    image/softImage/system/login_3.png \
    image/softImage/system/register_0.png \
    image/softImage/system/register_1.png \
    image/softImage/system/register_2.png \
    image/softImage/system/register_3.png \
    image/softImage/system/search_0.png \
    image/softImage/system/search_1.png \
    image/softImage/system/search_2.png \
    image/softImage/system/search_3.png \
    image/softImage/system/setting_0.png \
    image/softImage/system/setting_1.png \
    image/softImage/system/setting_2.png \
    image/softImage/system/setting_3.png \
    image/softImage/0.png \
    image/softImage/1.png \
    image/softImage/2.png \
    image/softImage/3.png \
    image/softImage/4.png \
    image/softImage/5.png \
    image/softImage/6.png \
    image/softImage/7.png \
    image/softImage/8.png \
    image/softImage/9.png \
    image/softImage/background_1.png \
    image/softImage/background_2.png \
    image/softImage/callboard.png \
    image/softImage/callboard_1.png \
    image/softImage/close_1.png \
    image/softImage/close_2.png \
    image/softImage/close_3.png \
    image/softImage/DataGraph.png \
    image/softImage/FindBackPassword_0.png \
    image/softImage/FindBackPassword_1.png \
    image/softImage/FindBackPassword_2.png \
    image/softImage/FindBackPassword_3.png \
    image/softImage/image_0.png \
    image/softImage/image_23.png \
    image/softImage/leftArrow_0.png \
    image/softImage/leftArrow_1.png \
    image/softImage/leftArrow_2.png \
    image/softImage/leftArrow_3.png \
    image/softImage/minize_0.png \
    image/softImage/minize_1.png \
    image/softImage/minize_2.png \
    image/softImage/minize_3.png \
    image/softImage/rightArrow_0.png \
    image/softImage/rightArrow_1.png \
    image/softImage/rightArrow_2.png \
    image/softImage/rightArrow_3.png \
    image/softImage/softIcon.png \
    image/softImage/softIntroduction_0.png \
    image/softImage/softIntroduction_1.png \
    image/softImage/softIntroduction_2.png \
    image/softImage/softIntroduction_3.png \
    image/softImage/TimeBackground.png \
    image/softImage/TimeBackground_1.png \
    image/0.png \
    image/1.png \
    image/2.png \
    image/3.png \
    image/4.png \
    image/5.png \
    image/6.png \
    image/7.png \
    image/8.png \
    image/9.png \
    image/Background.png \
    image/background_2.png \
    image/callboard.png \
    image/callboard_1.png \
    image/DataGraph.png \
    image/leftArrow_0.png \
    image/leftArrow_1.png \
    image/leftArrow_2.png \
    image/leftArrow_3.png \
    image/register_1.png \
    image/rightArrow_0.png \
    image/rightArrow_1.png \
    image/rightArrow_2.png \
    image/rightArrow_3.png \
    image/softIntroduction_0.png \
    image/softIntroduction_1.png \
    image/softIntroduction_2.png \
    image/softIntroduction_3.png \
    image/TimeBackground.png \
    image/TimeBackground_1.png
