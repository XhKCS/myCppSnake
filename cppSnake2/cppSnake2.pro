QT      += core gui
QT      += multimedia
QT      += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    box.cpp \
    gamewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mypushbutton.cpp \
    recordwidget.cpp \
    sdwidget.cpp \
    snake.cpp \
    srwidget.cpp

HEADERS += \
    box.h \
    gamewidget.h \
    mainwindow.h \
    mypushbutton.h \
    recordwidget.h \
    sdwidget.h \
    snake.h \
    srwidget.h

FORMS += \
    gamewidget.ui \
    mainwindow.ui \
    recordwidget.ui \
    sdwidget.ui \
    srwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res2.qrc

RC_ICONS = favicon.ico



