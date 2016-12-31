#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T14:12:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP2
TEMPLATE = app

INCLUDEPATH += $$PWD/../../glm-0.9.8.3

SOURCES += main.cpp\
        mainwindow.cpp \
        widgetopengl.cpp \
    camera.cpp \
    drawableopengl.cpp

HEADERS  += mainwindow.h \
            widgetopengl.h \
    camera.h \
    drawableopengl.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
