CC=clang
INCLUDE=-I./include -I./include/dsa/vector
CFLAGS=-g -Wall -Wextra -Werror -pedantic -pedantic-errors $(INCLUDE) -std=c17

SRCDIR=src
OBJDIR=obj
BINDIR=bin
TESTDIR=tests
TESTBINDIR=tests/bin
SRCS=$(shell find $(SRCDIR) -type f -name '*.c')
TESTSRCS=$(shell find $(TESTDIR) -type f -name '*.c')
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BINS=$(BINDIR)/libturbo.so $(TESTBINDIR)/libturbo
ZIP=$(BINDIR)/turbo.tar.gz $(BINDIR)/turbo.so.tar.gz

all: $(BINS)

release: CFLAGS=-Wall -pedantic -O2 -DNDEBUG -std=c17
release: clean
release: $(BIN)

$(TESTBINDIR)/libturbo: $(TESTSRCS) 
	$(CC) $(CFLAGS) -o $@ $^ -L$(BINDIR) -lturbo

$(BINDIR)/libturbo.so: $(OBJS)
	$(CC) $(CFLAGS) -fPIC -shared $(addprefix $(OBJDIR)/, $(notdir $(OBJS))) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

clean:
	$(RM) $(BINDIR)/*.o $(BINDIR)/*.so $(OBJDIR)/*.o $(TESTBINDIR)/libturbo
