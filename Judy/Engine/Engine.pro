
include(../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += Source

HEADERS += \
    Source/App.h \
    Source/Renderer.h \
    Source/Window.h \
    Source/Platforms.h \
    Source/Context.h \

SOURCES += \
    Source/App.cpp \
    Source/Renderer.cpp \
    Source/Window.cpp \
    Source/Context.cpp \

win {
    INCLUDEPATH += Source/Windows
    HEADERS += Source/Win/WinWindow.h
    SOURCES += Source/Win/WinWindow.cpp
    HEADERS += Source/Win/WinApp.h
    SOURCES += Source/Win/WinApp.cpp
    HEADERS += Source/Win/WinContext.h
    SOURCES += Source/Win/WinContext.cpp
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

    HEADERS += \
        Source/Mac/MacWindow.h \
        Source/Mac/MacApp.h

    OBJECTIVE_SOURCES += \
        Source/Mac/MacWindow.mm \
        Source/Mac/MacApp.mm
}

OTHER_FILES += \
    Include.pri
