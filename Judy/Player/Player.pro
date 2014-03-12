
TEMPLATE = app

INCLUDEPATH += "..\Engine\Source"
LIBS += -L"..\Engine\release" -lEngine
PRE_TARGETDEPS += "..\Engine\release\Engine.lib"

SOURCES += \
    Source/Main.cpp
