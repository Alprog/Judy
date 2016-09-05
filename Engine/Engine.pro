
include(../Default.pri)

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../3rd-party/lua/Source

subdirs = Source Source/Input Source/Meta Source/Math \
          Source/Net Source/LuaMachine Source/Containers Source/Render \
          Source/Render/GL

for(subdir, subdirs) {
    dirs += $$subdir

    win:   dirs += $$subdir/Win
    linux: dirs += $$subdir/Linux $$subdir/Unix
    mac:   dirs += $$subdir/Mac $$subdir/Unix
}

win: dirs += Source/Render/DX Source/Render/Vulkan "$$(Vulkan_SDK)/Include"
linux: dirs += /usr/include/libevdev-1.0

for(dir, dirs) {
    INCLUDEPATH += $$dir
    HEADERS += $$files($$dir/*.h)
    HEADERS += $$files($$dir/*.tpp)
    SOURCES += $$files($$dir/*.cpp)
    SOURCES += $$files($$dir/*.mm)
}

OTHER_FILES += \
    Include.pri
