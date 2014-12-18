#-------------------------------------------------
#
# Project created by QtCreator 2013-04-15T21:12:55
#
#-------------------------------------------------

QT       += sql core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyVensim
TEMPLATE = app


SOURCES += \
    main.cpp \
    UserFlows.cpp \
    SystemImpl.cpp \
    ModelImpl.cpp \
    mainwindow.cpp \
    FlowImpl.cpp \
    Factory.cpp

HEADERS  += \
    UserFlows.h \
    SystemImpl.h \
    System.h \
    ModelImpl.h \
    Model.h \
    mainwindow.h \
    HandleBody.h \
    FlowImpl.h \
    Flow.h \
    Factory.h

FORMS    += \
    mainwindow.ui
