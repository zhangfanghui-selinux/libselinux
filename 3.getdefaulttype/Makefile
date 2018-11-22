TARGETS = $(patsubst %.c,%,$(wildcard *.c))
LDLIBS += -lselinux -lnotebook -lpthread -laudit -lkeyutils -lsepol
BINDIR ?= /usr/local/bin
CFLAGS ?= -Wall

# Make INFO = 1 to display initial text or 0 to stop.
INFO = 1
ifeq ($(INFO),1)
	override CFLAGS += -DINFO
endif

# Note if using 32 bit systems then libselinux requires Large File Support 
# (LFS) in Linux, therefore need -D_FILE_OFFSET_BITS=64 otherwise
# matchpathcon_filespec_add passes over wrong size ino_t.
LFS := $(patsubst x86_64,i386,$(shell uname -m))
	ifeq (,$(filter i386,$(LFS)))
		override CFLAGS += -D_FILE_OFFSET_BITS=64
	endif


all: $(TARGETS)
    echo: "$(TARGETS)"
	
install:
	install -m 755 $(TARGETS) $(BINDIR)
	rm -f $(TARGETS)
