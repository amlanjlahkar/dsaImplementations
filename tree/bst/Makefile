CC=zig
CFLAGS=cc -Wall -Wextra -g -Og -std=c17

SRCDIR=src
OBJDIR=obj
BINDIR=bin

SRCFILES:=$(wildcard $(SRCDIR)/*.c)
OBJFILES:=$(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BIN:=$(BINDIR)/bst

$(OBJDIR) $(BINDIR):
	mkdir -p $@

$(BIN): $(OBJFILES) | $(BINDIR)
	$(if $(SRCFILES), $(CC) $(CFLAGS) $^ -o $@, \
	       	$(error source directory is empty))

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.DEFAULT_GOAL := $(BIN)

.PHONY: clean check
clean:
	rm -f $(OBJFILES) $(BIN)

check:
	$(MAKE) -s $(BIN)
	valgrind -q -s --leak-check=full ./$(BIN)

