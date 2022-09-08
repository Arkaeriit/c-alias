CFLAGS ?= -g -Wall -Werror

all: c_alias

c_alias: c_alias.c
	gcc $^ $(CFLAGS) -o $@

clean:
	rm -rf c_alias

