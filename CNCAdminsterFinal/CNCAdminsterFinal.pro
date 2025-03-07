QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosewindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpsocket.cpp \
    parameterwidget.cpp \
    registerwindow.cpp

HEADERS += \
    choosewindow.h \
    loginwindow.h \
    mainwindow.h \
    mytcpsocket.h \
    parameterwidget.h \
    registerwindow.h

FORMS += \
    choosewindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    parameterwidget.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
