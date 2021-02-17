#pragma once

#include "string.h"
#include "xml.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



////////////////////////////////////////////////////////////////////////////////
// 							SCML format
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// File
////////////////////////////////////////////////////////////////////////////////

struct file {
	int id;
	struct string name;
	int width, height;
	float pivot_x, pivot_y;
};

struct file file_create(int id, struct string name, int width, int height, float pivot_x, float pivot_y);
void file_destroy(struct file *file);

////////////////////////////////////////////////////////////////////////////////
// File list
////////////////////////////////////////////////////////////////////////////////
struct file_list {
	int length;
	struct file *items;
};

struct file_list file_list_create();
void file_list_destroy(struct file_list *file_list);
void file_list_append(struct file_list *file_list, struct file file);
struct file* file_list_top(struct file_list *file_list);

////////////////////////////////////////////////////////////////////////////////
// Folder
////////////////////////////////////////////////////////////////////////////////

struct folder {
	int id;
	struct file_list file_list;
};

struct folder folder_create(int id);
void folder_destroy(struct folder *folder);

////////////////////////////////////////////////////////////////////////////////
// Folder list
////////////////////////////////////////////////////////////////////////////////
struct folder_list {
	int length;
	struct folder *items;
};

struct folder_list folder_list_create();
void folder_list_destroy(struct folder_list *folder_list);
void folder_list_append(struct folder_list *folder_list, struct folder folder);
struct folder* folder_list_top(struct folder_list *folder_list);

////////////////////////////////////////////////////////////////////////////////
// Object ref
////////////////////////////////////////////////////////////////////////////////
struct object_ref {
	int id;
	int timeline;
	int key;
	int z_index;
};

struct object_ref object_ref_create(int id, int timeline, int key, int z_index);
void object_ref_destroy(struct object_ref *object_ref);

////////////////////////////////////////////////////////////////////////////////
// Object ref list
////////////////////////////////////////////////////////////////////////////////
struct object_ref_list {
	int length;
	struct object_ref *items;
};

struct object_ref_list object_ref_list_create();
void object_ref_list_destroy(struct object_ref_list *object_ref_list);
void object_ref_list_append(struct object_ref_list *object_ref_list, struct object_ref object_ref);
struct object_ref* object_ref_list_top(struct object_ref_list *object_ref_list);

////////////////////////////////////////////////////////////////////////////////
// Bone ref
////////////////////////////////////////////////////////////////////////////////
struct bone_ref {
	int id;
	int parent;
	int timeline;
	int key;
};

struct bone_ref bone_ref_create(int id, int parent, int timeline, int key);
void bone_ref_destroy(struct bone_ref *bone_ref);

////////////////////////////////////////////////////////////////////////////////
// Bone ref list
////////////////////////////////////////////////////////////////////////////////
struct bone_ref_list {
	int length;
	struct bone_ref *items;
};

struct bone_ref_list bone_ref_list_create();
void bone_ref_list_destroy(struct bone_ref_list *bone_ref_list);
void bone_ref_list_append(struct bone_ref_list *bone_ref_list, struct bone_ref bone_ref);
struct bone_ref* bone_ref_list_top(struct bone_ref_list *bone_ref_list);

////////////////////////////////////////////////////////////////////////////////
// Mainline key
////////////////////////////////////////////////////////////////////////////////
struct mainline_key {
	int id;
	struct object_ref_list object_ref_list;
	struct bone_ref_list bone_ref_list;
};

struct mainline_key mainline_key_create(int id);
void mainline_key_destroy(struct mainline_key *mainline_key);

////////////////////////////////////////////////////////////////////////////////
// Mainline key list
////////////////////////////////////////////////////////////////////////////////
struct mainline_key_list {
	int length;
	struct mainline_key *items;
};

struct mainline_key_list mainline_key_list_create();
void mainline_key_list_destroy(struct mainline_key_list *mainline_key_list);
void mainline_key_list_append(struct mainline_key_list *mainline_key_list, struct mainline_key mainline_key);
struct mainline_key* mainline_key_list_top(struct mainline_key_list *mainline_key_list);

////////////////////////////////////////////////////////////////////////////////
// Mainline
////////////////////////////////////////////////////////////////////////////////
struct mainline {
	struct mainline_key_list mainline_key_list;
};

struct mainline mainline_create();
void mainline_destroy(struct mainline *mainline);

////////////////////////////////////////////////////////////////////////////////
// Object
////////////////////////////////////////////////////////////////////////////////

struct object {
	int folder;
	int file;
	float angle;
	float scale_x;
	float scale_y;
};

