#include "scml.h"


////////////////////////////////////////////////////////////////////////////////
// 							SCML format
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// File
////////////////////////////////////////////////////////////////////////////////

struct file file_create(int id, struct string name, int width, int height, float pivot_x, float pivot_y) {
	struct file file;
	file.id = id;
	file.name = name;
	file.width = width;
	file.height = height;
	file.pivot_x = pivot_x;
	file.pivot_y = pivot_y;
	return file;
}

void file_destroy(struct file *file) {
	assert(file != NULL);
	
	string_destroy(&file->name);
}

////////////////////////////////////////////////////////////////////////////////
// File list
////////////////////////////////////////////////////////////////////////////////
struct file_list file_list_create() {
	struct file_list file_list;
	file_list.length = 0;
	file_list.items = NULL;
	return file_list;
}

void file_list_destroy(struct file_list *file_list) {
	assert(file_list != NULL);
	
	for (int i = 0; i < file_list->length; i++) {
		struct file file = file_list->items[i];
		file_destroy(&file);
	}
	
	free(file_list->items);
}

void file_list_append(struct file_list *file_list, struct file file) {
	assert(file_list != NULL);
	
	file_list->length++;
	file_list->items = realloc(file_list->items, sizeof(struct file) * file_list->length);
	file_list->items[file_list->length - 1] = file;
}

struct file* file_list_top(struct file_list *file_list) {
	assert(file_list != NULL);
	assert(file_list->length > 0);
	
