# Set compiler information and compiler flags
CC     := clang
CFLAGS  = -std=c17 -g -Wextra -Werror -pedantic -pedantic-errors $(INCLUDE)

# Set `*.h` header files and include directories
HEADERS := $(shell find ./include ./lib -type f -name '*.h' | sort -r)
INCLUDE := $(sort $(addprefix -I,$(dir $(HEADERS))))

# Set `compile_flags.txt` for the Clang LSP
CFLAGSTXT := $(subst -I,-I ,$(INCLUDE))

# Determine build output directories and build configuration properties
SYSTEM := $(shell uname -s | tr A-Z a-z)
ARCH   := $(shell uname -m | sed 's/x86_64/x64/; s/i.86/x86/')
CONFIG := Debug

# Define intermediary and binary output directories
SRCDIR := src
LIBDIR := lib
OBJDIR := obj/$(SYSTEM)/$(CONFIG)_$(ARCH)
BINDIR := bin/$(SYSTEM)/$(CONFIG)_$(ARCH)

# Library output directory
LIBOUT := tests/$(BINDIR)

# Define commands to retrieve `*.c` source and `*.o` intermediate files
TEST := $(shell find $(TESTDIR) -type f -name '*.c')
SRCS := $(shell find $(SRCDIR) -type f -name '*.c')
LIBS := $(shell find $(LIBDIR) -type f -name '*.c')
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJS += $(patsubst $(LIBDIR)/%.c, $(OBJDIR)/%.o, $(LIBS))

# Set Shared Object `*.so` output file path
BINS := $(BINDIR)/libcspd.so tests/$(BINDIR)/libcspd
ZIPS := $(BINDIR)/libcspd.tar.gz tests/$(BINDIR)/libcspd.so.tar.gz

# Targets
all: $(BINS)

release: CFLAGS = -Wall -pedantic -O2 -DNDEBUG -std=c17
release: CONFIG := Release
release: $(BINS)
release: clean

# Ensure directories exist
$(OBJDIR) $(BINDIR) $(LIBOUT):
	mkdir -p $@

tests/$(BINDIR)/libcspd: $(TEST) | $(LIBOUT)
	$(CC) $(CFLAGS) -o $@ $^ -L$(BINDIR) -lcspd

$(BINDIR)/libcspd.so: $(OBJS) | $(BINDIR)
	$(shell cp /dev/null compile_flags.txt)
	$(foreach i,$(CFLAGSTXT),$(file >> compile_flags.txt,$(i)))
	$(CC) $(CFLAGS) -fPIC -shared $(addprefix $(OBJDIR)/, $(notdir $(OBJS))) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $(OBJDIR)/$(notdir $@)


$(OBJDIR)/%.o: $(LIBDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $(OBJDIR)/$(notdir $@)

clean:
	$(RM) $(BINDIR)/*.o $(BINDIR)/*.so $(OBJDIR)/*.o tests/bin/libcspd
