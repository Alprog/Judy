
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

CONFIG += qt
QT += widgets

HEADERS += \
    Source/MainWindow.h \
    Source/Document.h \
    Source/DocumentsPane.h \
    Source/OutputPane.h \
    Source/RemotePlayer.h \
    Source/Menu/BaseMenu.h \
    Source/Menu/DebugMenu.h \
    Source/Menu/FileMenu.h \
    Source/Menu/WindowMenu.h \
    Source/StackPane.h \
    Source/Settings.h \
    Source/IDE.h \
    Source/LuaDocement.h \
    Source/SceneDocument.h \
    Source/CodeEditor.h \
    Source/DocumentType.h \
    Source/HierarchyPane.h \
    Source/InspectorPane.h

SOURCES += \
    Source/MainWindow.cpp \
    Source/Main.cpp \
    Source/Document.cpp \
    Source/DocumentsPane.cpp \
    Source/OutputPane.cpp \
    Source/RemotePlayer.cpp \
    Source/Menu/BaseMenu.cpp \
    Source/Menu/DebugMenu.cpp \
    Source/Menu/FileMenu.cpp \
    Source/Menu/WindowMenu.cpp \
    Source/StackPane.cpp \
    Source/Settings.cpp \
    Source/IDE.cpp \
    Source/LuaDocement.cpp \
    Source/SceneDocument.cpp \
    Source/CodeEditor.cpp \
    Source/HierarchyPane.cpp \
    Source/InspectorPane.cpp

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

LIBS += -lglew32s
