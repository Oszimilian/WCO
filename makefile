CC = gcc
CCF = -Wall -g
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))
BIN = bin/prog

Flags = -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 
HeaderDir = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/local/include/ImageMagick-7 -I/home/maximilian/Git/WCO/headers
LiberyLink = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -export-dynamic  /usr/local/lib/libhpdf.a -L/usr/local/lib -lz -lm -lpthread -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI -llzma -ljbig -ljpeg -lpng -ltiff
KP_old =   $(Flags) $(HeaderDir) $(LiberyLink)

LibGTK_Lin = $(shell pkg-config --libs gtk+-3.0)
FlagGTK_Lin = $(shell pkg-config --cflags gtk+-3.0)
LibGTK_Win = -LC:/msys64/mingw64/bin/../lib -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -Wl,-luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl
FlagGTK_Win = -IC:/msys64/mingw64/bin/../include/gtk-3.0 -IC:/msys64/mingw64/bin/../include/pango-1.0 -IC:/msys64/mingw64/bin/../include -IC:/msys64/mingw64/bin/../include/glib-2.0 -IC:/msys64/mingw64/bin/../lib/glib-2.0/include -IC:/msys64/mingw64/bin/../include/harfbuzz -IC:/msys64/mingw64/bin/../include/freetype2 -IC:/msys64/mingw64/bin/../include/libpng16 -IC:/msys64/mingw64/bin/../include/fribidi -IC:/msys64/mingw64/bin/../include/cairo -IC:/msys64/mingw64/bin/../include/lzo -IC:/msys64/mingw64/bin/../include/pixman-1 -IC:/msys64/mingw64/bin/../include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/bin/../include/atk-1.0 -mms-bitfields
DynGTK = -export-dynamic

LibLibHaru_Lin = /usr/local/lib/libhpdf.a -L/usr/local/lib -lz -lm -lpthread
LibLibHaru_Win = C:/cygwin64/usr/local/lib/libhpdf.a -lz -lm -lpthread -IC:/cygwin64/usr/local/include

LibIM_Lin = $(shell pkg-config --libs MagickWand) -llzma -ljbig -ljpeg -lpng -ltiff
FlagIM_Lin = $(shell pkg-config --cflags MagickWand)
LibIM_Win = -LC:/msys64/mingw64/bin/../lib -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI
FlagIM_Win = -IC:/msys64/mingw64/bin/../include/ImageMagick-7 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -D_DLL -D_MT

FlagWCO_Lin = -I/home/maximilian/Git/WCO/headers
FlagWCO_Win = -IC:\msys64\home\maximilian\WCO\headers


KP = $(LibGTK_Lin) $(LibLibHaru_Lin) $(LibIM_Lin) $(FlagWCO_Lin) $(FlagGTK_Lin) $(FlagIM_Lin) $(DynGTK)
#KP = $(LibGTK_Win) $(LibLibHaru_Win) $(LibIM_Win) $(FlagWCO_Win) $(FlagGTK_Win) $(FlagIM_Win) 

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(KP) -o $@

obj/%.o: src/%.c
	$(CC) $(CCF) $(KP) -c $< -o $@

clean:
	rm  $(BIN)
