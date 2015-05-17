
include(../../default.pri)

TARGET = ../ScintillaEdit
TEMPLATE = lib
CONFIG += lib_bundle

CONFIG += qt
QT += core gui widgets

DEFINES += SCI_LEXER

VERSION = 3.5.5

SOURCES += \
    qt/ScintillaEdit.cpp \
    qt/ScintillaDocument.cpp \
    qt/PlatQt.cpp \
    qt/ScintillaQt.cpp \
    qt/ScintillaEditBase.cpp \
    src/XPM.cxx \
    src/ViewStyle.cxx \
    src/UniConversion.cxx \
    src/Style.cxx \
    src/Selection.cxx \
    src/ScintillaBase.cxx \
    src/RunStyles.cxx \
    src/RESearch.cxx \
    src/PositionCache.cxx \
    src/PerLine.cxx \
    src/LineMarker.cxx \
    src/KeyMap.cxx \
    src/Indicator.cxx \
    src/ExternalLexer.cxx \
    src/Editor.cxx \
    src/EditView.cxx \
    src/EditModel.cxx \
    src/Document.cxx \
    src/Decoration.cxx \
    src/ContractionState.cxx \
    src/CharClassify.cxx \
    src/CellBuffer.cxx \
    src/Catalogue.cxx \
    src/CaseFolder.cxx \
    src/CaseConvert.cxx \
    src/CallTip.cxx \
    src/AutoComplete.cxx \
    src/MarginView.cxx \
    lexlib/WordList.cxx \
    lexlib/StyleContext.cxx \
    lexlib/PropSetSimple.cxx \
    lexlib/LexerSimple.cxx \
    lexlib/LexerNoExceptions.cxx \
    lexlib/LexerModule.cxx \
    lexlib/LexerBase.cxx \
    lexlib/CharacterSet.cxx \
    lexlib/CharacterCategory.cxx \
    lexlib/Accessor.cxx \
    lexers/LexLua.cxx \

HEADERS += \
    qt/ScintillaEdit.h \
    qt/ScintillaDocument.h \
    qt/ScintillaEditBase.h \
    qt/ScintillaQt.h

INCLUDEPATH += qt src lexlib include

DEFINES += SCINTILLA_QT=1 MAKING_LIBRARY=1 SCI_LEXER=1 _CRT_SECURE_NO_DEPRECATE=1

macx {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
}
