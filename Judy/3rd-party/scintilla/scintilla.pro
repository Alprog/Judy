
include(../../default.pri)

TARGET = ../ScintillaEdit
TEMPLATE = lib
CONFIG += lib_bundle

CONFIG += qt
QT += core gui widgets

DEFINES += SCI_LEXER

VERSION = 3.3.6

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
    lexers/LexA68k.cxx \
    lexers/LexAbaqus.cxx \
    lexers/LexAda.cxx \
    lexers/LexAPDL.cxx \
    lexers/LexAsm.cxx \
    lexers/LexAsn1.cxx \
    lexers/LexASY.cxx \
    lexers/LexAU3.cxx \
    lexers/LexAVE.cxx \
    lexers/LexAVS.cxx \
    lexers/LexBaan.cxx \
    lexers/LexBash.cxx \
    lexers/LexBasic.cxx \
    lexers/LexBullant.cxx \
    lexers/LexCaml.cxx \
    lexers/LexCLW.cxx \
    lexers/LexCmake.cxx \
    lexers/LexCOBOL.cxx \
    lexers/LexCoffeeScript.cxx \
    lexers/LexConf.cxx \
    lexers/LexCPP.cxx \
    lexers/LexCrontab.cxx \
    lexers/LexCsound.cxx \
    lexers/LexCSS.cxx \
    lexers/LexD.cxx \
    lexers/LexECL.cxx \
    lexers/LexEiffel.cxx \
    lexers/LexErlang.cxx \
    lexers/LexEScript.cxx \
    lexers/LexFlagship.cxx \
    lexers/LexForth.cxx \
    lexers/LexFortran.cxx \
    lexers/LexGAP.cxx \
    lexers/LexGui4Cli.cxx \
    lexers/LexHaskell.cxx \
    lexers/LexHTML.cxx \
    lexers/LexInno.cxx \
    lexers/LexKix.cxx \
    lexers/LexKVIrc.cxx \
    lexers/LexLaTeX.cxx \
    lexers/LexLisp.cxx \
    lexers/LexLout.cxx \
    lexers/LexLua.cxx \
    lexers/LexMagik.cxx \
    lexers/LexMarkdown.cxx \
    lexers/LexMatlab.cxx \
    lexers/LexMetapost.cxx \
    lexers/LexMMIXAL.cxx \
    lexers/LexModula.cxx \
    lexers/LexMPT.cxx \
    lexers/LexMSSQL.cxx \
    lexers/LexMySQL.cxx \
    lexers/LexNimrod.cxx \
    lexers/LexNsis.cxx \
    lexers/LexOpal.cxx \
    lexers/LexOScript.cxx \
    lexers/LexOthers.cxx \
    lexers/LexPascal.cxx \
    lexers/LexPB.cxx \
    lexers/LexPerl.cxx \
    lexers/LexPLM.cxx \
    lexers/LexPO.cxx \
    lexers/LexPOV.cxx \
    lexers/LexPowerPro.cxx \
    lexers/LexPowerShell.cxx \
    lexers/LexProgress.cxx \
    lexers/LexPS.cxx \
    lexers/LexPython.cxx \
    lexers/LexR.cxx \
    lexers/LexRebol.cxx \
    lexers/LexRuby.cxx \
    lexers/LexRust.cxx \
    lexers/LexScriptol.cxx \
    lexers/LexSmalltalk.cxx \
    lexers/LexSML.cxx \
    lexers/LexSorcus.cxx \
    lexers/LexSpecman.cxx \
    lexers/LexSpice.cxx \
    lexers/LexSQL.cxx \
    lexers/LexSTTXT.cxx \
    lexers/LexTACL.cxx \
    lexers/LexTADS3.cxx \
    lexers/LexTAL.cxx \
    lexers/LexTCL.cxx \
    lexers/LexTCMD.cxx \
    lexers/LexTeX.cxx \
    lexers/LexTxt2tags.cxx \
    lexers/LexVB.cxx \
    lexers/LexVerilog.cxx \
    lexers/LexVHDL.cxx \
    lexers/LexVisualProlog.cxx \
    lexers/LexYAML.cxx

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
