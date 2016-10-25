
include(../../Default.pri)

TEMPLATE = lib
TARGET = ../spirv-cross
CONFIG += staticlib

SOURCES += \
	Source/main.cpp \
	Source/spirv_cross.cpp \
	Source/spirv_cpp.cpp \
        Source/spirv_glsl.cpp \
        Source/spirv_msl.cpp
