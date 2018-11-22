LIBDIR = /usr/lib
CFLAGS = -Wall
LDFLAGS = -rdynamic -shared -lm
CONFIG = ./config/notebook.conf
LIBSO = libnotebook.so
OBJS = notebook-lib.o rgb-color-conv.o

LIBLOC := $(patsubst x86_64,i386,$(shell uname -m))
	ifeq (,$(filter x86_64,$(LIBLOC)))
		override LIBDIR = /usr/lib64
	endif


all: $(LIBSO) install clean

$(LIBSO): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.c.o:
	$(CC) -fPIC $(CFLAGS) -c -o $@ $<

install: $(LIBSO)
	install -m 755 $(LIBSO) $(LIBDIR)
	install -m 644 $(CONFIG) $(HOME)

clean:
	rm -rf $(OBJS)
