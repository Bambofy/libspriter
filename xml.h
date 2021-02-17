#pragma once

#include "string.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// 								XML
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Value
////////////////////////////////////////////////////////////////////////////////
struct value {
	struct string text;
};

struct value value_create(struct string text);
void value_destroy(struct value *value);

////////////////////////////////////////////////////////////////////////////////
// Name
////////////////////////////////////////////////////////////////////////////////
struct name {
	struct string text;
};

struct name name_create(struct string text);
void name_destroy(struct name *name);

////////////////////////////////////////////////////////////////////////////////
// Attribute
////////////////////////////////////////////////////////////////////////////////
struct attribute {
	struct value value;
	struct name name;
};

struct attribute attribute_create(struct value value, struct name name);
void attribute_destroy(struct attribute *attr);
void attribute_reset(struct attribute *attr);

////////////////////////////////////////////////////////////////////////////////
// Attribute list
////////////////////////////////////////////////////////////////////////////////
struct attribute_list {
	int length;
	struct attribute *items;
};

struct attribute_list attribute_list_create();
void attribute_list_destroy(struct attribute_list *attr_list);
void attribute_list_append(struct attribute_list *attr_list, struct attribute attr);
struct attribute attribute_list_find_by_name(struct attribute_list *attr_list, const char *name);
bool attribute_list_contains_name(struct attribute_list *attr_list, const char *name);
int attribute_list_length(struct attribute_list *attribute_list);
struct attribute attribute_list_at(struct attribute_list *attribute_list, int index);

////////////////////////////////////////////////////////////////////////////////
// Identifier
////////////////////////////////////////////////////////////////////////////////
struct identifier {
	struct string text;
};

struct identifier identifier_create(struct string text);
void identifier_destroy(struct identifier *identifier);

////////////////////////////////////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////////////////////////////////////
struct tag {
	struct identifier identifier;
	struct attribute_list attributes;
};

struct tag tag_create(struct identifier identifier, struct attribute_list attributes);
void tag_destroy(struct tag *tag);

////////////////////////////////////////////////////////////////////////////////
// Tag list
////////////////////////////////////////////////////////////////////////////////
struct tag_list {
	int length;
	struct tag *items;
};

struct tag_list tag_list_create();
void tag_list_destroy(struct tag_list *tag_list);
void tag_list_append(struct tag_list *tag_list, struct tag tag);
struct tag* tag_list_top(struct tag_list *tag_list);
int tag_list_length(struct tag_list *tag_list);
struct tag tag_list_at(struct tag_list *tag_list, int index);

////////////////////////////////////////////////////////////////////////////////
// Procedures
////////////////////////////////////////////////////////////////////////////////
struct attribute_list parse_attributes(struct string line);
struct identifier parse_identifier(struct string line);
struct tag parse_tag(struct string line);
enum tag_types {
	tag_type_opening,
	tag_type_closing
};
enum tag_types identify_tag(struct string line);
struct tag_list parse_file(char *filepath);