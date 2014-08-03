
include(../../default.pri)

TEMPLATE = lib
TARGET = ../hlsl2glslfork
CONFIG += staticlib

INCLUDEPATH += \
    source \
    source/Include \
    source/MachineIndependent \

HEADERS += \
    source/GLSLCodeGen/glslCommon.h \
    source/GLSLCodeGen/glslFunction.h \
    source/GLSLCodeGen/glslOutput.h \
    source/GLSLCodeGen/glslStruct.h \
    source/GLSLCodeGen/glslSymbol.h \
    source/GLSLCodeGen/hlslCrossCompiler.h \
    source/GLSLCodeGen/hlslLinker.h \
    source/GLSLCodeGen/hlslSupportLib.h \
    source/GLSLCodeGen/propagateMutable.h \
    source/GLSLCodeGen/typeSamplers.h \
    source/Include/BaseTypes.h \
    source/Include/Common.h \
    source/Include/InfoSink.h \
    source/Include/InitializeGlobals.h \
    source/Include/InitializeParseContext.h \
    source/Include/intermediate.h \
    source/Include/PoolAlloc.h \
    source/Include/Types.h \
    source/MachineIndependent/hlslang_tab.h \
    source/MachineIndependent/Initialize.h \
    source/MachineIndependent/localintermediate.h \
    source/MachineIndependent/ParseHelper.h \
    source/MachineIndependent/RemoveTree.h \
    source/MachineIndependent/SymbolTable.h \
    source/MachineIndependent/preprocessor/mojoshader.h \
    source/MachineIndependent/preprocessor/mojoshader_internal.h \
    source/MachineIndependent/preprocessor/sourceloc.h \

SOURCES += \
    source/GLSLCodeGen/glslCommon.cpp \
    source/GLSLCodeGen/glslFunction.cpp \
    source/GLSLCodeGen/glslOutput.cpp \
    source/GLSLCodeGen/glslStruct.cpp \
    source/GLSLCodeGen/glslSymbol.cpp \
    source/GLSLCodeGen/hlslCrossCompiler.cpp \
    source/GLSLCodeGen/hlslLinker.cpp \
    source/GLSLCodeGen/hlslSupportLib.cpp \
    source/GLSLCodeGen/propagateMutable.cpp \
    source/GLSLCodeGen/typeSamplers.cpp \
    source/MachineIndependent/ConstantFolding.cpp \
    source/MachineIndependent/Gen_hlslang.cpp \
    source/MachineIndependent/Gen_hlslang_tab.cpp \
    source/MachineIndependent/HLSL2GLSL.cpp \
    source/MachineIndependent/InfoSink.cpp \
    source/MachineIndependent/Initialize.cpp \
    source/MachineIndependent/Intermediate.cpp \
    source/MachineIndependent/intermOut.cpp \
    source/MachineIndependent/IntermTraverse.cpp \
    source/MachineIndependent/ParseHelper.cpp \
    source/MachineIndependent/PoolAlloc.cpp \
    source/MachineIndependent/RemoveTree.cpp \
    source/MachineIndependent/SymbolTable.cpp \
    source/MachineIndependent/preprocessor/mojoshader.cpp \
    source/MachineIndependent/preprocessor/mojoshader_common.cpp \
    source/MachineIndependent/preprocessor/mojoshader_lexer.cpp \
    source/MachineIndependent/preprocessor/mojoshader_preprocessor.cpp \
    source/MachineIndependent/preprocessor/sourceloc.cpp \

win {
    INCLUDEPATH += source/OSDependent/Windows
    HEADERS += source/OSDependent/Windows/unistd.h
    HEADERS += source/OSDependent/Windows/osinclude.h
    SOURCES +=source/OSDependent/Windows/ossource.cpp
}

linux {
    INCLUDEPATH += source/OSDependent/Linux
    HEADERS +=source/OSDependent/Linux/osinclude.h
    SOURCES += source/OSDependent/Linux/ossource.cpp
}

