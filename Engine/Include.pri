
win {
    INCLUDEPATH += "..\Engine\Source"
    INCLUDEPATH += "..\Engine\Source\Win"
    INCLUDEPATH += "..\3rd-party\lua\Source"

    LIBS += -L"..\Engine" -lEngine
    LIBS += -L"..\3rd-Party" -lzlib -llibpng -llua -lglslang -lspirv-cross
    PRE_TARGETDEPS += "..\Engine\Engine.lib"
    PRE_TARGETDEPS += "..\3rd-party\zlib.lib"
    PRE_TARGETDEPS += "..\3rd-party\libpng.lib"
    PRE_TARGETDEPS += "..\3rd-party\lua.lib"
    PRE_TARGETDEPS += "..\3rd-party\glslang.lib"

    LIBS += -ld3d12 -ldxgi -ld3dCompiler -lhid
    LIBS += -lUser32 -lGdi32 -lOpengl32 -lWs2_32 -lglew32s
    LIBS += -L"$$(VULKAN_SDK)/bin" -lvulkan-1
}

linux {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Linux"
    INCLUDEPATH += "../3rd-party/lua/Source"

    LIBS += -L"../Engine" -lEngine

    LIBS += -L"../3rd-party" -llibpng -llua -lzlib
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    PRE_TARGETDEPS += "../3rd-party/libzlib.a"
    PRE_TARGETDEPS += "../3rd-party/liblibpng.a"
    PRE_TARGETDEPS += "../3rd-party/liblua.a"

    LIBS += -lX11 -lGL -lGLEW -lpthread -ludev -levdev
}

mac {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Mac"
    INCLUDEPATH += "../3rd-party/lua/Source"

    LIBS += -L"../Engine" -lEngine
    LIBS += -L"../3rd-party" -lzlib -llibpng -llua
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    PRE_TARGETDEPS += "../3rd-party/libzlib.a"
    PRE_TARGETDEPS += "../3rd-party/liblibpng.a"
    PRE_TARGETDEPS += "../3rd-party/liblua.a"

    LIBS += -framework Cocoa -framework OpenGL
}
