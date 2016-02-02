#include "b_tree.h"


bnode* insert_bnode(bnode* root, int data){
	if (root == NULL) {
		return create_new_bnode(data);
	}
	if (data >= root->data) {
		root = insert_bnode(root->right, data);
	} else {
		root = insert_bnode(root->left, data);
	}

	return root;
}

bnode* create_new_bnode(int data){
	bnode* node = malloc(sizeof(bnode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

bool search_tree(bnode* root, int data){
	if (root == NULL) {
		return false;
	}

	if (root->data == data) {
		return true;
	} else if (data >= root->data) {
		return search_tree(root->right, data);
	} else {
		return search_tree(root->left, data);
	}
}

void free_tree(bnode* root){
	if (root->left) {
		free_tree(root->left);
	}
	if (root->right) {
		free_tree(root->right);
	}
	free(root);
}
