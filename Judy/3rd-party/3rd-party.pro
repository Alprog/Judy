
TEMPLATE = subdirs
SUBDIRS += zlib libpng lua toLua

libpng.depends = zlib
toLua.depends = lua
