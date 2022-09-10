INSTALL_PATH_SHARE ?= /usr/local/share/c-alias
INSTALL_PATH_BIN ?= /usr/local/bin
CFLAGS ?= -Wall -Werror -L./
CFLAGS += "-DINSTALL_CFLAGS=\" -L$(INSTALL_PATH_SHARE)/ -I$(INSTALL_PATH_SHARE)/ $(INSTALL_PATH_SHARE)/c-alias-runtime.c -lc-alias\""

ifdef DEBUG
	CFLAGS += -DDEBUG -g
else
	CFLAGS += -O2
endif

all: c-alias

c-alias: c-alias.o libc-alias.a
	$(CC) $< $(CFLAGS) -lc-alias -o $@

libc-alias.a: c-alias-lib.o
	ar rcs $@ $^

%.o: %.c c-alias-lib.h
	$(CC) -c $< $(CFLAGS) -o $@

install: c-alias libc-alias.a
	mkdir -p $(INSTALL_PATH_BIN)
	mkdir -p $(INSTALL_PATH_SHARE)
	cp c-alias $(INSTALL_PATH_BIN)
	cp c-alias-lib.h libc-alias.a c-alias-runtime.c $(INSTALL_PATH_SHARE)

uninstall:
	rm -f $(INSTALL_PATH_SHARE)/libc-alias.a
	rm -f $(INSTALL_PATH_SHARE)/c-alias-lib.h
	rm -f $(INSTALL_PATH_SHARE)/c-alias-runtime.c
	rmdir --ignore-fail-on-non-empty $(INSTALL_PATH_SHARE)
	rm -f $(INSTALL_PATH_BIN)/c-alias
	rmdir --ignore-fail-on-non-empty $(INSTALL_PATH_BIN)

clean:
	rm -rf c-alias
	rm -rf *.o
	rm -rf *.a

