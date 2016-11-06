
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

CONFIG += qt
QT += widgets

DEFINES += SCI_NAMESPACE

HEADERS += $$files(Source/*.h, true)
SOURCES += $$files(Source/*.cpp, true)

LIBS += -L"../3rd-Party" -lglslang -lspirv-cross

INCLUDEPATH += "../3rd-party/scintilla/include"
INCLUDEPATH += "../3rd-party/glslang/Source"
INCLUDEPATH += "../3rd-party/spirv-cross/Source"

win: LIBS += -L"../3rd-party" -lscintillaedit3

linux: LIBS += -L"../3rd-party" -lScintillaEdit

mac: LIBS += -F"../3rd-party" -framework ScintillaEdit

RESOURCES = ide.qrc
