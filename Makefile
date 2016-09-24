CC:=gcc
LD:=ld
AR:=ar

CFLAGS:=

BASEDIR:=.
OUT:=$(BASEDIR)/bin
PREFIX:=/usr/local
DESTDIR:=$(PREFIX)

OBJECTS:=\
	$(OUT)/ccmd_init.o \
	$(OUT)/ccmd_result.o \
	$(OUT)/ccmd_exec.o

INCLUDES:=\
	$(BASEDIR)/include/ccmd.h \
	$(BASEDIR)/include/ccmd_t.h

$(OUT)/%.o: $(BASEDIR)/src/%.c $(INCLUDES)
	mkdir -p $(OUT)
	$(CC) -g -c -o $@ -fPIC -I$(BASEDIR)/src -I$(BASEDIR)/include $(CFLAGS) $<

$(OUT)/libccmd.so: $(OBJECTS)
	$(LD) -shared -o $@ $^ -lc

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

install:
	echo TODO
