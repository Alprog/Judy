
include(../../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
    source \

HEADERS += \
    source/crc32.h \
    source/deflate.h \
    source/gzguts.h \
    source/inffast.h \
    source/inffixed.h \
    source/inflate.h \
    source/inftrees.h \
    source/trees.h \
    source/zconf.h \
    source/zlib.h \
    source/zutil.h

SOURCES += \
    source/adler32.c \
    source/compress.c \
    source/crc32.c \
    source/deflate.c \
    source/gzclose.c \
    source/gzlib.c \
    source/gzread.c \
    source/gzwrite.c \
    source/infback.c \
    source/inffast.c \
    source/inflate.c \
    source/inftrees.c \
    source/trees.c \
    source/uncompr.c \
    source/zutil.c
