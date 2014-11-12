
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

INCLUDEPATH += \
    ../3rd-party/lua/source \


SOURCES += \
    Source/Main.cpp

HEADERS += \
    Windows.h

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}
