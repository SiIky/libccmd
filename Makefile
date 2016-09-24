CC?=gcc
LD?=ld
AR?=ar

CFLAGS?=
LDFLAGS?=

BASEDIR?=.
OUT:=$(BASEDIR)/bin
PREFIX?=/usr/local
DESTDIR?=$(PREFIX)

OBJECTS:=\
	$(OUT)/ccmd_init.o \
	$(OUT)/ccmd_result.o \
	$(OUT)/ccmd_exec.o \
	$(OUT)/ccmd_split.o \
	$(OUT)/ccmd_join.o

INCLUDES:=\
	$(BASEDIR)/include/ccmd.h \
	$(BASEDIR)/src/ccmd_t.h

$(OUT)/%.o: $(BASEDIR)/src/%.c $(INCLUDES)
	mkdir -p $(OUT)
	$(CC) -g -c -o $@ -fPIC -I$(BASEDIR)/src -I$(BASEDIR)/include $(CFLAGS) $<

$(OUT)/libccmd.so: $(OBJECTS)
	$(LD) -shared -o $@ $^ -lc $(LDFLAGS)

$(OUT)/libccmd.a: $(OBJECTS)
	$(AR) cr $@ $^

$(OUT)/ccmd_test: $(BASEDIR)/test/main.c $(OUT)/libccmd.a
	$(CC) -g -o $@ \
		$(BASEDIR)/test/main.c -I$(BASEDIR)/include \
		-L$(OUT) -l:libccmd.a $(CFLAGS)

.PHONY: all_static all_shared all clean distclean check install
.DEFAULT_GOAL=all

all_static: $(OUT)/libccmd.a

all_shared: $(OUT)/libccmd.so

all: all_static all_shared

clean:
	rm -rf $(OUT)

distclean: clean

check: $(OUT)/ccmd_test
	$(OUT)/ccmd_test suite

install_static:
	install -Dm644 $(OUT)/libccmd.a $(DESTDIR)/lib/libccmd.a

install_shared:
	install -Dm755 $(OUT)/libccmd.so $(DESTDIR)/lib/libccmd.so

install_headers:
	install -Dm644 $(BASEDIR)/include/ccmd.h $(DESTDIR)/include/ccmd.h

install: install_static install_shared install_headers

uninstall:
	rm -f $(DESTDIR)/include/ccmd.h
	rm -f $(DESTDIR)/lib/libccmd.so
	rm -f $(DESTDIR)/lib/libccmd.a
