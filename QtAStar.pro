#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T22:12:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtAStar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mapview.cpp \
    AStar.cpp

HEADERS  += mainwindow.h \
    mapview.h \
    AStar.h \
    astarmap.h

FORMS    +=

CONFIG += c++11
