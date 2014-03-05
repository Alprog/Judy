#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T06:51:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += "D:/Metroidvania/src/scintilla/qt/ScintillaEditBase"
INCLUDEPATH += "D:/Metroidvania/src/scintilla/include"

LIBS += -LD:/Metroidvania/src/scintilla/bin -lScintillaEditBase3
