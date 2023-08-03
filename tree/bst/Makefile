CC=zig
CFLAGS=cc -Wall -Wextra -g -Og -std=c17

SRCDIR=src
OBJDIR=obj

SRCFILES:=$(wildcard $(SRCDIR)/*.c)
OBJFILES:=$(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BIN=bst

ifndef vb
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
	valgrind -q -s --leak-check=full ./$(BIN)

