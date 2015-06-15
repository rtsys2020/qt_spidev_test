#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T15:14:50
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = qt_spidev
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    spidev.cpp \


HEADERS += \
    spidevm.h\
    #../../ilum9260/include/asm-generic/ioctl.h

#INCLUDEPATH += ../../ilum9260
