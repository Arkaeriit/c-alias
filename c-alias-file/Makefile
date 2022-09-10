INSTALL_PATH_BIN ?= /usr/local/bin

c-alias-file: c-alias-file.sh
	./$< $< $@

clean:
	rm -f c-alias-file

install: c-alias-file
	mkdir -p $(INSTALL_PATH_BIN)
	cp $< $(INSTALL_PATH_BIN)/

uninstall:
	rm -f $(INSTALL_PATH_BIN)/c-alias-file
	rmdir --ignore-fail-on-non-empty $(INSTALL_PATH_BIN)

# Test that the script embed itself as it should
.PHONY: test
test: c-alias-file.sh
	./$< $< level1
	./level1 $< level2
	./level2 $< level3
	diff level1 level2
	diff level2 level3
	rm level1 level2 level3

