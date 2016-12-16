#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T20:35:49
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = managerSystem
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    login.cpp \
    PageWidget.cpp \
    dialog.cpp \
    tableview.cpp

HEADERS  += widget.h \
    login.h \
    pagewidget.h \
    dialog.h \
    connect_database.h \
    tableview.h

FORMS    += \
    PageWidget.ui