	return &(file_list->items[file_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Folder
////////////////////////////////////////////////////////////////////////////////
struct folder folder_create(int id) {
	struct folder folder;
	folder.id = id;
	folder.file_list = file_list_create();
	return folder;
}

void folder_destroy(struct folder *folder) {
	assert(folder != NULL);
	
	file_list_destroy(&folder->file_list);
}

////////////////////////////////////////////////////////////////////////////////
// Folder list
////////////////////////////////////////////////////////////////////////////////

struct folder_list folder_list_create() {
	struct folder_list folder_list;
	folder_list.length = 0;
	folder_list.items = NULL;
	return folder_list;
}

void folder_list_destroy(struct folder_list *folder_list) {
	assert(folder_list != NULL);
	
	for (int i = 0; i < folder_list->length; i++) {
		struct folder folder = folder_list->items[i];
		folder_destroy(&folder);
	}
	
	free(folder_list->items);
}

void folder_list_append(struct folder_list *folder_list, struct folder folder) {
	assert(folder_list != NULL);
	
	folder_list->length++;
	folder_list->items = realloc(folder_list->items, sizeof(struct file) * folder_list->length);
	folder_list->items[folder_list->length - 1] = folder;
}

struct folder* folder_list_top(struct folder_list *folder_list) {
	assert(folder_list != NULL);
	assert(folder_list->length > 0);
	
	return &(folder_list->items[folder_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Object ref
////////////////////////////////////////////////////////////////////////////////
struct object_ref object_ref_create(int id, int timeline, int key, int z_index) {
	struct object_ref object_ref;
	object_ref.id = id;
	object_ref.timeline = timeline;
	object_ref.key = key;
	object_ref.z_index = z_index;
	return object_ref;
}

void object_ref_destroy(struct object_ref *object_ref) {
	assert(object_ref != NULL);
}

////////////////////////////////////////////////////////////////////////////////
// Object ref list
////////////////////////////////////////////////////////////////////////////////
struct object_ref_list object_ref_list_create() {
	struct object_ref_list object_ref_list;
	object_ref_list.length = 0;
	object_ref_list.items = NULL;
	return object_ref_list;
}

void object_ref_list_destroy(struct object_ref_list *object_ref_list) {
	assert(object_ref_list != NULL);
	
	free(object_ref_list->items);
}

void object_ref_list_append(struct object_ref_list *object_ref_list, struct object_ref object_ref) {
	assert(object_ref_list != NULL);
	
	object_ref_list->length++;
	object_ref_list->items = realloc(object_ref_list->items, sizeof(struct object_ref) * object_ref_list->length);
	object_ref_list->items[object_ref_list->length - 1] = object_ref;
}

struct object_ref* object_ref_list_top(struct object_ref_list *object_ref_list) {
	assert(object_ref_list != NULL);
	assert(object_ref_list->length > 0);
	
	return &(object_ref_list->items[object_ref_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Bone ref
////////////////////////////////////////////////////////////////////////////////
struct bone_ref bone_ref_create(int id, int parent, int timeline, int key) {
	struct bone_ref bone_ref;
	bone_ref.id = id;
	bone_ref.parent = parent;
	bone_ref.timeline = timeline;
	bone_ref.key = key;
	return bone_ref;
}

void bone_ref_destroy(struct bone_ref *bone_ref) {
	assert(bone_ref != NULL);
}

////////////////////////////////////////////////////////////////////////////////
// Bone ref list
////////////////////////////////////////////////////////////////////////////////
struct bone_ref_list bone_ref_list_create() {
	struct bone_ref_list bone_ref_list;
	bone_ref_list.length = 0;
	bone_ref_list.items = NULL;
	return bone_ref_list;
}

void bone_ref_list_destroy(struct bone_ref_list *bone_ref_list) {
	assert(bone_ref_list != NULL);
	
	free(bone_ref_list->items);
}

void bone_ref_list_append(struct bone_ref_list *bone_ref_list, struct bone_ref bone_ref) {
	assert(bone_ref_list != NULL);
	
	bone_ref_list->length++;
	bone_ref_list->items = realloc(bone_ref_list->items, sizeof(struct bone_ref) * bone_ref_list->length);
	bone_ref_list->items[bone_ref_list->length - 1] = bone_ref;
}

struct bone_ref* bone_ref_list_top(struct bone_ref_list *bone_ref_list) {
	assert(bone_ref_list != NULL);
	assert(bone_ref_list->length > 0);
	
	return &(bone_ref_list->items[bone_ref_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Mainline key
////////////////////////////////////////////////////////////////////////////////
struct mainline_key mainline_key_create(int id) {
	struct mainline_key mainline_key;
	mainline_key.id = id;
	mainline_key.object_ref_list = object_ref_list_create();
	mainline_key.bone_ref_list = bone_ref_list_create();
	return mainline_key;
}

void mainline_key_destroy(struct mainline_key *mainline_key) {
	assert(mainline_key != NULL);
	
	object_ref_list_destroy(&mainline_key->object_ref_list);
	bone_ref_list_destroy(&mainline_key->bone_ref_list);
}

////////////////////////////////////////////////////////////////////////////////
// Mainline key list
////////////////////////////////////////////////////////////////////////////////
struct mainline_key_list mainline_key_list_create() {
	struct mainline_key_list mainline_key_list;
	mainline_key_list.length = 0;
	mainline_key_list.items = NULL;
	return mainline_key_list;
}

void mainline_key_list_destroy(struct mainline_key_list *mainline_key_list) {
	assert(mainline_key_list != NULL);
	
	for (int i = 0; i < mainline_key_list->length; i++) {
		struct mainline_key mainline_key = mainline_key_list->items[i];
		mainline_key_destroy(&mainline_key);
	}
	
	free(mainline_key_list->items);
}

void mainline_key_list_append(struct mainline_key_list *mainline_key_list, struct mainline_key mainline_key) {
	assert(mainline_key_list != NULL);
	
	mainline_key_list->length++;
	mainline_key_list->items = realloc(mainline_key_list->items, sizeof(struct mainline_key) * mainline_key_list->length);
	mainline_key_list->items[mainline_key_list->length - 1] = mainline_key;
}

struct mainline_key* mainline_key_list_top(struct mainline_key_list *mainline_key_list) {
	assert(mainline_key_list != NULL);
	assert(mainline_key_list->length > 0);
	
	return &(mainline_key_list->items[mainline_key_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Mainline
////////////////////////////////////////////////////////////////////////////////
struct mainline mainline_create() {
	struct mainline mainline;
	mainline.mainline_key_list = mainline_key_list_create();
	return mainline;
}

void mainline_destroy(struct mainline *mainline) {
	assert(mainline != NULL);
	mainline_key_list_destroy(&mainline->mainline_key_list);
}

////////////////////////////////////////////////////////////////////////////////
// Object
////////////////////////////////////////////////////////////////////////////////
struct object object_create(int folder, int file, float angle, float scale_x, float scale_y) {
	struct object object;
	object.folder = folder;
	object.file = file;
	object.angle = angle;
	object.scale_x = scale_x;
	object.scale_y = scale_y;
	return object;
}

void object_destroy(struct object *object) {
	assert(object != NULL);
}

////////////////////////////////////////////////////////////////////////////////
// Object list
////////////////////////////////////////////////////////////////////////////////
struct object_list object_list_create() {
	struct object_list object_list;
	object_list.length = 0;
	object_list.items = NULL;
	return object_list;
}

void object_list_destroy(struct object_list *object_list) {
	assert(object_list != NULL);
	
	for (int i = 0; i < object_list->length; i++) {
		struct object object = object_list->items[i];
		object_destroy(&object);
	}
	
	free(object_list->items);
}

void object_list_append(struct object_list *object_list, struct object object) {
	assert(object_list != NULL);
	
	object_list->length++;
	object_list->items = realloc(object_list->items, sizeof(struct object) * object_list->length);
	object_list->items[object_list->length - 1] = object;
}

struct object* object_list_top(struct object_list *object_list) {
	assert(object_list != NULL);
	assert(object_list->length > 0);
	
	return &(object_list->items[object_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Bone
////////////////////////////////////////////////////////////////////////////////
struct bone bone_create(float x, float y, float angle, float scale_x, float scale_y, float a) {
	struct bone bone;
	bone.x = x;
	bone.y = y;
	bone.angle = angle;
	bone.scale_x = scale_x;
	bone.scale_y = scale_y;
	return bone;
}

void bone_destroy(struct bone *bone) {
	assert(bone != NULL);
}

////////////////////////////////////////////////////////////////////////////////
// Bone list
////////////////////////////////////////////////////////////////////////////////
struct bone_list bone_list_create() {
	struct bone_list bone_list;
	bone_list.length = 0;
	bone_list.items = NULL;
	return bone_list;
}

void bone_list_destroy(struct bone_list *bone_list) {
	assert(bone_list != NULL);
	
	for (int i = 0; i < bone_list->length; i++) {
		struct bone bone = bone_list->items[i];
		bone_destroy(&bone);
	}
	
	free(bone_list->items);
}

void bone_list_append(struct bone_list *bone_list, struct bone bone) {
	assert(bone_list != NULL);
	
	bone_list->length++;
	bone_list->items = realloc(bone_list->items, sizeof(struct bone) * bone_list->length);
	bone_list->items[bone_list->length - 1] = bone;
}

struct bone* bone_list_top(struct bone_list *bone_list) {
	assert(bone_list != NULL);
	assert(bone_list->length > 0);
	
	return &(bone_list->items[bone_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Timeline key
////////////////////////////////////////////////////////////////////////////////
struct timeline_key timeline_key_create(int id, int time, int spin) {
	struct timeline_key timeline_key;
	timeline_key.id = id;
	timeline_key.time = time;
	timeline_key.spin = spin;
	timeline_key.object_list = object_list_create();
	timeline_key.bone_list = bone_list_create();
	return timeline_key;
}

void timeline_key_destroy(struct timeline_key *timeline_key) {
	assert(timeline_key != NULL);
	
	object_list_destroy(&timeline_key->object_list);
	bone_list_destroy(&timeline_key->bone_list);
}

////////////////////////////////////////////////////////////////////////////////
// Timeline key list
////////////////////////////////////////////////////////////////////////////////
struct timeline_key_list timeline_key_list_create() {
	struct timeline_key_list timeline_key_list;
	timeline_key_list.length = 0;
	timeline_key_list.items = NULL;
	return timeline_key_list;
}

void timeline_key_list_destroy(struct timeline_key_list *timeline_key_list) {
	assert(timeline_key_list != NULL);
	
	for (int i = 0; i < timeline_key_list->length; i++) {
		struct timeline_key timeline_key = timeline_key_list->items[i];
		timeline_key_destroy(&timeline_key);
	}
	
	free(timeline_key_list->items);
}

void timeline_key_list_append(struct timeline_key_list *timeline_key_list, struct timeline_key timeline_key) {
	assert(timeline_key_list != NULL);
	
	timeline_key_list->length++;
	timeline_key_list->items = realloc(timeline_key_list->items, sizeof(struct timeline_key) * timeline_key_list->length);
	timeline_key_list->items[timeline_key_list->length - 1] = timeline_key;
}

struct timeline_key* timeline_key_list_top(struct timeline_key_list *timeline_key_list) {
	assert(timeline_key_list != NULL);
	assert(timeline_key_list->length > 0);
	
	return &(timeline_key_list->items[timeline_key_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Timeline
////////////////////////////////////////////////////////////////////////////////
struct timeline timeline_create(int id, struct string name) {
	struct timeline timeline;
	timeline.id = id;
	timeline.name = name;
	timeline.timeline_key_list = timeline_key_list_create();
	return timeline;
}

void timeline_destroy(struct timeline *timeline) {
	assert(timeline != NULL);
	
	string_destroy(&timeline->name);
}

////////////////////////////////////////////////////////////////////////////////
// Animation
////////////////////////////////////////////////////////////////////////////////
struct animation animation_create(int id, struct string name, int length, int interval) {
	struct animation animation;
	animation.id = id;
	animation.name = name;
	animation.length = length;
	animation.interval = interval;
	return animation;
}

void animation_destroy(struct animation *animation) {
	assert(animation != NULL);
	
	string_destroy(&animation->name);
	mainline_destroy(&animation->mainline);
	timeline_destroy(&animation->timeline);
}

////////////////////////////////////////////////////////////////////////////////
// Animation list
////////////////////////////////////////////////////////////////////////////////
struct animation_list animation_list_create() {
	struct animation_list animation_list;
	animation_list.length = 0;
	animation_list.items = NULL;
	return animation_list;
}

void animation_list_destroy(struct animation_list *animation_list) {
	assert(animation_list != NULL);
	
	for (int i = 0; i < animation_list->length; i++) {
		struct animation animation = animation_list->items[i];
		animation_destroy(&animation);
	}
	
	free(animation_list->items);
}

void animation_list_append(struct animation_list *animation_list, struct animation animation) {
	assert(animation_list != NULL);
	
	animation_list->length++;
	animation_list->items = realloc(animation_list->items, sizeof(struct animation) * animation_list->length);
	animation_list->items[animation_list->length - 1] = animation;
}

struct animation* animation_list_top(struct animation_list *animation_list) {
	assert(animation_list != NULL);
	assert(animation_list->length > 0);
	
	return &(animation_list->items[animation_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Entity
////////////////////////////////////////////////////////////////////////////////
struct entity entity_create(int id, struct string name) {
	struct entity entity;
	entity.id = id;
	entity.name = name;
	entity.animation_list = animation_list_create();
	return entity;
}

void entity_destroy(struct entity *entity) {
	assert(entity != NULL);
	
	string_destroy(&entity->name);
	animation_list_destroy(&entity->animation_list);
}

////////////////////////////////////////////////////////////////////////////////
// Entity list
////////////////////////////////////////////////////////////////////////////////
struct entity_list entity_list_create() {
	struct entity_list entity_list;
	entity_list.length = 0;
	entity_list.items = NULL;
	return entity_list;
}

void entity_list_destroy(struct entity_list *entity_list) {
	assert(entity_list != NULL);
	
	for (int i = 0; i < entity_list->length; i++) {
		struct entity entity = entity_list->items[i];
		entity_destroy(&entity);
	}
	
	free(entity_list->items);
}

void entity_list_append(struct entity_list *entity_list, struct entity entity) {
	assert(entity_list != NULL);
	
	entity_list->length++;
	entity_list->items = realloc(entity_list->items, sizeof(struct entity) * entity_list->length);
	entity_list->items[entity_list->length - 1] = entity;
}

struct entity* entity_list_top(struct entity_list *entity_list) {
	assert(entity_list != NULL);
	assert(entity_list->length > 0);
	
	return &(entity_list->items[entity_list->length - 1]);
}

////////////////////////////////////////////////////////////////////////////////
// Spriter Data
////////////////////////////////////////////////////////////////////////////////
struct spriter_data spriter_data_create() {
	struct spriter_data spriter_data;
	spriter_data.folder_list = folder_list_create();
	spriter_data.entity_list = entity_list_create();
	return spriter_data;
}

void spriter_data_destroy(struct spriter_data *spriter_data) {
	string_destroy(&spriter_data->version);
	string_destroy(&spriter_data->generator);
	string_destroy(&spriter_data->generator_version);
	folder_list_destroy(&spriter_data->folder_list);
	entity_list_destroy(&spriter_data->entity_list);
}


struct spriter_data parse_tags(struct tag_list tags) {
	struct spriter_data spriter_data = spriter_data_create();
	
	bool enclosed_in_timeline = false; // used to determine what type of key
	bool enclosed_in_mainline = false;
	
	for (int i = 0; i < tags.length; i++) {
		struct tag tag = tags.items[i];
		
		if (string_compare(&tag.identifier.text, "file")) {
			printf("Parsing file\r\n");
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			struct attribute attr_name = attribute_list_find_by_name(&tag.attributes, "name");
			struct attribute attr_width = attribute_list_find_by_name(&tag.attributes, "width");
			struct attribute attr_height = attribute_list_find_by_name(&tag.attributes, "height");
			struct attribute attr_pivot_x = attribute_list_find_by_name(&tag.attributes, "pivot_x");
			struct attribute attr_pivot_y = attribute_list_find_by_name(&tag.attributes, "pivot_y");
			
			
			int id = string_to_int(&attr_id.value.text);
			struct string name = attr_name.value.text;
			int width = string_to_int(&attr_width.value.text);
			int height = string_to_int(&attr_height.value.text);
			float pivot_x = string_to_float(&attr_pivot_x.value.text);
			float pivot_y = string_to_float(&attr_pivot_y.value.text);
			
			struct file file = file_create(id, name, width, height, pivot_x, pivot_y);
			
			struct folder* folder = folder_list_top(&spriter_data.folder_list);
			file_list_append(&folder->file_list, file);
			
		} else if (string_compare(&tag.identifier.text, "folder")) {
			printf("Parsing folder\r\n");
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			
			int id = string_to_int(&attr_id.value.text);
			
			struct folder folder = folder_create(id);
			
			folder_list_append(&spriter_data.folder_list, folder);
			
		} else if (string_compare(&tag.identifier.text, "object_ref")) {
			printf("Parsing object ref\r\n");
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			struct attribute attr_timeline = attribute_list_find_by_name(&tag.attributes, "timeline");
			struct attribute attr_key = attribute_list_find_by_name(&tag.attributes, "key");
			struct attribute attr_z_index = attribute_list_find_by_name(&tag.attributes, "z_index");
			
			int id = string_to_int(&attr_id.value.text);
			int timeline = string_to_int(&attr_timeline.value.text);
			int key = string_to_int(&attr_key.value.text);
			int z_index = string_to_int(&attr_z_index.value.text);
			
			struct object_ref object_ref = object_ref_create(id, timeline, key, z_index);
			
			struct entity* entity = entity_list_top(&spriter_data.entity_list);
			struct animation* animation = animation_list_top(&entity->animation_list);
			struct mainline* mainline = &animation->mainline;
			struct mainline_key_list* mainline_key_list = &(mainline->mainline_key_list);
			struct mainline_key* mainline_key = mainline_key_list_top(mainline_key_list);
			struct object_ref_list object_ref_list = mainline_key->object_ref_list;
			object_ref_list_append(&object_ref_list, object_ref);
			
		} else if (string_compare(&tag.identifier.text, "bone")) {
			printf("Parsing bone\r\n");
			
			float x = 0.0f;
			float y = 0.0f;
			float angle = 0.0f;
			float scale_x = 1.0f;
			float scale_y = 1.0f;
			float a = 1.0f;
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			struct attribute attr_parent = attribute_list_find_by_name(&tag.attributes, "parent");
			struct attribute attr_timeline = attribute_list_find_by_name(&tag.attributes, "timeline");
			struct attribute attr_key = attribute_list_find_by_name(&tag.attributes, "key");
			
			struct bone bone = bone_create(x, y, angle, scale_x, scale_y, a);
			
			struct entity* entity = entity_list_top(&spriter_data.entity_list);
			struct animation* animation = animation_list_top(&entity->animation_list);
			struct timeline* timeline = &animation->timeline;
			struct timeline_key_list* timeline_key_list = &(timeline->timeline_key_list);
			struct timeline_key* timeline_key = timeline_key_list_top(timeline_key_list);
			bone_list_append(&timeline_key->bone_list, bone);
			
		} else if (string_compare(&tag.identifier.text, "bone_ref")) {
			printf("Parsing bone_ref\r\n");
			
			int id = 0;
			int parent = -1;
			int timeline = 0;
			int key = 0;
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			if (attribute_list_contains_name(&tag.attributes, "parent")) {
				struct attribute attr_parent = attribute_list_find_by_name(&tag.attributes, "parent");
				parent = string_to_int(&attr_parent.value.text);
			}
			struct attribute attr_timeline = attribute_list_find_by_name(&tag.attributes, "timeline");
			struct attribute attr_key = attribute_list_find_by_name(&tag.attributes, "key");
			
			timeline = string_to_int(&attr_timeline.value.text);
			key = string_to_int(&attr_key.value.text);
			
			struct bone_ref bone_ref = bone_ref_create(id, parent, timeline, key);
			
			struct entity* entity = entity_list_top(&spriter_data.entity_list);
			struct animation* animation = animation_list_top(&entity->animation_list);
			struct mainline* mainline = &animation->mainline;
			struct mainline_key_list* mainline_key_list = &(mainline->mainline_key_list);
			struct mainline_key* mainline_key = mainline_key_list_top(mainline_key_list);
			bone_ref_list_append(&mainline_key->bone_ref_list, bone_ref);
			
		} else if (string_compare(&tag.identifier.text, "mainline")) {
			printf("Parsing mainline\r\n");
			
			struct mainline mainline = mainline_create();
			
			struct entity* entity = entity_list_top(&spriter_data.entity_list);
			struct animation* animation = animation_list_top(&entity->animation_list);
			animation->mainline = mainline;
			
			enclosed_in_timeline = false;
			enclosed_in_mainline = true;
			
		} else if (string_compare(&tag.identifier.text, "object")) {
			printf("Parsing object\r\n");
			
			int folder = 0;
			int file = 0;
			float angle = 0.0f;
			float scale_x = 1.0f;
			float scale_y = 1.0f;
			
			struct attribute attr_folder = attribute_list_find_by_name(&tag.attributes, "folder");
			struct attribute attr_file = attribute_list_find_by_name(&tag.attributes, "file");
			if (attribute_list_contains_name(&tag.attributes, "scale_y")) {
				struct attribute attr_angle = attribute_list_find_by_name(&tag.attributes, "angle");
				angle = string_to_float(&attr_angle.value.text);
			}
			if (attribute_list_contains_name(&tag.attributes, "scale_x")) {
				struct attribute attr_scale_x = attribute_list_find_by_name(&tag.attributes, "scale_x");
				scale_x = string_to_float(&attr_scale_x.value.text);
			}
			if (attribute_list_contains_name(&tag.attributes, "scale_y")) {
				struct attribute attr_scale_y = attribute_list_find_by_name(&tag.attributes, "scale_y");
				scale_y = string_to_float(&attr_scale_y.value.text);
			}
			
			folder = string_to_int(&attr_folder.value.text);
			file = string_to_int(&attr_file.value.text);
			
			struct object object = object_create(folder, file, angle, scale_x, scale_y);
			
			struct entity* entity = entity_list_top(&spriter_data.entity_list);
			struct animation* animation = animation_list_top(&entity->animation_list);
			struct timeline timeline = animation->timeline;
			struct timeline_key* timeline_key = timeline_key_list_top(&timeline.timeline_key_list);
			object_list_append(&timeline_key->object_list, object);
			
		} else if (string_compare(&tag.identifier.text, "key")) {
			printf("Parsing key!\r\n");
			
			if (enclosed_in_mainline) {
				printf("Parsing mainline key\r\n");
				
				int id = 0;
				
				struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
				
				id = string_to_int(&attr_id.value.text);
				
				struct mainline_key mainline_key = mainline_key_create(id);
				
				struct entity* entity = entity_list_top(&spriter_data.entity_list);
				struct animation* animation = animation_list_top(&entity->animation_list);
				struct mainline* mainline = &animation->mainline;
				mainline_key_list_append(&mainline->mainline_key_list, mainline_key);
				
			} else if (enclosed_in_timeline) {
				printf("Parsing timeline key\r\n");
				
				int id = 0;
				int time = 0;
				int spin = 0;
				
				struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
				if (attribute_list_contains_name(&tag.attributes, "time")) {
					struct attribute attr_time = attribute_list_find_by_name(&tag.attributes, "time");
					time = string_to_int(&attr_time.value.text);
				}
				struct attribute attr_spin = attribute_list_find_by_name(&tag.attributes, "spin");
				
				id = string_to_int(&attr_id.value.text);
				spin = string_to_int(&attr_spin.value.text);
				
				struct timeline_key timeline_key = timeline_key_create(id, time, spin);
				
				struct entity *entity = entity_list_top(&spriter_data.entity_list);
				struct animation *animation = animation_list_top(&entity->animation_list);
				struct timeline* timeline = &animation->timeline;
				timeline_key_list_append(&timeline->timeline_key_list, timeline_key);
				
			}
		} else if (string_compare(&tag.identifier.text, "timeline")) {
			printf("Parsing timeline\r\n");
			
			int id = 0;
			struct string name = string_create("");
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			struct attribute attr_name = attribute_list_find_by_name(&tag.attributes, "name");
			
			struct timeline timeline = timeline_create(id, name);
			
			struct entity* entity = entity_list_top(&spriter_data.entity_list);
			struct animation* animation = animation_list_top(&entity->animation_list);
			animation->timeline = timeline;
			
			enclosed_in_timeline = true;
			enclosed_in_mainline = false;
			
		} else if (string_compare(&tag.identifier.text, "animation")) {
			printf("Parsing animation\r\n");
			
			int id = 0;
			struct string name = string_create("");
			int length = 0;
			int interval = 0;
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			struct attribute attr_name = attribute_list_find_by_name(&tag.attributes, "name");
			struct attribute attr_length = attribute_list_find_by_name(&tag.attributes, "length");
			struct attribute attr_interval = attribute_list_find_by_name(&tag.attributes, "interval");
			
			id = string_to_int(&attr_id.value.text);
			name = attr_name.value.text;
			length = string_to_int(&attr_length.value.text);
			interval = string_to_int(&attr_interval.value.text);
			
			struct animation animation = animation_create(id, name, length, interval);
			
			struct entity* entity = entity_list_top(&spriter_data.entity_list);
			animation_list_append(&entity->animation_list, animation);
			
		} else if (string_compare(&tag.identifier.text, "entity")) {
			printf("Parsing entity\r\n");
			
			int id = 0;
			struct string name = string_create("");
			
			struct attribute attr_id = attribute_list_find_by_name(&tag.attributes, "id");
			struct attribute attr_name = attribute_list_find_by_name(&tag.attributes, "name");
			
			id = string_to_int(&attr_id.value.text);
			name = attr_name.value.text;
			
			struct entity entity = entity_create(id, name);
			entity_list_append(&spriter_data.entity_list, entity);
			
		} else if (string_compare(&tag.identifier.text, "spriter_data")) {
			printf("Parsing spriter data\r\n");
			
			struct attribute attr_version = attribute_list_find_by_name(&tag.attributes, "scml_version");
			struct attribute attr_generator = attribute_list_find_by_name(&tag.attributes, "generator");
			struct attribute attr_generator_version = attribute_list_find_by_name(&tag.attributes, "generator_version");
			
			spriter_data.version = attr_version.value.text;
			spriter_data.generator = attr_generator.value.text;
			spriter_data.generator_version = attr_generator.value.text;
		}
	}
	
	return spriter_data;
}