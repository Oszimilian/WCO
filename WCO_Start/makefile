#CC = i686-w64-mingw32-gcc
CC = x86_64-w64-mingw32
#CC = gcc
CCF = -Wall -g
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))
BIN = bin/wco
HEAD = -I/home/maximilian/git/WCO/WCO_Start/header


$(BIN): $(OBJS)
	$(CC) $(CCF) $(OBJS) -o $@

obj/%.o: src/%.c
	$(CC) $(CCF) -c $< -o $@

clean: 
	rm $(BIN)