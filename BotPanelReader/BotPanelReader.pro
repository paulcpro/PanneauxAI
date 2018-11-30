#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T09:30:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BotPanelReader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    analysewindow.cpp \
    histogrammewindow.cpp

HEADERS  += mainwindow.h \
    analysewindow.h \
    histogrammewindow.h

FORMS    += mainwindow.ui \
    analysewindow.ui \
    histogrammewindow.ui
