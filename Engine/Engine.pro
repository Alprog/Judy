
include(../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
    Source \
    Source/Math \
    ../../../3rd-party/toLua++ \
    ../../../3rd-party/lua/source \

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
    Source/Vector.h \
    Source/DXSwapChain.h \
    Source/GLContext.h \
    Source/Win/WinGLContext.h \
    Source/Images.h \
    Source/Node.h \
    Source/Quad.h \
    Source/Math/Matrix.h \
    Source/Math/Vector2.h \
    Source/Math/Vector3.h \
    Source/Math/Vector4.h \
    Source/DXShaderResource.h \
    Source/Keyframe.h \
    Source/Math/Transform.h \
    Source/Meta/TypeMeta.h \
    Source/Meta/Variant.h \
    Source/Meta/FieldMeta.h \
    Source/Meta/MethodMeta.h \
    Source/Meta/MetaDefiner.h \
    Source/Meta/Any.h

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
    Source/Images.cpp \
    Source/Node.cpp \
    Source/Quad.cpp \
    Source/Math/Matrix.cpp \
    Source/Math/Vector2.cpp \
    Source/Math/Vector3.cpp \
    Source/Math/Vector4.cpp \
    Source/DXShaderResource.cpp \
    Source/Keyframe.cpp \
    Source/Math/Transform.cpp \
    Source/Binding.cpp \
    Source/Meta/TypeMeta.cpp \
    Source/Meta/Variant.cpp \
    Source/Meta/FieldMeta.cpp \
    Source/Meta/MethodMeta.cpp \
    Source/Meta/Any.cpp

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
