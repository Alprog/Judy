
include(../Default.pri)

TEMPLATE = app

SOURCES += \
    Source/Main.cpp \
    Source/Parser.cpp \
    Source/Statement.cpp \
    Source/Snippet.cpp \
    Source/Info/ArgumentInfo.cpp \
    Source/Info/MemberInfo.cpp \
    Source/Info/TypeInfo.cpp \
    Source/Info/MethodInfo.cpp \
    Source/Info/ClassInfo.cpp \
    Source/Info/InheritanceInfo.cpp \
    Source/Info/FieldInfo.cpp \
    Source/Info/NamespaceInfo.cpp \
    Source/Tokens/AtomToken.cpp \
    Source/Tokens/Token.cpp \
    Source/Tokens/TokenGroup.cpp

CONFIG += qt

win {
    QMAKE_LFLAGS += /ENTRY:"mainCRTStartup"
}

HEADERS += \
    Source/Parser.h \
    Source/Statement.h \
    Source/Snippet.h \
    Source/RegexConstants.h \
    Source/Info/AccessModifier.h \
    Source/Info/ArgumentInfo.h \
    Source/Info/MemberInfo.h \
    Source/Info/TypeInfo.h \
    Source/Info/MethodInfo.h \
    Source/Info/ClassInfo.h \
    Source/Info/InheritanceInfo.h \
    Source/Info/FieldInfo.h \
    Source/Info/NamespaceInfo.h \
    Source/Tokens/AtomToken.h \
    Source/Tokens/Token.h \
    Source/Tokens/TokenGroup.h
