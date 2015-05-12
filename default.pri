
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

linux {
    QMAKE_CXXFLAGS += -std=c++0x -fpermissive
}
