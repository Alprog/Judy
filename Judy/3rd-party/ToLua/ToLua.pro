
include(../../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
    source \
    ../lua/source \

HEADERS += \
    source/lib/tolua_event.h \

SOURCES += \
    source/lib/tolua_event.c \
    source/lib/tolua_is.c \
    source/lib/tolua_map.c \
    source/lib/tolua_push.c \
    source/lib/tolua_to.c \

