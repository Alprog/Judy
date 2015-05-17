
include(../Default.pri)
include(../Engine/Include.pri)

TEMPLATE = app

CONFIG += qt
QT += widgets

HEADERS += \
    Source/MainWindow.h \
    Source/TextEditor.h \
    Source/Document.h \
    Source/DocumentsPane.h

SOURCES += \
    Source/Main.cpp \
    Source/MainWindow.cpp \
    Source/TextEditor.cpp \
    Source/Document.cpp \
    Source/DocumentsPane.cpp

INCLUDEPATH += "../3rd-party/scintilla/include"

win {
    LIBS += -L"../3rd-party" -lscintillaedit3
}

linux {
    LIBS += -L"../3rd-party" -lScintillaEdit
}

RESOURCES = ide.qrc
