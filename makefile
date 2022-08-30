CC = gcc
CCF = -Wall -g
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))
BIN = bin/prog

Flags = -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 
HeaderDir = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/local/include/ImageMagick-7 -I/home/maximilian/Git/WCO/headers
LiberyLink = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -export-dynamic  /usr/local/lib/libhpdf.a -L/usr/local/lib -lz -lm -lpthread -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI -llzma -ljbig -ljpeg -lpng -ltiff
KP_old =   $(Flags) $(HeaderDir) $(LiberyLink)

LibGTK = $(shell pkg-config --libs gtk+-3.0)
FlagGTK = $(shell pkg-config --cflags gtk+-3.0)
DynGTK = -export-dynamic
LibLibHaru_Lin = /usr/local/lib/libhpdf.a -L/usr/local/lib -lz -lm -lpthread
LibLibHaru_Win = C:/cygwin64/usr/local/lib/libhpdf.a -lz -lm -lpthread -IC:/cygwin64/usr/local/include
LibIM = $(shell pkg-config --libs MagickWand) -llzma -ljbig -ljpeg -lpng -ltiff
FlagIM = $(shell pkg-config --cflags MagickWand)
FlagWCO_Lin = -I/home/maximilian/Git/WCO/headers
FlagWCO_Win = -IC:\msys64\home\maximilian\WCO\headers


KP = $(LibGTK) $(LibLibHaru_Lin) $(LibIM) $(FlagWCO_Lin) $(FlagGTK) $(FlagIM) $(DynGTK)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(KP) -o $@

obj/%.o: src/%.c
	$(CC) $(CCF) $(KP) -c $< -o $@

clean:
	rm  $(BIN)
