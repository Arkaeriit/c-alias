#include "c_alias_lib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
char* escape_in_str(const char* str, char c, const char* escape_code) {
	char* rep = malloc(2 + strlen(escape_code));
	strcpy(rep, escape_code);
	char buff[2] = {c, 0};
	strcat(rep, buff);
	char* ret = replace_char(str, c, rep);
	free(rep);
	return ret;
}

/*
 * Replace a char from a string with a new string
 */
char* replace_char(const char* str, char c, const char* rep) {
	size_t c_count = 0;
	for (int i=0; i<strlen(str); i++) {
		if (str[i] == c) {
			c_count++;
		}
	}
	size_t ret_len = strlen(str) + (c_count * (strlen(rep) - 1));
	char* ret = malloc(ret_len + 1);
	ret[0] = 0;
	for (int i=0; i<strlen(str); i++) {
		if (str[i] == c) {
			strcat(ret, rep);
		} else {
			char buff[2] = {str[i], 0};
			strcat(ret, buff);
		}
	}
	return ret;
}

/*
 * Puts a char at the beginning and the end of a string.
 * The returned value is malloc'ed.
 */
char* surround_string(const char* str, char first_edge, const char* last_edge) {
	char* ret = malloc(strlen(str) + 3);
	ret[0] = first_edge;
	ret[1] = 0;
	strcat(ret, str);
	char buff[2] = {*last_edge, 0};
	strcat(ret, buff);
	return ret;
}

/*
 * Runs a function of the prototype char* xxx(const char*, char, char*) over all
 * the element of an array of string.
 */
char** process_over_arr(const char** arr, size_t size_arr, char* (func)(const char*, char, const char*), char arg1, const char* arg2) {
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
char** process_over_arr_and_free(char** arr, size_t size_arr, char* (func)(const char*, char, const char*), char arg1, const char* arg2) {
	char** ret = process_over_arr((const char**) arr, size_arr, func, arg1, arg2);
	free_arr(arr, size_arr);
	return ret;
}

/*
 * Display an array of strings.
 */
void __attribute__((unused)) disp_arr(const char** arr, size_t size_arr) {
	puts("[");
	for (size_t i=0; i<size_arr; i++) {
		printf("%s,\n", arr[i]);
	}
	puts("]");
}

