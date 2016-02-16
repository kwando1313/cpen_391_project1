#ifndef B_TREE_H_
#define B_TREE_H_

#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"

typedef struct __bnode{
	int key;
	void* data;
	struct __bnode* left;
	struct __bnode* right;
} bnode;

bnode* create_new_bnode(int key, void* data);
bnode* insert_bnode(bnode* root, int key, void* data);
bnode* delete_bnode_with_key(bnode* root, int key);

bool node_exists(bnode* root, int key);
void* get_data(bnode* root, int key);
bnode* get_min_bnode(bnode* root);
bnode* get_max_bnode(bnode* root);

void free_bnode(bnode* root, bool free_data);
void free_tree(bnode* root, bool free_data);

//astar search specific -> dont use these for anything else
bnode* delete_bnode_with_v_id(bnode* root, int key, int v_id);

#endif
