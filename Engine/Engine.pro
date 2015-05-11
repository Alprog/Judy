
include(../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
    Source \
    Source/Math \
    ../3rd-party/lua/source \

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
    Source/Meta/FieldMeta.h \
    Source/Meta/MethodMeta.h \
    Source/Meta/Meta.h \
    Source/Meta/Serializer.h \
    Source/Meta/Binder.h \
    Source/Meta/ConstructorMeta.h \
    Source/Meta/FunctionMeta.h \
    Source/Meta/ClassDefiner.h \
    Source/Meta/ITypeMeta.h \
    Source/Meta/BaseType.h \
    Source/Meta/Any.h \
    Source/Meta/AnyData.h \
    Source/Singleton.h \
    Source/Meta/Sfinae.h \
    Source/Meta/ClassMeta.h \
    Source/Meta/PointerTypeMeta.h

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
    Source/Meta/TypeMeta.cpp \
    Source/Meta/FieldMeta.cpp \
    Source/Meta/MethodMeta.cpp \
    Source/Meta/Any.cpp \
    Source/Meta/Meta.cpp \
    Source/Meta/MetaGen.cpp \
    Source/Meta/Serializer.cpp \
    Source/Meta/Binder.cpp \
    Source/Meta/ConstructorMeta.cpp \
    Source/Meta/FunctionMeta.cpp \
    Source/Meta/ITypeMeta.cpp \
    Source/Meta/AnyData.cpp \
    Source/Singleton.cpp \
    Source/Meta/NewMeta.cpp

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
