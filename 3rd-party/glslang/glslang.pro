
include(../../Default.pri)

TEMPLATE = lib
TARGET = ../glslang
CONFIG += staticlib

dirs += \
    Source/glslang/Include \
    Source/glslang/Public \
    Source/glslang/GenericCodeGen \
    Source/glslang/MachineIndependent \
    Source/glslang/MachineIndependent/preprocessor \
    Source/glslang/OSDependent \
    Source/hlsl \
    Source/SPIRV \
    Source/OGLCompilersDLL

win: dirs += Source/glslang/OSDependent/Windows
unix: dirs += Source/glslang/OSDependent/Unix

for(dir, dirs) {
    INCLUDEPATH += $$dir
    HEADERS += $$files($$dir/*.h)
    SOURCES += $$files($$dir/*.cpp)
}
