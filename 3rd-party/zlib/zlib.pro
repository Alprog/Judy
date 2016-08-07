
include(../../Default.pri)

TEMPLATE = lib
TARGET = ../zlib
CONFIG += staticlib

DEFINES += Z_SOLO

INCLUDEPATH += \
    Source \

HEADERS += \
    Source/crc32.h \
    Source/deflate.h \
    Source/inffast.h \
    Source/inffixed.h \
    Source/inflate.h \
    Source/inftrees.h \
    Source/trees.h \
    Source/zconf.h \
    Source/zlib.h \
    Source/zutil.h

SOURCES += \
    Source/adler32.c \
    Source/compress.c \
    Source/crc32.c \
    Source/deflate.c \
    Source/infback.c \
    Source/inffast.c \
    Source/inflate.c \
    Source/inftrees.c \
    Source/trees.c \
    Source/uncompr.c \
    Source/zutil.c
