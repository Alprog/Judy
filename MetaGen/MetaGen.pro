
include(../Default.pri)

TEMPLATE = app

SOURCES += \
    Source/Main.cpp

CONFIG += qt

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}
