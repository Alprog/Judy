
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

SOURCES += \
    Source/Main.cpp

HEADERS += \
    Windows.h

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}
