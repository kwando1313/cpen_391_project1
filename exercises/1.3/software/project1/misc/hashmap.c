#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//this can be played with, just don't make too high(ie > 5)
#define LOAD_FACTOR 2

void rehash(hashmap* map);
void free_bucket(hash_entry* head);

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

void* hashmapRemove(hashmap* map, unsigned int key){
	int index = hash(key) % map->size;
	hash_entry* curr_entry = map->buckets[index];
	hash_entry* prev_entry = map->buckets[index];
	while(true){
		if (curr_entry == NULL) {
			return HASHMAP_ERROR;
		}

		if (curr_entry->key == key) {
			void* data = curr_entry->data;

			if (prev_entry == curr_entry) {
				// first entry in bucket
				map->buckets[index] = curr_entry->next;
			} else {
				prev_entry->next = curr_entry->next;
			}

			free(curr_entry);
			map->count--;
			return data;
		}

		prev_entry = curr_entry;
		curr_entry = curr_entry->next;
	}
}

int hashmapCount(hashmap* map){
  return map->count;
}

void hashmapDelete(hashmap* map){
	for (int i = 0; i<map->size; i++) {
		free_bucket(map->buckets[i]);
	}
	free(map->buckets);
	free(map);
}


void rehash(hashmap* map){
	int old_size = map->size;
	hash_entry** old_buckets = map->buckets;
	map->size *= 2;
	map->count = 0;
	map->buckets = malloc(sizeof(hash_entry*)*map->size);
	for (int i = 0; i<map->size; i++){
		map->buckets[i] = NULL;
	}

	for(int i = 0; i<old_size; i++){
		hash_entry* curr = old_buckets[i];
		while(curr != NULL) {
			hashmapInsert(map, curr->data, curr->key);
			curr = curr->next;
		}
		free_bucket(old_buckets[i]);
	}

	free(old_buckets);
}

void free_bucket(hash_entry* head){
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
