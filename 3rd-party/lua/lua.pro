
include(../../Default.pri)

TEMPLATE = lib
TARGET = ../lua
CONFIG += staticlib

HEADERS += \
    Source/lapi.h \
    Source/lauxlib.h \
    Source/lcode.h \
    Source/lctype.h \
    Source/ldebug.h \
    Source/ldo.h \
    Source/lfunc.h \
    Source/lgc.h \
    Source/llex.h \
    Source/llimits.h \
    Source/lmem.h \
    Source/lobject.h \
    Source/lopcodes.h \
    Source/lparser.h \
    Source/lstate.h \
    Source/lstring.h \
    Source/ltable.h \
    Source/ltm.h \
    Source/lua.h \
    Source/lua.hpp \
    Source/luaconf.h \
    Source/lualib.h \
    Source/lundump.h \
    Source/lvm.h \
    Source/lzio.h \
    Source/lprefix.h

SOURCES += \
    Source/lapi.c \
    Source/lauxlib.c \
    Source/lbaselib.c \
    Source/lbitlib.c \
    Source/lcode.c \
    Source/lcorolib.c \
    Source/lctype.c \
    Source/ldblib.c \
    Source/ldebug.c \
    Source/ldo.c \
    Source/ldump.c \
    Source/lfunc.c \
    Source/lgc.c \
    Source/linit.c \
    Source/liolib.c \
    Source/llex.c \
    Source/lmathlib.c \
    Source/lmem.c \
    Source/loadlib.c \
    Source/lobject.c \
    Source/lopcodes.c \
    Source/loslib.c \
    Source/lparser.c \
    Source/lstate.c \
    Source/lstring.c \
    Source/lstrlib.c \
    Source/ltable.c \
    Source/ltablib.c \
    Source/ltm.c \
    Source/lua.c \
    Source/luac.c \
    Source/lundump.c \
    Source/lvm.c \
    Source/lzio.c \
    Source/lutf8lib.c


