#include "xml.h"

////////////////////////////////////////////////////////////////////////////////
// 								XML
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Value
////////////////////////////////////////////////////////////////////////////////
struct value value_create(struct string text) {
	struct value value;
	value.text = text;
	return value;
}

void value_destroy(struct value *value) {
	assert(value != NULL);
	
	string_destroy(&value->text);
}

////////////////////////////////////////////////////////////////////////////////
// Name
////////////////////////////////////////////////////////////////////////////////
struct name name_create(struct string text) {
	struct name name;
	name.text = text;
	return name;
}

void name_destroy(struct name *name) {
	assert(name != NULL);
	
	string_destroy(&name->text);
}

////////////////////////////////////////////////////////////////////////////////
// Attribute
////////////////////////////////////////////////////////////////////////////////
struct attribute attribute_create(struct value value, struct name name) {
	struct attribute attribute;
	attribute.value = value;
	attribute.name = name;
	return attribute;
}

void attribute_destroy(struct attribute *attr) {
	assert(attr != NULL);
	
	value_destroy(&attr->value);
	name_destroy(&attr->name);
}

void attribute_reset(struct attribute *attr) {
	assert(attr != NULL);
	
	memset(attr, 0, sizeof(struct attribute));
}

////////////////////////////////////////////////////////////////////////////////
// Attribute list
////////////////////////////////////////////////////////////////////////////////
struct attribute_list attribute_list_create() {
	struct attribute_list attribute_list;
	attribute_list.length = 0;
	attribute_list.items = NULL;
	return attribute_list;
}

void attribute_list_destroy(struct attribute_list *attr_list) {
	assert(attr_list != NULL);
	
	for (int i = 0; i < attr_list->length; i++) {
		struct attribute attr = attr_list->items[i];
		attribute_destroy(&attr);
	}
	
	free(attr_list->items);
}

void attribute_list_append(struct attribute_list *attr_list, struct attribute attr) {
	assert(attr_list != NULL);
	
	attr_list->length++;
	attr_list->items = realloc(attr_list->items, sizeof(struct attribute) * attr_list->length);
	attr_list->items[attr_list->length - 1] = attr;
}

struct attribute attribute_list_find_by_name(struct attribute_list *attr_list, const char *name) {
	assert(attr_list != NULL);
	assert(name != NULL);
	
	struct attribute attr;
	bool attribute_found = false;
	
	for (int i = 0; i < attr_list->length; i++) {
		struct attribute curr_attr = attr_list->items[i];
		if (string_compare(&curr_attr.name.text, name)) {
			attr = curr_attr;
			attribute_found = true;
			break;
		}
	}
	
	assert(attribute_found);
	
	return attr;
}

bool attribute_list_contains_name(struct attribute_list *attr_list, const char *name) {
	assert(attr_list != NULL);
	assert(name != NULL);
	
	bool attribute_found = false;
	
	for (int i = 0; i < attr_list->length; i++) {
		struct attribute curr_attr = attr_list->items[i];
		if (string_compare(&curr_attr.name.text, name)) {
			attribute_found = true;
			break;
		}
	}
	
	return attribute_found;
}

int attribute_list_length(struct attribute_list *attribute_list) {
	assert(attribute_list != NULL);
	
	return attribute_list->length;
}

struct attribute attribute_list_at(struct attribute_list *attribute_list, int index) {
	assert(attribute_list != NULL);
	assert(index >= 0);
	assert(index < attribute_list_length(attribute_list));
	
	return attribute_list->items[index];
}

////////////////////////////////////////////////////////////////////////////////
// Identifier
////////////////////////////////////////////////////////////////////////////////
struct identifier identifier_create(struct string text) {
	struct identifier identifier;
	identifier.text = text;
	return identifier;
}

void identifier_destroy(struct identifier *identifier) {
	assert(identifier != NULL);
	
	string_destroy(&identifier->text);
}

////////////////////////////////////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////////////////////////////////////
struct tag tag_create(struct identifier identifier, struct attribute_list attributes) {
	struct tag tag;
	tag.identifier = identifier;
	tag.attributes = attributes;
	return tag;
}

void tag_destroy(struct tag *tag) {
	assert(tag != NULL);
	
	identifier_destroy(&tag->identifier);
	attribute_list_destroy(&tag->attributes);
}

////////////////////////////////////////////////////////////////////////////////
// Tag list
////////////////////////////////////////////////////////////////////////////////s
struct tag_list tag_list_create() {
	struct tag_list tag_list;
	tag_list.length = 0;
	tag_list.items = NULL;
	return tag_list;
}

void tag_list_destroy(struct tag_list *tag_list) {
	assert(tag_list != NULL);
	
	for (int i = 0; i < tag_list->length; i++) {
		struct tag tag = tag_list->items[i];
		tag_destroy(&tag);
	}
	free(tag_list->items);
}

