#-------------------------------------------------
#
# Project created by QtCreator 2010-12-07T22:46:20
#
#-------------------------------------------------

QT += core gui sql xml network

TARGET = CETServer
TEMPLATE = app


SOURCES += main.cpp\
        cetserver.cpp \
    DatabaseHandler.cpp

HEADERS  += cetserver.h \
    DatabaseHandler.h

FORMS    += cetserver.ui
