
# Platform defines

win32|win64:CONFIG += win
unix:!macx:CONFIG += linux
macx:CONFIG += mac

win:DEFINES += WIN
linux:DEFINES += LINUX
mac:DEFINES += MAC

# Default settings

CONFIG -= qt
CONFIG -= debug_and_release debug_and_release_target
CONFIG += c++11

win|mac {
    QMAKE_CXXFLAGS += /wd4250 /wd4800 /wd5030
}

linux {
    QMAKE_CXXFLAGS += -std=c++0x -fpermissive -Wno-attribute
}

#QMAKE_CFLAGS_RELEASE -= -MD
#QMAKE_CFLAGS_RELEASE += -MT
#QMAKE_CXXFLAGS_RELEASE -= -MD
#QMAKE_CXXFLAGS_RELEASE += -MT
