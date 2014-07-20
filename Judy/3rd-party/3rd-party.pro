
TEMPLATE = subdirs
SUBDIRS += zlib libpng lua toLua scintilla

libpng.depends = zlib
toLua.depends = lua
