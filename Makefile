INSTALL_PATH_SHARE ?= /usr/local/share/c_alias
INSTALL_PATH_BIN ?= /usr/local/bin
CFLAGS ?= -Wall -Werror -L./
CFLAGS += "-DINSTALL_CFLAGS=\" -L$(INSTALL_PATH_SHARE)/ -I$(INSTALL_PATH_SHARE)/ $(INSTALL_PATH_SHARE)/c_alias_runtime.c -lc_alias\""

ifdef DEBUG
	CFLAGS += -DDEBUG -g
else
	CFLAGS += -O2
endif

all: c_alias

c_alias: c_alias.o libc_alias.a
	$(CC) $< $(CFLAGS) -lc_alias -o $@

libc_alias.a: c_alias_lib.o
	ar rcs $@ $^

%.o: %.c c_alias_lib.h
	$(CC) -c $< $(CFLAGS) -o $@

install: c_alias libc_alias.a
	mkdir -p $(INSTALL_PATH_BIN)
	mkdir -p $(INSTALL_PATH_SHARE)
	cp c_alias $(INSTALL_PATH_BIN)
	cp c_alias_lib.h libc_alias.a c_alias_runtime.c $(INSTALL_PATH_SHARE)

uninstall:
	rm -f $(INSTALL_PATH_SHARE)/libc_alias.a
	rm -f $(INSTALL_PATH_SHARE)/c_alias_lib.h
	rm -f $(INSTALL_PATH_SHARE)/c_alias_runtime.c
	rmdir --ignore-fail-on-non-empty $(INSTALL_PATH_SHARE)
	rm -f $(INSTALL_PATH_BIN)/c_alias
	rmdir --ignore-fail-on-non-empty $(INSTALL_PATH_BIN)

clean:
	rm -rf c_alias
	rm -rf *.o
	rm -rf *.a

