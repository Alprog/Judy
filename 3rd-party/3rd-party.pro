
TEMPLATE = subdirs
SUBDIRS += zlib libpng lua scintilla glslang spirv-cross

libpng.depends = zlib
