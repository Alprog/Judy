
include(../../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
    source \
    ../zlib/source \

HEADERS += \
    source/png.h \
    source/pngconf.h \
    source/pngdebug.h \
    source/pnginfo.h \
    source/pngstruct.h \
    source/pngpriv.h

SOURCES += \
    source/png.c \
    source/pngerror.c \
    source/pngget.c \
    source/pngmem.c \
    source/pngpread.c \
    source/pngread.c \
    source/pngrio.c \
    source/pngrtran.c \
    source/pngrutil.c \
    source/pngset.c \
    source/pngtrans.c \
    source/pngwio.c \
    source/pngwrite.c \
    source/pngwtran.c \
    source/pngwutil.c
