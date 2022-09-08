
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	for (size_t i=0; i<sizeof(int); i++) {
		char mask = (in >> (i * 8)) & 0xFF;
		ret |= mask;
	}
	return ret;
}

/*
 * Counts the number of time the given char is in the string.
 */
int count_char_in_string(const char* str, char c) {
	int ret = 0;
	for (size_t i=0; i<strlen(str); i++) {
		if (str[i] == c) {
			ret++;
		}
	}
	return ret;
}

/*
 * Escape the given char with the given escape char in the input string.
 * The output string is malloc-ed.
 */
char* escape_in_str(const char* str, char c, char escape_code) {
	char* ret = malloc(strlen(str) + count_char_in_string(str, c) + 1);
	ret[strlen(str) + count_char_in_string(str, c)] = 0;
	char* p = ret;
	for (size_t i=0; i<strlen(str); i++) {
		if (str[i] == c) {
			*p = escape_code;
			p++;
		}
		*p = str[i];
		p++;
	}
	return ret;
}

/*
 * Puts a char at the beginning and the end of a string.
 * The returned value is malloc'ed.
 */
char* surround_string(const char* str, char first_edge, char last_edge) {
	char* ret = malloc(strlen(str) + 3);
	ret[0] = first_edge;
	ret[1] = 0;
	strcat(ret, str);
	char buff[2] = {last_edge, 0};
	strcat(ret, buff);
	return ret;
}

/*
 * Runs a function of the prototype char* xxx(const char*, char, char) over all
 * the element of an array of string.
 */
char** process_over_arr(const char** arr, size_t size_arr, char* (func)(const char*, char, char), char arg1, char arg2) {
	char** ret = malloc(sizeof(char*) * size_arr);
	for (size_t i=0; i<size_arr; i++) {
		ret[i] = func(arr[i], arg1, arg2);
	}
	return ret;
}

/*
 * Frees an array of strings.
 */
void free_arr(char** arr, size_t size_arr) {
	for (size_t i=0; i<size_arr; i++) {
		free(arr[i]);
	}
}

/*
 * Runs process_over_arr and free the input array
 */
char** process_over_arr_and_free(char** arr, size_t size_arr, char* (func)(const char*, char, char), char arg1, char arg2) {
	char** ret = process_over_arr((const char**) arr, size_arr, func, arg1, arg2);
	free_arr(arr, size_arr);
	return ret;
}

/*
 * Display an array of strings.
 */
void disp_arr(const char** arr, size_t size_arr) {
	puts("[");
	for (size_t i=0; i<size_arr; i++) {
		printf("%s,\n", arr[i]);
	}
	puts("]");
}

int main(int argc, const char** argv) {
	char** processed_arr = process_over_arr(argv+2, argc-2, escape_in_str, '\\', '\\');
	processed_arr = process_over_arr_and_free(processed_arr, argc-2, escape_in_str, '"', '\\');
	char* arg_buff = str_arr_into_buff(argc-2, (const char**) processed_arr);
	free_arr(processed_arr, argc-2);
	char* exec_buff = malloc(100000);
	sprintf(exec_buff, "gcc -o %s c_alias_runtime.c '-DCMD_TO_ALIAS=\"%s\"'", argv[1], arg_buff);
	int ret = system(exec_buff);
	free(exec_buff);
	free(arg_buff);
	return fold_to_char(ret);
}

