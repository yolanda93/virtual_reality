#-------------------------------------------------
# Cours de Réalité Virtuelle
# leo.donati@unice.fr
#
# EPU 2016-17
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RV_ex3
TEMPLATE = app


SOURCES += main.cpp\
    widgetopengl.cpp

HEADERS  += widgetopengl.h

FORMS    +=

#DISTFILES += RealiteVirtuelle.txt

INCLUDEPATH += $$PWD/../glm

windows:LIBS += -lopengl32

