
include(../../Default.pri)

TEMPLATE = lib
TARGET = ../libpng
CONFIG += staticlib

INCLUDEPATH += \
    source \
    ../zlib/Source \

HEADERS += \
    Source/png.h \
    Source/pngconf.h \
    Source/pngdebug.h \
    Source/pnginfo.h \
    Source/pngstruct.h \
    Source/pngpriv.h

SOURCES += \
    Source/png.c \
    Source/pngerror.c \
    Source/pngget.c \
    Source/pngmem.c \
    Source/pngpread.c \
    Source/pngread.c \
    Source/pngrio.c \
    Source/pngrtran.c \
    Source/pngrutil.c \
    Source/pngset.c \
    Source/pngtrans.c \
    Source/pngwio.c \
    Source/pngwrite.c \
    Source/pngwtran.c \
    Source/pngwutil.c
