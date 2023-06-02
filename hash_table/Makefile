CC=zig
CFLAGS=cc -Wall -g
SRC=src
BIN=bin/main

.PHONY: all clean
all:
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(BIN)
	$(BIN)

clean:
	rm -rv $(BIN)

