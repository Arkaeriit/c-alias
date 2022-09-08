#ifndef C_ALIAS_LIB_H
#define C_ALIAS_LIB_H

#include <stddef.h>

size_t str_arr_tot_len(int n_elems, const char** arr);
char* str_arr_into_buff(int n, const char** arr);
char fold_to_char(int in);
int count_char_in_string(const char* str, char c);
char* escape_in_str(const char* str, char c, char escape_code);
char* surround_string(const char* str, char first_edge, char last_edge);
char** process_over_arr(const char** arr, size_t size_arr, char* (func)(const char*, char, char), char arg1, char arg2);
void free_arr(char** arr, size_t size_arr);
char** process_over_arr_and_free(char** arr, size_t size_arr, char* (func)(const char*, char, char), char arg1, char arg2);
void __attribute__((unused)) disp_arr(const char** arr, size_t size_arr);

#endif

