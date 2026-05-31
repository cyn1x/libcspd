# Set compiler information and compiler flags
CC     := clang
CFLAGS  = -std=c17 -g -Wextra -Werror -pedantic -pedantic-errors $(INCLUDE)

# Set `*.h` header files and include directories
HEADERS := $(shell find ./include ./tests/include -type f -name '*.h' | sort -r)
INCLUDE := $(sort $(addprefix -I,$(dir $(HEADERS))))

# Set `compile_flags.txt` for the Clang LSP
CFLAGSTXT := $(subst -I,-I ,$(INCLUDE))

# Determine build output directories and build configuration properties
SYSTEM := $(shell uname -s | tr A-Z a-z)
ARCH   := $(shell uname -m | sed 's/x86_64/x64/; s/i.86/x86/')
CONFIG := Debug

# Define intermediary and binary output directories
SRCDIR := src
LIBDIR := lib/$(SYSTEM)/$(CONFIG)_$(ARCH)
OBJDIR := obj/$(SYSTEM)/$(CONFIG)_$(ARCH)
BINDIR := bin/$(SYSTEM)/$(CONFIG)_$(ARCH)

# Define commands to retrieve `*.c` source and `*.o` intermediate files
TEST := $(shell find $(TESTDIR) -type f -name '*.c')
SRCS := $(shell find $(SRCDIR) -type f -name '*.c')
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Set `*.so` (Shared Object) target for `all` 
BINS := $(LIBDIR)/libcspd.so $(BINDIR)/libcspd
# TODO: Set `*.tar.gz` (Compressed Archive) target for `all` 
# ZIPS := $(LIBDIR)/libcspd.tar.gz $(BINDIR)/libcspd.so.tar.gz

# Make target for shared library and test suite executable
all: $(BINS)

release: CFLAGS = -Wall -pedantic -O2 -DNDEBUG -std=c17
release: CONFIG := Release
release: $(BINS)
release: clean

# Create required directories for library and test suite compilation
$(OBJDIR) $(BINDIR) $(LIBDIR):
	mkdir -p $@

# Compile core library `*.c` files and output to intermediary directory
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $(OBJDIR)/$(notdir $@)

# Generate shared library for dynamic linking
$(LIBDIR)/libcspd.so: $(OBJS) | $(LIBDIR)
	$(shell cp /dev/null compile_flags.txt)
	$(foreach i,$(CFLAGSTXT),$(file >> compile_flags.txt,$(i)))
	$(CC) $(CFLAGS) -fPIC -shared $(addprefix $(OBJDIR)/, $(notdir $(OBJS))) -o $@

# Compile and link test suite
$(BINDIR)/libcspd: $(TEST) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBDIR) -lcspd

clean:
	$(RM) $(BINDIR)/*.o $(LIBDIR)/*.so $(OBJDIR)/*.o $(BINDIR)/libcspd
