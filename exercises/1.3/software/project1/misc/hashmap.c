#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//this can be played with, just don't make too high(ie > 5)
#define LOAD_FACTOR 2

static void rehash(hashmap* hm)
{
//  long size = hm->size;
//  hEntry* table = hm->table;
//
//  hm->size = findPrimeGreaterThan(size<<1);
//  hm->table = (hEntry*)calloc(sizeof(hEntry), hm->size);
//  hm->count = 0;
//
//  while(--size >= 0)
//    if (table[size].flags == ACTIVE)
//      hashmapInsert(hm, table[size].data, table[size].key);
//
//  free(table);
}

hashmap* hashmapCreate(int start_size){
	hashmap* map = malloc(sizeof(hashmap));
	map->size = start_size;
	map->count = 0;
	map->buckets = malloc(sizeof(hash_entry*)*start_size);
	for (int i = 0; i<map->size; i++){
		map->buckets[i] = NULL;
	}
	return map;
}

unsigned int hash(unsigned int key){
	//https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
	return (key*2654435761 % 0xffffffff);
}

hash_entry* init_hash_entry(unsigned int key, const void* data){
	hash_entry* entry = malloc(sizeof(hash_entry));
	entry->key = key;
	entry->next = NULL;
	entry->data = data;
	return entry;
}

void hashmapInsert(hashmap* map, const void* data, unsigned int key){
	if ((map->count/map->size) > LOAD_FACTOR){
		rehash(map);
	}

	int index = hash(key) % map->size;
	hash_entry* prev_entry = map->buckets[index];
	hash_entry* curr_entry = prev_entry;
	while(curr_entry != NULL) {
		if (curr_entry->key == key) {
			curr_entry->data = data;
			return;
		}
		prev_entry = curr_entry;
		curr_entry = curr_entry->next;
	}

	hash_entry* new_entry = init_hash_entry(key, data);

	if (prev_entry == NULL) {
		//first entry in bucket
		map->buckets[index] = new_entry;
	} else {
		prev_entry->next = new_entry;
	}

	map->count++;
}

void* hashmapGet(hashmap* map, unsigned int key){
	int index = hash(key) % map->size;
	hash_entry* curr_entry = map->buckets[index];
	while(true){
		if (curr_entry == NULL) {
			return HASHMAP_ERROR;
		}

		if (curr_entry->key == key) {
			return curr_entry->data;
		}

		curr_entry = curr_entry->next;
	}
}

void* hashmapRemove(hashmap* hash, unsigned int key)
{
//
//  if (hash->count)
//  {
//    long index, i, step;
//    index = key % hash->size;
//    step = (key % (hash->size-2)) + 1;
//
//    for (i = 0; i < hash->size; i++)
//    {
//      if (hash->table[index].key == key)
//      {
//        if (hash->table[index].flags & ACTIVE)
//          return hash->table[index].data;
//        break;
//      }
//      else
//        if (!hash->table[index].data)
//          break;
//
//      index = (index + step) % hash->size;
//    }
//  }
//
	return HASHMAP_ERROR;
}

int hashmapCount(hashmap* map){
  return map->count;
}

void hashmapDelete(hashmap* map){
	for (int i = 0; i<map->size; i++) {
		hash_entry* head = map->buckets[i];
		if (head == NULL){
		        return;
		}
		hash_entry* prev = head;
		head = head->next;
		while (head != NULL) {
			free(prev);
		    prev = head;
		    head = head->next;
		}
		free(prev); // frees last entry
	}
	free(map->buckets);
	free(map);
}
