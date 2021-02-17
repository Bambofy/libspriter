# libspriter
 A C SCML parser

# Example

```
#include "libspriter.c"

int main() {
	struct tag_list tag_list = parse_file("test.scml");
	
	struct spriter_data spriter_data = parse_tags(tag_list);
	
	// navigate the spriter_data structures
	
	return 0;
}
```
