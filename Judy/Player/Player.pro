
TEMPLATE = app

CONFIG -= qt
LIBS += -lUser32 -lGdi32

include(../Default.pri)
include(../Engine/Include.pri)

SOURCES += \
    Source/Main.cpp

HEADERS += \
    Windows.h
