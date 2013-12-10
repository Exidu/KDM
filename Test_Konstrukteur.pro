#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T17:46:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KosmeKonstrukteur
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h\
         libxl.h\
         IBookT.h\
         IFormatT.h\
         IFontT.h\
         ISheetT.h\
         enum.h\
         setup.h

FORMS    += mainwindow.ui

QMAKESPEC = QTDIR\mkspecs\win32-g++

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libxl-3.5.3.0/lib64/release/ -lxl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libxl-3.5.3.0/lib64/debug/ -lxl
else:unix: LIBS += -L$$PWD/../libxl-3.5.3.0/lib64/ -lxl

INCLUDEPATH += $$PWD/../libxl-3.5.3.0/lib64
DEPENDPATH += $$PWD/../libxl-3.5.3.0/lib64
