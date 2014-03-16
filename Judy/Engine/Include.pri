
win {
    INCLUDEPATH += "..\Engine\Source"
    INCLUDEPATH += "..\Engine\Source\Windows"
    LIBS += -L"..\Engine\release" -lEngine
    PRE_TARGETDEPS += "..\Engine\release\Engine.lib"
}

linux {
    INCLUDEPATH += "..\Engine\Source"
    INCLUDEPATH += "..\Engine\Source\Linux"
    LIBS += -L"../Engine" -lEngine
    PRE_TARGETDEPS += "../Engine/libEngine.a"
    LIBS += -lX11
}
