
include(../../../default.pri)

TEMPLATE = app
CONFIG += console
TARGET = ../../toLua++

LIBS += -L"../../" -llua -ltolua++
PRE_TARGETDEPS += "../../lua.lib"
PRE_TARGETDEPS += "../../tolua++.lib"

INCLUDEPATH += \
    ../ \
    ../../lua/source \

SOURCES += \
    tolua.c \
    toluabind.c \
