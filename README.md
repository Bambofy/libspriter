# libspriter
 A C SCML parser

# Example

```
#include "libspriter.c"

int main() {
	printf("Starting...");
	
	struct tag_list tag_list = parse_file("test.scml");
	
	for (int i = 0; i < tag_list_length(&tag_list); i++) {
		struct tag tag = tag_list_at(&tag_list, i);
		printf("Name: %s\r\n", tag.identifier.text.characters);
		
		for (int k = 0; k < attribute_list_length(&tag.attributes); k++) {
			struct attribute attr = attribute_list_at(&tag.attributes, k);
			printf("\t'%s'='%s'\r\n", attr.name.text.characters, attr.value.text.characters);
		}
	}
	
	struct spriter_data spriter_data = parse_tags(tag_list);

 // navigate the spriter_data structures
	
	return 0;
}
```
