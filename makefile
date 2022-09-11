CC = gcc
CCF = -g
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))
BIN = bin/prog

LibGTK_Lin = $(shell pkg-config --libs gtk+-3.0)
FlagGTK_Lin = $(shell pkg-config --cflags gtk+-3.0)

DynGTK = -export-dynamic

LibLibHaru_Lin = /usr/local/lib/libhpdf.a -L/usr/local/lib -lz -lm -lpthread
LibLibHaru_Win = C:/cygwin64/usr/local/lib/libhpdf.a -lz -lm -lpthread -IC:/cygwin64/usr/local/include

LibIM_Lin = $(shell pkg-config --libs MagickWand) -llzma -ljpeg -lpng -ltiff
FlagIM_Lin = $(shell pkg-config --cflags MagickWand)

LibIM_Cyg = -LC:/msys64/mingw64/lib -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI
FlagIm_Cyg = -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -D_DLL -D_MT -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -D_DLL -D_MT -IC:/msys64/mingw64/include/ImageMagick-7

FlagWCO_Lin = -I/home/maximilian/Git/WCO/headers
FlagWCO_Win = -IC:\msys64\home\maximilian\Git\WCO\headers


KP = $(LibGTK_Lin) $(LibLibHaru_Lin) $(LibIM_Lin) $(FlagWCO_Lin) $(FlagGTK_Lin) $(FlagIM_Lin) $(DynGTK)
#KP = $(LibGTK_Lin) $(LibLibHaru_Win) $(LibIM_Lin) $(FlagWCO_Win) $(FlagGTK_Lin) $(FlagIM_Lin) 
#KP = $(LibGTK_Lin) $(LibLibHaru_Win) $(LibIM_Cyg) $(FlagWCO_Win) $(FlagGTK_Lin) $(FlagIm_Cyg) -rdynamic

$(BIN): $(OBJS)
	$(CC) $(CCF) $(OBJS) $(KP) -o $@

obj/%.o: src/%.c
	$(CC) $(CCF) $(KP) -c $< -o $@

clean:
	rm  $(BIN)
