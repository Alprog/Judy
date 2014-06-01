
win {
    INCLUDEPATH += "..\Engine\Source"
    INCLUDEPATH += "..\Engine\Source\Win"
    LIBS += -L"..\Engine\release" -lEngine
    PRE_TARGETDEPS += "..\Engine\release\Engine.lib"
    LIBS += -lUser32 -lGdi32 -lOpengl32
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
    LIBS += -framework Cocoa
}
