
TEMPLATE = subdirs
SUBDIRS += zlib libpng lua scintilla

libpng.depends = zlib
