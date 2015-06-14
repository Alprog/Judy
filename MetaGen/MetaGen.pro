
include(../Default.pri)

TEMPLATE = app

SOURCES += \
    Source/Main.cpp \
    Source/Parser.cpp \
    Source/Statement.cpp \
    Source/Snippet.cpp \
    Source/Token.cpp \
    Source/Info/ArgumentInfo.cpp \
    Source/Info/MemberInfo.cpp \
    Source/Info/TypeInfo.cpp \
    Source/Info/MethodInfo.cpp \
    Source/Info/ClassInfo.cpp

CONFIG += qt

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}

HEADERS += \
    Source/Parser.h \
    Source/Statement.h \
    Source/Snippet.h \
    Source/Token.h \
    Source/RegexConstants.h \
    Source/Info/AccessModifier.h \
    Source/Info/ArgumentInfo.h \
    Source/Info/MemberInfo.h \
    Source/Info/TypeInfo.h \
    Source/Info/MethodInfo.h \
    Source/Info/ClassInfo.h
