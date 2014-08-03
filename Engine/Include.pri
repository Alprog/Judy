
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


    LIBS += -lUser32 -lGdi32 -ld3d11 -ldxgi -lOpengl32
    LIBS += -ld3dCompiler
}

linux {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Linux"
    LIBS += -L"../Engine" -lEngine
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    LIBS += -lX11 -lGL
}

mac {
    INCLUDEPATH += "../Engine/Source"
    INCLUDEPATH += "../Engine/Source/Mac"
    LIBS += -L"../Engine" -lEngine
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    LIBS += -framework Cocoa -framework OpenGL
}
