#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// String
////////////////////////////////////////////////////////////////////////////////
struct string {
	char *characters;
};

struct string string_create(const char *content);
void string_destroy(struct string *str);
int string_length(struct string *str);
char string_at(struct string *str, int index);
void string_append_char(struct string *str, char c);
void string_append_char_array(struct string *str, const char *chars);
void string_print(struct string *str);
void string_print_raw(struct string *str);
bool string_compare(struct string *str, const char *char_array);
void string_copy(struct string *dest_str, struct string *src_str);
int string_to_int(struct string *str);
float string_to_float(struct string *str);
void string_reset(struct string *str);