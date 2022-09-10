
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c-alias-lib.h"

/*
 * Try to find libc_alias.a, c_alias_runtime.c, and c_alias_lib.h in the
 * working directory. If they are found, returs c_flags to use them. If not,
 * returns INSTALL_CFLAGS. For the sake of portability, uses stdio functions
 * to do so.
 */
#define CHECK_FILE(filename)   \
    f = fopen(filename, "r");  \
    if (f == NULL) {           \
        return INSTALL_CFLAGS; \
    }                          \
    fclose(f)                   
const char* get_instalation_flags(void) {
	FILE* f;
	CHECK_FILE("c-alias-runtime.c");
	CHECK_FILE("libc-alias.a");
	CHECK_FILE("c-alias-lib.h");
	return " c-alias-runtime.c -lc-alias -L./ ";
}

int main(int argc, const char** argv) {
	if (argc < 3) {
		printf("Usage:\n");
		printf("  %s <alias name> <alias content...>\n", argv[0]);
		return 1;
	}

	char** processed_arr = process_over_arr(argv+2, argc-2, escape_in_str, '\\', "\\");
	processed_arr = process_over_arr_and_free(processed_arr, argc-2, escape_in_str, '"', "\\");
	processed_arr = process_over_arr_and_free(processed_arr, argc-2, replace_char, '\'', "'\"'\"'");
	char* arg_buff = str_arr_into_buff(argc-2, (const char**) processed_arr);
	free_arr(processed_arr, argc-2);
	char* exec_buff = malloc(100000);
	strcpy(exec_buff, CC);
	sprintf(exec_buff+strlen(CC), " -o %s '-DCMD_TO_ALIAS=\"%s\"'", argv[1], arg_buff);
	strcat(exec_buff, get_instalation_flags());
#ifdef DEBUG
	strcat(exec_buff, " -DDEBUG ");
	printf("%s", exec_buff);
#endif
	int ret = system(exec_buff);
	free(exec_buff);
	free(arg_buff);
	return fold_to_char(ret);
}

