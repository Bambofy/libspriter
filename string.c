#include "string.h"

////////////////////////////////////////////////////////////////////////////////
// String
////////////////////////////////////////////////////////////////////////////////
struct string string_create(const char *content) {
	struct string str;
	str.characters = calloc(strlen(content) + 1, sizeof(char));
	strcpy(str.characters, content);
	return str;
}

void string_destroy(struct string *str) {
	assert(str != NULL);
	assert(str->characters != NULL);
	
	free(str->characters);
}

int string_length(struct string *str) {
	assert(str != NULL);
	
	return strlen(str->characters);
}

char string_at(struct string *str, int index) {
	assert(str != NULL);
	assert(str->characters != NULL);
	assert(index <= strlen(str->characters));
	
	return str->characters[index];
}

void string_append_char(struct string *str, char c) {
	assert(str != NULL);
	assert(str->characters != NULL);
	
	int old_length = strlen(str->characters);
	int new_length = old_length + 1;
	
	str->characters = realloc(str->characters, new_length + 1);
	str->characters[new_length] = '\0';
	str->characters[new_length - 1] = c;
}

void string_append_char_array(struct string *str, const char *chars) {
	assert(str != NULL);
	assert(str->characters != NULL);
	assert(chars != NULL);
	
	int old_length = strlen(str->characters);
	int new_length = old_length + strlen(chars);
	
	str->characters = realloc(str->characters, new_length + 1);
	str->characters[new_length] = '\0';
	strcat(str->characters, chars);
}

void string_print(struct string *str) {
	assert(str != NULL);
	assert(str->characters != NULL);
	
	printf("\"%s\"\r\n", str->characters);
}

void string_print_raw(struct string *str) {
	assert(str != NULL);
	assert(str->characters != NULL);
	
	for (int i = 0; i < (strlen(str->characters) + 1); i++) {
		printf("'%c',", str->characters[i]);
	}
}

bool string_compare(struct string *str, const char *char_array) {
	assert(str != NULL);
	assert(str->characters != NULL);
	assert(char_array != NULL);
	
	return strcmp(str->characters, char_array) == 0;
}

void string_copy(struct string *dest_str, struct string *src_str) {
	assert(dest_str != NULL);
	assert(src_str != NULL);
	assert(dest_str->characters != NULL);
	assert(src_str->characters != NULL);
	
	free(dest_str->characters);
	dest_str->characters = calloc(string_length(src_str) + 1, sizeof(char));
	strcpy(dest_str->characters, src_str->characters);
	dest_str->characters[string_length(src_str)] = '\0';
}

int string_to_int(struct string *str) {
	assert(str != NULL);
	assert(str->characters != NULL);
	
	return atoi(str->characters);
}

float string_to_float(struct string *str) {
	assert(str != NULL);
	assert(str->characters != NULL);
	
	return atof(str->characters);
}

void string_reset(struct string *str) {
	assert(str != NULL);
	assert(str->characters != NULL);
	
	memset(str, 0, sizeof(struct string));
	str->characters = NULL;
}
