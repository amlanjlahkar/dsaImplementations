CC=gcc
CFLAGS=-I.
DEPS=list_operations.h
OBJ=list_operations.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

output: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rv ./*.o
