CC = gcc
CFLAGS = -g
LFLAGS = -lraylib -lm

BINARY = fern

all: main.c
	$(CC) -o $(BINARY) main.c $(CFLAGS) $(LFLAGS)

debug: main.c
	$(CC) -o $(BINARY) main.c $(CFLAGS) $(LFLAGS) -ggdb

run: all
	./$(BINARY)

