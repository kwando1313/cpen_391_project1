#ifndef HASHMAP_H_
#define HASHMAP_H_

typedef struct __hEntry{
  void* data;
  int flags;
  long key;
} hEntry;

typedef struct __hashmap{
  hEntry* table;
  long size, count;
} hashmap;

/** Creates a new hashmap near the given size. */
hashmap* hashmapCreate(int startsize);

/** Inserts a new element into the hashmap. */
void hashmapInsert(hashmap*, const void* data, unsigned long key);

/** Removes the storage for the element of the key and returns the element. */
void* hashmapRemove(hashmap*, unsigned long key);

/** Returns the element for the key. */
void* hashmapGet(hashmap*, unsigned long key);

/** Returns the number of saved elements. */
long hashmapCount(hashmap*);

/** Removes the hashmap structure. */
void hashmapDelete(hashmap*);

#endif
