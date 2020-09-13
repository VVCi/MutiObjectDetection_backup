#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T11:40:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MutiObjectDetection
TEMPLATE = app
INCLUDEPATH += /usr/local/include/opencv
LIBS += /usr/local/lib/*.so
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Fruit.cpp

HEADERS  += mainwindow.h \
    Fruit.h

FORMS    += mainwindow.ui