struct object object_create(int folder, int file, float angle, float scale_x, float scale_y);
void object_destroy(struct object *object);

////////////////////////////////////////////////////////////////////////////////
// Object list
////////////////////////////////////////////////////////////////////////////////
struct object_list {
	int length;
	struct object *items;
};

struct object_list object_list_create();
void object_list_destroy(struct object_list *object_list);
void object_list_append(struct object_list *object_list, struct object object);
struct object* object_list_top(struct object_list *object_list);

////////////////////////////////////////////////////////////////////////////////
// Bone
////////////////////////////////////////////////////////////////////////////////

struct bone {
	float x;
	float y;
	float angle;
	float scale_x;
	float scale_y;
	float a;
};

struct bone bone_create(float x, float y, float angle, float scale_x, float scale_y, float a);
void bone_destroy(struct bone *bone);

////////////////////////////////////////////////////////////////////////////////
// Bone list
////////////////////////////////////////////////////////////////////////////////
struct bone_list {
	int length;
	struct bone *items;
};

struct bone_list bone_list_create();
void bone_list_destroy(struct bone_list *bone_list);
void bone_list_append(struct bone_list *bone_list, struct bone bone);
struct bone* bone_list_top(struct bone_list *bone_list);

////////////////////////////////////////////////////////////////////////////////
// Timeline key
////////////////////////////////////////////////////////////////////////////////
struct timeline_key {
	int id;
	int time;
	int spin;
	struct object_list object_list;
	struct bone_list bone_list;
};

struct timeline_key timeline_key_create(int id, int time, int spin);
void timeline_key_destroy(struct timeline_key *timeline_key);

////////////////////////////////////////////////////////////////////////////////
// Timeline key list
////////////////////////////////////////////////////////////////////////////////
struct timeline_key_list {
	int length;
	struct timeline_key *items;
};

struct timeline_key_list timeline_key_list_create();
void timeline_key_list_destroy(struct timeline_key_list *timeline_key_list);
void timeline_key_list_append(struct timeline_key_list *timeline_key_list, struct timeline_key timeline_key);
struct timeline_key* timeline_key_list_top(struct timeline_key_list *timeline_key_list);

////////////////////////////////////////////////////////////////////////////////
// Timeline
////////////////////////////////////////////////////////////////////////////////
struct timeline {
	int id;
	struct string name;
	struct timeline_key_list timeline_key_list;
};

struct timeline timeline_create(int id, struct string name);
void timeline_destroy(struct timeline *timeline);

////////////////////////////////////////////////////////////////////////////////
// Animation
////////////////////////////////////////////////////////////////////////////////

struct animation {
	int id;
	struct string name;
	int length;
	int interval;
	
	struct mainline mainline;
	struct timeline timeline;
};

struct animation animation_create(int id, struct string name, int length, int interval);
void animation_destroy(struct animation *animation);

////////////////////////////////////////////////////////////////////////////////
// Animation list
////////////////////////////////////////////////////////////////////////////////
struct animation_list {
	int length;
	struct animation *items;
};

struct animation_list animation_list_create();
void animation_list_destroy(struct animation_list *animation_list);
void animation_list_append(struct animation_list *animation_list, struct animation animation);
struct animation* animation_list_top(struct animation_list *animation_list);

////////////////////////////////////////////////////////////////////////////////
// Entity
////////////////////////////////////////////////////////////////////////////////
struct entity {
	int id;
	struct string name;
	struct animation_list animation_list;
};

struct entity entity_create(int id, struct string name);
void entity_destroy(struct entity *entity);

////////////////////////////////////////////////////////////////////////////////
// Entity list
////////////////////////////////////////////////////////////////////////////////
struct entity_list {
	int length;
	struct entity *items;
};

struct entity_list entity_list_create();
void entity_list_destroy(struct entity_list *entity_list);
void entity_list_append(struct entity_list *entity_list, struct entity entity);
struct entity* entity_list_top(struct entity_list *entity_list);

////////////////////////////////////////////////////////////////////////////////
// Spriter Data
////////////////////////////////////////////////////////////////////////////////

struct spriter_data {
	struct string version;
	struct string generator;
	struct string generator_version;
	
	struct folder_list folder_list;
	struct entity_list entity_list;
};

struct spriter_data spriter_data_create();
void spriter_data_destroy(struct spriter_data *spriter_data);

///////////////////////////////////////////////////////////////////////////////
// Procedures
///////////////////////////////////////////////////////////////////////////////
struct spriter_data parse_tags(struct tag_list tags);