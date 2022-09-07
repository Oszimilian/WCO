#CC = i686-w64-mingw32-gcc
CC = gcc
CCF = -Wall -g
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))
BIN = bin/wco
HEAD = -I/home/maximilian/git/WCO/WCO_Start/header


$(BIN): $(OBJS)
	$(CC) $(OBJS) $(HEAD) -o $@

obj/%.o: src/%.c
	$(CC) $(CCF) $(HEAD) -c $< -o $@

clean: 
	rm $(BIN)