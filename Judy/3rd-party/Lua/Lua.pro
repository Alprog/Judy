
include(../../default.pri)

TEMPLATE = lib
TARGET = ../lua
CONFIG += staticlib

HEADERS += \
    source/lapi.h \
    source/lauxlib.h \
    source/lcode.h \
    source/lctype.h \
    source/ldebug.h \
    source/ldo.h \
    source/lfunc.h \
    source/lgc.h \
    source/llex.h \
    source/llimits.h \
    source/lmem.h \
    source/lobject.h \
    source/lopcodes.h \
    source/lparser.h \
    source/lstate.h \
    source/lstring.h \
    source/ltable.h \
    source/ltm.h \
    source/lua.h \
    source/lua.hpp \
    source/luaconf.h \
    source/lualib.h \
    source/lundump.h \
    source/lvm.h \
    source/lzio.h

SOURCES += \
    source/lapi.c \
    source/lauxlib.c \
    source/lbaselib.c \
    source/lbitlib.c \
    source/lcode.c \
    source/lcorolib.c \
    source/lctype.c \
    source/ldblib.c \
    source/ldebug.c \
    source/ldo.c \
    source/ldump.c \
    source/lfunc.c \
    source/lgc.c \
    source/linit.c \
    source/liolib.c \
    source/llex.c \
    source/lmathlib.c \
    source/lmem.c \
    source/loadlib.c \
    source/lobject.c \
    source/lopcodes.c \
    source/loslib.c \
    source/lparser.c \
    source/lstate.c \
    source/lstring.c \
    source/lstrlib.c \
    source/ltable.c \
    source/ltablib.c \
    source/ltm.c \
    source/lua.c \
    source/luac.c \
    source/lundump.c \
    source/lvm.c \
    source/lzio.c

