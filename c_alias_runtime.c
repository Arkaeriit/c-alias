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
#include "c_alias_lib.h"

#ifndef CMD_TO_ALIAS
#error "To compile this file, a string should be passed as the defined value `CMD_TO_ALIAS`. The resulting executable will be an alias to `CMD_TO_ALIAS`."
#endif


int main(int argc, const char** argv) {
	char** processed_arr = process_over_arr(argv+1, argc-1, escape_in_str, '\\', "\\");
	processed_arr = process_over_arr_and_free(processed_arr, argc-1, escape_in_str, '"', "\\");
	processed_arr = process_over_arr_and_free(processed_arr, argc-1, surround_string, '"', "\"");
	char* arg_buff = str_arr_into_buff(argc-1, (const char**) processed_arr);
	free_arr(processed_arr, argc-1);
	char* exec_buff = malloc(strlen(CMD_TO_ALIAS) + strlen(arg_buff) + 2);
	strcpy(exec_buff, CMD_TO_ALIAS);
	strcat(exec_buff, " ");
	strcat(exec_buff, arg_buff);
	printf("%s\n", exec_buff);
	int ret = system(exec_buff);
	free(exec_buff);
	free(arg_buff);
	return fold_to_char(ret);
}

