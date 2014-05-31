
include(../default.pri)

TEMPLATE = lib
CONFIG += staticlib

CONFIG -= qt

INCLUDEPATH += Source

HEADERS += \
    Source/App.h \
    Source/Renderer.h \
    Source/Window.h \
    Source/Platforms.h \


SOURCES += \
    Source/App.cpp \
    Source/Renderer.cpp \
    Source/Window.cpp \

win {
    INCLUDEPATH += Source/Windows
    HEADERS += Source/Win/WinWindow.h
    SOURCES += Source/Win/WinWindow.cpp
    HEADERS += Source/Win/WinApp.h
    SOURCES += Source/Win/WinApp.cpp
}

linux {
    INCLUDEPATH += Source/Linux
    HEADERS += Source/Linux/LinuxWindow.h
    SOURCES += Source/Linux/LinuxWindow.cpp
    HEADERS += Source/Linux/LinuxApp.h
    SOURCES += Source/Linux/LinuxApp.cpp
}

mac {
    INCLUDEPATH += Source/Mac
    HEADERS += Source/Mac/MacWindow.h
    SOURCES += Source/Mac/MacWindow.cpp
    HEADERS += Source/Mac/MacApp.h
    SOURCES += Source/Mac/MacApp.cpp
}
