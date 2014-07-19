
include(../../../default.pri)

TEMPLATE = lib
TARGET = ../../toLua
CONFIG += staticlib

INCLUDEPATH += \
    ../ \
    ../../lua/source \

HEADERS += \
    tolua_event.h \

SOURCES += \
    tolua_event.c \
    tolua_is.c \
    tolua_map.c \
    tolua_push.c \
    tolua_to.c \

