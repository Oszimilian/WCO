Flags = -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 
HeaderDir = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/local/include/ImageMagick-7
ObjectFiles = main.o GUI.o PDF.o PNG.o Worksheet_Creat.o GUI_Call.o Worksheet_Status.o GUI_Status.o GUI_Update.o Worksheet_Creat_Fraction.o
LiberyLink = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -export-dynamic  /usr/local/lib/libhpdf.a -L/usr/local/lib -lz -lm -lpthread -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI -llzma -ljbig -ljpeg -lpng -ltiff
KP1 = -Wall -g $(LiberyLink) $(HeaderDir)
KP = -Wall -g  $(Flags)  $(HeaderDir)

prog: $(ObjectFiles)
	gcc -o prog $(ObjectFiles) $(Flags) $(LiberyLink) 

main.o: main.c
	gcc $(KP) -c main.c


GUI.o: GUI.c
	gcc $(KP) -c GUI.c

GUI_Call.o: GUI_Call.c
	gcc $(KP) -c GUI_Call.c

PDF.o: PDF.c
	gcc $(KP) -c PDF.c

PNG.o: PNG.c
	gcc $(KP) -c PNG.c

Worksheet_Creat.o: Worksheet_Creat.c
	gcc $(KP) -c Worksheet_Creat.c

Worksheet_Status.o: Worksheet_Status.c
	gcc $(KP) -c Worksheet_Status.c

GUI_Status.o: GUI_Status.c
	gcc $(KP) -c GUI_Status.c

GUI_Update.o: GUI_Update.c
	gcc $(KP) -c GUI_Update.c

Worksheet_Creat_Fraction.o: Worksheet_Creat_Fraction.c
	gcc $(KP) -c Worksheet_Creat_Fraction.c

clean:
	rm *.o 
