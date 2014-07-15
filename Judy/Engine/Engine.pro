
include(../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += Source

HEADERS += \
    Source/App.h \
    Source/Renderer.h \
    Source/Window.h \
    Source/Platforms.h \
    Source/Scene.h \
    Source/DXRenderer.h \
    Source/GLRenderer.h \
    Source/RenderTarget.h \
    Source/Color.h \
    Source/Matrix.h \
    Source/Vector.h \
    Source/DXSwapChain.h \
    Source/GLContext.h \
    Source/Win/WinGLContext.h \
    Source/Images.h

SOURCES += \
    Source/App.cpp \
    Source/Renderer.cpp \
    Source/Window.cpp \
    Source/Scene.cpp \
    Source/DXRenderer.cpp \
    Source/GLRenderer.cpp \
    Source/RenderTarget.cpp \
    Source/Color.cpp \
    Source/DXSwapChain.cpp \
    Source/GLContext.cpp \
    Source/Win/WinGLContext.cpp \
    Source/Images.cpp

win {
    INCLUDEPATH += Source/Windows
    HEADERS += Source/Win/WinWindow.h
    SOURCES += Source/Win/WinWindow.cpp
    HEADERS += Source/Win/WinApp.h
    SOURCES += Source/Win/WinApp.cpp
    HEADERS += Source/Win/WinRenderTarget.h
    SOURCES += Source/Win/WinRenderTarget.cpp
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
