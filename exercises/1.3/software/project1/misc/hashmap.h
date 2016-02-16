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

/** Creates a new hashmap near the given size. */
hashmap* hashmapCreate(int start_size);

/** Inserts a new element into the hashmap. */
void hashmapInsert(hashmap*, const void* data, unsigned int key);

/** Removes the storage for the element of the key and returns the element. */
//returns -1 for fail
void* hashmapRemove(hashmap*, unsigned int key);

/** Returns the element for the key. */
//returns -1 if it wasnt there
void* hashmapGet(hashmap*, unsigned int key);

/** Returns the number of saved elements. */
int hashmapCount(hashmap*);

/** Removes the hashmap structure. */
void hashmapDelete(hashmap*);

#endif