void tag_list_append(struct tag_list *tag_list, struct tag tag) {
	assert(tag_list != NULL);
	
	tag_list->length++;
	tag_list->items = realloc(tag_list->items, sizeof(struct tag) * tag_list->length);
	tag_list->items[tag_list->length - 1] = tag;
}

struct tag* tag_list_top(struct tag_list *tag_list) {
	assert(tag_list != NULL);
	assert(tag_list->length > 0);
	
	return &(tag_list->items[tag_list->length - 1]);
}

int tag_list_length(struct tag_list *tag_list) {
	assert(tag_list != NULL);
	
	return tag_list->length;
}

struct tag tag_list_at(struct tag_list *tag_list, int index) {
	assert(tag_list != NULL);
	assert(index >= 0);
	assert(index < tag_list_length(tag_list));
	
	return tag_list->items[index];
}

////////////////////////////////////////////////////////////////////////////////
// Procedures
////////////////////////////////////////////////////////////////////////////////
struct attribute_list parse_attributes(struct string line) {
	struct attribute_list attribute_list = attribute_list_create();
	
	struct string name_str = string_create("");
	struct string value_str = string_create("");
	
	bool past_whitespace = false;
	
	bool identifier_skipped = false;
	bool reading_name = true;
	bool reading_value = false;
	
	bool in_quotes = false;
	
	for (int i = 0; i < string_length(&line); i++) {
		char c = string_at(&line, i);
		
		if (!past_whitespace) {
			if (c == ' ') {
				continue;
			} else {
				past_whitespace = true;
			}
		}
		
		if (!identifier_skipped) {
			if (c == ' ') { identifier_skipped = true; }
			continue;
		}
		
		if (reading_name) {
			if (c == ' ') continue;
			
			if (c == '=') {
				reading_name = false;
				reading_value = true;
			} else {
				string_append_char(&name_str, c);
			}
		} else if (reading_value) {
			if (c == '"') {
				in_quotes = !in_quotes;
				
				if (!in_quotes) {
					struct name name = name_create(name_str);
					struct value value = value_create(value_str);
					
					struct attribute attribute = attribute_create(value, name);
					attribute_list_append(&attribute_list, attribute);
					
					name_str = string_create("");
					value_str = string_create("");
					
					reading_name = true;
					reading_value = false;
					in_quotes = false;
				}
			} else if (in_quotes) {
				string_append_char(&value_str, c);
			}
		} else {
			continue;
		}
	}
	
	string_destroy(&name_str);
	string_destroy(&value_str);
	
	return attribute_list;
}

struct identifier parse_identifier(struct string line) {
	struct string identifier_str = string_create("");
	bool whitespace_ended = false;
	
	for (int i = 0; i < string_length(&line); i++) {
		char c = string_at(&line, i);
		
		if (!whitespace_ended) {
			if (c == ' ') {
				continue;
			} else {
				whitespace_ended = true;
			}
		}
		
		if (c == '<') continue;
		if (c == '/') continue;
		if (c == '>') continue;
		if (c == '?') continue;
		if (c == ' ') break;
		
		string_append_char(&identifier_str, c);
	}
	
	struct identifier identifier = identifier_create(identifier_str);
	return identifier;
}

struct tag parse_tag(struct string line) {
	struct identifier identifier = parse_identifier(line);
	struct attribute_list attribute_list = parse_attributes(line);
	
	struct tag tag = tag_create(identifier, attribute_list);
	return tag;
}

enum tag_types identify_tag(struct string line) {
	enum tag_types tag_type = tag_type_opening;
	
	bool found_less_than = false;
	int found_less_than_at = 0;
	
	for (int i = 0; i < string_length(&line); i++) { // searching for '</'
		char c = string_at(&line, i);
		
		if (c == '<') {
			found_less_than = true;
			found_less_than_at = i;
		}
		if (c == '/') {
			if (found_less_than_at == (i-1)) { // is less than index 1 before?
				tag_type = tag_type_closing;
				break;
			}
		}
	}
	
	return tag_type;
}

struct tag_list parse_file(char *filepath) {
	FILE *f;
	f = fopen(filepath, "r");
	
	struct tag_list tag_list = tag_list_create();
	
	struct string line = string_create("");
	
	bool line_ended = false;
	while (!feof(f)) {
		char c = getc(f);
		
		if (!line_ended) {
			if ((c == '\r') || (c == '\n')) {
				line_ended = true;
			} else {
				string_append_char(&line, c);
			}
		} else {
			if ((c != '\r') && (c != '\n')) {
				line_ended = false;
				
				if (identify_tag(line) == tag_type_opening) {
					struct tag tag = parse_tag(line);
					tag_list_append(&tag_list, tag);
				}
				
				line = string_create("");
				if (c != ' ') {
					string_append_char(&line, c);
				}
			}
		}
	}
	
	string_destroy(&line);
	
	fclose(f);
	
	return tag_list;
}
