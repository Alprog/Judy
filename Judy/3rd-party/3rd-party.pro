
TEMPLATE = subdirs
SUBDIRS += zlib libpng lua toLua scintilla hlsl2glslfork

libpng.depends = zlib
toLua.depends = lua
