.SUFFIXES: .c .o .h .a

CFLAGS:=$(shell pkg-config --cflags gtk+-3.0)
LIBS:=$(shell pkg-config --libs gtk+-3.0 gthread-2.0 gmodule-2.0)

all: bait

.c.o:
	g++ -DGTK -c $< -o $@ -I scintilla/include $(CFLAGS)
bait: bait.o scintilla/bin/scintilla_win.a
	gcc -DGTK $^ -o win $(LIBS) -lstdc++ -enable-auto-import
clean:
	rm -rf bait *.o