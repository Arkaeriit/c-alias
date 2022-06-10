
all: c_alias

# c_alias_mini.sh is c_alias.sh changed into a one-liner
c_alias_mini.sh: c_alias.sh
	cat $< | grep -v '#' | grep -v '^$$' | sed -z 's:() {\n:() { :g; s:then\n:then :g; s:\n: ; :g' > $@

# To make c_alias, the argument usage at the end of dc_alias_mini.sh is removed
# and that one liner is feed back into itself to generate an executable
# equivalent to the script.
c_alias: c_alias.c c_alias_mini.sh c_alias.sh
	BIG_ALIAS=$$(cat c_alias_mini.sh | sed 's:process $$@.*:process:'); \
	./c_alias.sh $@ "$$BIG_ALIAS"

.PHONY: c_alias_test
c_alias_test: c_alias c_alias_mini.sh
	BIG_ALIAS=$$(cat c_alias_mini.sh | sed 's:process $$@.*:process:'); \
	./c_alias c_alias "\"$$BIG_ALIAS\""

clean:
	rm -rf c_alias
	rm -rf c_alias_mini.sh


