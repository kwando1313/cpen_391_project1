#ifndef B_TREE_H_
#define B_TREE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct __bnode{
	int data;
	struct __bnode* left;
	struct __bnode* right;
} bnode;

bnode* create_new_bnode(int data);
bnode* insert_bnode(bnode* root, int data);
bool search_tree(bnode* root, int data);
void free_tree(bnode* root);

#endif
