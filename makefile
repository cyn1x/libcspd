CC=clang
INCLUDE=$(shell find ./include -type f -name '*.h')
CFLAGS=-g -Wall -Wextra -Werror -pedantic -pedantic-errors $(addprefix -I,$(dir $(INCLUDE))) -std=c17

SRCDIR=src
OBJDIR=obj
BINDIR=bin
TESTS=$(shell find $(TESTDIR) -type f -name '*.c')
SRCS=$(shell find $(SRCDIR) -type f -name '*.c')
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BINS=$(BINDIR)/libturboc.so tests/bin/libturboc
ZIPS=$(BINDIR)/turboc.tar.gz $(BINDIR)/turboc.so.tar.gz

all: $(BINS)

release: CFLAGS=-Wall -pedantic -O2 -DNDEBUG -std=c17
release: clean
release: $(BINS)

tests/bin/libturboc: $(TESTS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(BINDIR) -lturboc

$(BINDIR)/libturboc.so: $(OBJS)
	$(CC) $(CFLAGS) -fPIC -shared $(addprefix $(OBJDIR)/, $(notdir $(OBJS))) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

clean:
	$(RM) $(BINDIR)/*.o $(BINDIR)/*.so $(OBJDIR)/*.o tests/bin/libturboc
