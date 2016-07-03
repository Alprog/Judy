
win {
    INCLUDEPATH += "..\Engine\Source"
    INCLUDEPATH += "..\Engine\Source\Win"
    INCLUDEPATH += "..\3rd-Party\lua\Source"

    LIBS += -L"..\Engine" -lEngine
    LIBS += -L"..\3rd-Party" -lzlib -llibpng -llua
    PRE_TARGETDEPS += "..\Engine\Engine.lib"
    PRE_TARGETDEPS += "..\3rd-Party\zlib.lib"
    PRE_TARGETDEPS += "..\3rd-Party\libpng.lib"
    PRE_TARGETDEPS += "..\3rd-Party\lua.lib"

    LIBS += -ld3d12 -ldxgi -ld3dCompiler
    LIBS += -lUser32 -lGdi32 -lOpengl32 -lWs2_32
    LIBS += -L"$$(VULKAN_SDK)/bin" -lvulkan-1
}

linux {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Linux"
    INCLUDEPATH += "../3rd-Party/lua/Source"

    LIBS += -L"../Engine" -lEngine
    LIBS += -L"../3rd-Party" -lzlib -llibpng -llua
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    PRE_TARGETDEPS += "../3rd-Party/libzlib.a"
    PRE_TARGETDEPS += "../3rd-Party/liblibpng.a"
    PRE_TARGETDEPS += "../3rd-Party/liblua.a"

    LIBS += -lX11 -lGL
}

mac {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Mac"
    INCLUDEPATH += "../3rd-Party/lua/Source"

    LIBS += -L"../Engine" -lEngine
    LIBS += -L"../3rd-Party" -lzlib -llibpng -llua
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    PRE_TARGETDEPS += "../3rd-Party/libzlib.a"
    PRE_TARGETDEPS += "../3rd-Party/liblibpng.a"
    PRE_TARGETDEPS += "../3rd-Party/liblua.a"

    LIBS += -framework Cocoa -framework OpenGL
}
