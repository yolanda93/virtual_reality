#-------------------------------------------------
# Cours de Réalité Virtuelle
# leo.donati@unice.fr
#
# EPU 2016-17
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RV_ex4
TEMPLATE = app


SOURCES += main.cpp\
    widgetopengl.cpp

HEADERS  += \
    widgetopengl.h

#DISTFILES += RealiteVirtuelle.txt

INCLUDEPATH += $$PWD/../glm

windows:LIBS += -lopengl32


RESOURCES += \
    ex3.qrc

