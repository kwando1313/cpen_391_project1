#ifndef HASHMAP_H_
#define HASHMAP_H_

#define HASHMAP_ERROR (void*)-1

typedef struct __hash_entry{
	void* data;
	unsigned int key;
	struct __hash_entry* next;
} hash_entry;

typedef struct __hashmap{
	hash_entry** buckets;
	int size, count;
} hashmap;

// Creates a new hashmap near the given size
hashmap* hashmapCreate(int start_size);

// Inserts a new element into the hashmap
void hashmapInsert(hashmap* map, const void* data, unsigned int key);

// Removes the (key,value) pair, returns the value
// returns HASHMAP_ERROR for fail
void* hashmapRemove(hashmap* map, unsigned int key);

// Returns the value for the key
// returns HASHMAP_ERROR if it wasnt there
void* hashmapGet(hashmap* map, unsigned int key);

// Returns the number of saved elements
int hashmapCount(hashmap* map);

// Frees the hashmap structure
void hashmapDelete(hashmap* map);

#endif
