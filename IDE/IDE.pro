
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

CONFIG += qt
QT += widgets

HEADERS += \
    Source/MainWindow.h \
    Source/Document.h \
    Source/TextEditor.h \
    Source/DocumentsPane.h \
    Source/OutputPane.h \
    Source/RemotePlayer.h \
    Source/Utils.h \
    Source/Menu/BaseMenu.h \
    Source/Menu/DebugMenu.h \
    Source/Menu/FileMenu.h

SOURCES += \
    Source/MainWindow.cpp \
    Source/Main.cpp \
    Source/Document.cpp \
    Source/TextEditor.cpp \
    Source/DocumentsPane.cpp \
    Source/OutputPane.cpp \
    Source/RemotePlayer.cpp \
    Source/Utils.cpp \
    Source/Menu/BaseMenu.cpp \
    Source/Menu/DebugMenu.cpp \
    Source/Menu/FileMenu.cpp

INCLUDEPATH += "../3rd-party/scintilla/include"

win {
    LIBS += -L"../3rd-party" -lscintillaedit3
}

linux {
    LIBS += -L"../3rd-party" -lScintillaEdit
}

mac {
    LIBS += -F"../3rd-party" -framework ScintillaEdit
}

RESOURCES = ide.qrc
