
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

CONFIG += qt
QT += widgets

SOURCES += \
    Source/Main.cpp \
    Source/MainWindow.cpp

INCLUDEPATH += "../3rd-party/scintilla/include"

LIBS += -L"../3rd-party" -lscintillaedit3

HEADERS += \
    Source/MainWindow.h

RESOURCES = ide.qrc
