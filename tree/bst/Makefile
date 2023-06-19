CC=zig
CFLAGS=cc -Wall -g -Og -std=c17

SRCDIR=src
OBJDIR=obj

SRCFILES:=$(wildcard $(SRCDIR)/*.c)
OBJFILES:=$(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BIN=bst

ifndef verbose
.SILENT:
endif

all: $(BIN)

$(BIN): $(OBJFILES)
	$(if $(SRCFILES), $(CC) $(CFLAGS) $^ -o $@, \
	       	$(error source directory is empty))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(shell [ ! -d $(@D) ] && mkdir $(@D))
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run
clean:
	rm -f $(OBJDIR)/*.o $(BIN)

run:
	$(MAKE) -s $(BIN)
	./$(BIN)

