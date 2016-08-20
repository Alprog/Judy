
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

CONFIG += qt
QT += widgets

DEFINES += SCI_NAMESPACE

HEADERS += $$files(Source/*.h, true)
SOURCES += $$files(Source/*.cpp, true)

INCLUDEPATH += "../3rd-party/scintilla/include"

win: LIBS += -L"../3rd-party" -lscintillaedit3

linux: LIBS += -L"../3rd-party" -lScintillaEdit

mac: LIBS += -F"../3rd-party" -framework ScintillaEdit

RESOURCES = ide.qrc
