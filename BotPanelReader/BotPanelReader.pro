#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T09:30:43
#
#-------------------------------------------------

QT       += core gui
TARGET = openCvQt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BotPanelReader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    analysewindow.cpp \
    streamwindow.cpp \
    learningwindow.cpp

HEADERS  += mainwindow.h \
    analysewindow.h \
    streamwindow.h \
    learningwindow.h

FORMS    += mainwindow.ui \
    analysewindow.ui \
    streamwindow.ui


INCLUDEPATH += C:\opencv\build\include

LIBS += C:\opencv-build\bin\libopencv_videoio400.dll
LIBS += C:\opencv-build\bin\libopencv_core400.dll
LIBS += C:\opencv-build\bin\libopencv_highgui400.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs400.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc400.dll
LIBS += C:\opencv-build\bin\libopencv_features2d400.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d400.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d400.dll
LIBS += C:\opencv-build\bin\libopencv_ml400.dll
