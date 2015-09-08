
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

INCLUDEPATH += \
    ../3rd-party/lua/source \

SOURCES += \
    Source/Main.cpp \
    Source/RemoteDebbuger.cpp

HEADERS += \
    Windows.h \
    Source/RemoteDebbuger.h

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}
