
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
    Source/Containers/Set.h \
    Source/Attributes.h \
    Source/Meta/PropertyMeta.h \
    Source/Meta/IFunctionMeta.h \
    Source/Meta/IndexSequence.h \
    Source/Meta/IConstructorMeta.h \
    Source/Meta/IClassMeta.h \
    Source/Meta/IFieldMeta.h \
    Source/Object.h \
    Source/Ref.h \
    Source/TextureManager.h \
    Source/ShaderManager.h \
    Source/Render/Renderer.h \
    Source/Render/RendererResource.h \
    Source/Render/Impl.h \
    Source/Render/Texture.h \
    Source/Render/Shader.h \
    Source/Render/IndexBuffer.h \
    Source/Render/RenderCommand.h \
    Source/Render/RendererFrontend.h \
    Source/Render/RenderManager.h \
    Source/Render/RenderState.h \
    Source/Render/VertexBuffer.h \
    Source/Render/RendererType.h \
    Source/Render/DX/DXIndexBufferImpl.h \
    Source/Render/DX/DXPipelineState.h \
    Source/Render/DX/DXRenderer.h \
    Source/Render/DX/DXSwapChain.h \
    Source/Render/DX/DXVertexBufferImpl.h \
    Source/Render/GL/GLContext.h \
    Source/Render/GL/GLIndexBufferImpl.h \
    Source/Render/GL/GLRenderer.h \
    Source/Render/GL/GLShaderImpl.h \
    Source/Render/GL/GLTextureImpl.h \
    Source/Render/GL/GLVertexBufferImpl.h \
    Source/Render/GL/gl.h \
    Source/Render/DX/dx.h \
    Source/Render/DX/DXConstantBufferImpl.h \
    Source/Render/GL/GLConstantBufferImpl.h \
    Source/Render/ConstantBuffer.h \
    Source/Render/DX/DXTextureImpl.h \
    Source/Render/DX/DXShaderImpl.h \
    Source/Render/RendererBase.h \
    Source/Render/DX/DXDescriptorHeap.h \
    Source/Render/DX/DXDescriptorHandle.h

SOURCES += \
    Source/App.cpp \
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
    Source/Meta/IMemberMeta.cpp \
    Source/Meta/PropertyMeta.cpp \
    Source/Meta/IClassMeta.cpp \
    Source/Object.cpp \
    Source/Lua.cpp \
    Source/TextureManager.cpp \
    Source/ShaderManager.cpp \
    Source/Render/Texture.cpp \
    Source/Render/DX/DXIndexBufferImpl.cpp \
    Source/Render/DX/DXPipelineState.cpp \
    Source/Render/DX/DXVertexBufferImpl.cpp \
    Source/Render/GL/GLContext.cpp \
    Source/Render/GL/GLIndexBufferImpl.cpp \
    Source/Render/GL/GLRenderer.cpp \
    Source/Render/GL/GLShaderImpl.cpp \
    Source/Render/GL/GLTextureImpl.cpp \
    Source/Render/GL/GLVertexBufferImpl.cpp \
    Source/Render/IndexBuffer.cpp \
    Source/Render/RenderCommand.cpp \
    Source/Render/Renderer.cpp \
    Source/Render/RendererFrontend.cpp \
    Source/Render/RenderManager.cpp \
    Source/Render/RenderState.cpp \
    Source/Render/VertexBuffer.cpp \
    Source/Render/Shader.cpp \
    Source/Render/DX/DXConstantBufferImpl.cpp \
    Source/Render/GL/GLConstantBufferImpl.cpp \
    Source/Render/ConstantBuffer.cpp \
    Source/Render/DX/DXTextureImpl.cpp \
    Source/Render/DX/DXShaderImpl.cpp \
    Source/Render/Impl.cpp \
    Source/Render/DX/DXDescriptorHeap.cpp \
    Source/Render/DX/DXDescriptorHandle.cpp

win {
    INCLUDEPATH += Source/Windows

    SOURCES += \
        Source/Win/WinWindow.cpp \
        Source/Win/WinApp.cpp \
        Source/Win/WinRenderTarget.cpp \
        Source/Win/WinProcess.cpp \
        Source/Win/WinSocket.cpp \
        Source/Render/GL/GLRenderer.cpp \
        Source/Render/GL/GLContext.cpp \
        Source/Render/RenderTarget.cpp \
        Source/Render/DX/DXRenderer.cpp \
        Source/Render/DX/DXSwapChain.cpp \
        Source/Win/WinGLContext.cpp
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
