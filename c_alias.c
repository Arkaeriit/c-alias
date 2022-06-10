/*----------------------------------------------\
|This file is a template to create C-aliases.   |
|Those are executables that behaves as if they  |
|were alias to a command. This command should be|
|given at compile time as the defined constant  |
|CMD_TO_ALIAS. This defined constant should be a|
|string literal.                                |
\----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CMD_TO_ALIAS
#error "To compile this file, a string should be passed as the defined value `CMD_TO_ALIAS`. The resulting executable will be an alias to `CMD_TO_ALIAS`."
#endif

/*
 * Computes the sum of the length of the strings in an array.
 */
size_t str_arr_tot_len(int n_elems, const char** arr) {
	size_t ret = 0;
	for (int i=0; i<n_elems; i++) {
		ret += strlen(arr[i]);
	}
	return ret;
}

/*
 * Concatenates all the strings in an arrays into a single one, separated by
 * spaces.
 */
char* str_arr_into_buff(int n, const char** arr) {
	char* ret = malloc(n + str_arr_tot_len(n, arr) + 1);	
	ret[0] = 0;
	for (int i=0; i<n; i++) {
		strcat(ret, arr[i]);
		strcat(ret, " ");
	}
	ret[strlen(ret)-1] = 0; // Cut off last space
	return ret;
}

/*
 * Split an int into byte-size chunks and OR all of the chunks.
 */
char fold_to_char(int in) {
	char ret = 0;
	for (int i=0; i<sizeof(int); i++) {
		char mask = (in >> (i * 8)) & 0xFF;
		ret |= mask;
	}
	return ret;
}

int main(int argc, const char** argv) {
	char* arg_buff = str_arr_into_buff(argc - 1, argv + 1);
	char* exec_buff = malloc(strlen(CMD_TO_ALIAS) + strlen(arg_buff) + 2);
	strcpy(exec_buff, CMD_TO_ALIAS);
	strcat(exec_buff, " ");
	strcat(exec_buff, arg_buff);
	printf("%s\n", exec_buff);
	int ret = system(exec_buff);
	printf("%i\n", ret);
	free(exec_buff);
	free(arg_buff);
	return fold_to_char(ret);
}

