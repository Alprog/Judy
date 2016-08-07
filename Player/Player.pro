
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

INCLUDEPATH += \
    ../3rd-party/lua/Source \

SOURCES += \
    Source/Main.cpp \
    Source/RemoteDebbuger.cpp

HEADERS += \
    Windows.h \
    Source/RemoteDebbuger.h

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
    LIBS += -lglew32s
}
