
include(../Default.pri)

TEMPLATE = app

SOURCES += \
    Source/Main.cpp \
    Source/Parser.cpp \
    Source/Statement.cpp \
    Source/Snippet.cpp \
    Source/Token.cpp

CONFIG += qt

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}

HEADERS += \
    Source/Parser.h \
    Source/Statement.h \
    Source/Snippet.h \
    Source/Token.h \
    Source/RegexConstants.h
