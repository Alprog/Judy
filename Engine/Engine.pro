
include(../default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
    Source \
    Source/Math \
    Source/LuaMachine \
    Source/Containers \
    ../3rd-party/lua/source

HEADERS += \
    Source/*.h \
    Source/Meta/*.h \
    Source/Math/*.h \
    Source/LuaMachine/*.h \
    Source/Unix/*.h \
    Source/Win/*.h \
    Source/Linux/*.h \
    Source/Mac/*.h \
    Source/Net/*.h \
    Source/Platform.h \
    Source/Math/Quaternion.h \
    Source/Math/Transform.h \
    Source/Vertex.h \
    Source/Mesh.h \
    Source/Material.h \
    Source/Model.h \
    Source/Containers/List.h \
    Source/Meta/IMemberMeta.h \
    Source/Lua.h \
    Source/Containers/Map.h \
    Source/Containers/Set.h

SOURCES += \
    Source/App.cpp \
    Source/Renderer.cpp \
    Source/Window.cpp \
    Source/Scene.cpp \
    Source/Color.cpp \
    Source/Images.cpp \
    Source/Node.cpp \
    Source/Quad.cpp \
    Source/Math/Matrix.cpp \
    Source/Math/Vector2.cpp \
    Source/Math/Vector3.cpp \
    Source/Math/Vector4.cpp \
    Source/Keyframe.cpp \
    Source/Meta/TypeMeta.cpp \
    Source/Meta/FieldMeta.cpp \
    Source/Meta/MethodMeta.cpp \
    Source/Meta/Any.cpp \
    Source/Meta/Meta.cpp \
    Source/Meta/Serializer.cpp \
    Source/Meta/Binder.cpp \
    Source/Meta/ConstructorMeta.cpp \
    Source/Meta/FunctionMeta.cpp \
    Source/Meta/ITypeMeta.cpp \
    Source/Meta/AnyData.cpp \
    Source/Meta/NewMeta.cpp \
    Source/Singleton.cpp \
    Source/Pipe.cpp \
    Source/LuaMachine/Breakpoints.cpp \
    Source/LuaMachine/LuaMachine.cpp \
    Source/Net/NetNode.cpp \
    Source/Net/Socket.cpp \
    Source/DeepPointer.cpp \
    Source/Meta/Meta.gen.cpp \
    Source/Meta/CFunctionMeta.cpp \
    Source/LuaMachine/LogMessage.cpp \
    Source/LuaMachine/DebugCommand.cpp \
    Source/Process.cpp \
    Source/LuaMachine/CallInfo.cpp \
    Source/LuaMachine/CallStack.cpp \
    Source/LuaMachine/FileBreakpoints.cpp \
    Source/Path.cpp \
    Source/Utils.cpp \
    Source/Platform.cpp \
    Source/Math/Quaternion.cpp \
    Source/Math/Transform2D.cpp \
    Source/Math/Transform.cpp \
    Source/Vertex.cpp \
    Source/Mesh.cpp \
    Source/Material.cpp \
    Source/Model.cpp \
    Source/Meta/IMemberMeta.cpp

win {
    INCLUDEPATH += Source/Windows

    SOURCES += \
        Source/Win/WinWindow.cpp \
        Source/Win/WinApp.cpp \
        Source/DXSwapChain.cpp \
        Source/Win/WinRenderTarget.cpp \
        Source/Win/WinProcess.cpp \
        Source/Win/WinSocket.cpp \
        Source/GLRenderer.cpp \
        Source/GLContext.cpp \
        Source/RenderTarget.cpp \
        Source/DXRenderer.cpp \
        Source/Win/WinGLContext.cpp \
        Source/DXShaderResource.cpp
}

linux {
    INCLUDEPATH += Source/Linux

    SOURCES += \
        Source/Linux/LinuxWindow.cpp \
        Source/Linux/LinuxApp.cpp \
        Source/Unix/UnixSocket.cpp \
        Source/Unix/UnixProcess.cpp
}

mac {
    INCLUDEPATH += Source/Mac

    SOURCES += \
        Source/Unix/UnixSocket.cpp \
        Source/Unix/UnixProcess.cpp

    OBJECTIVE_SOURCES += \
        Source/Mac/MacWindow.mm \
        Source/Mac/MacApp.mm
}

OTHER_FILES += \
    Include.pri
