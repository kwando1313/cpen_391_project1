#include "b_tree.h"

bnode* get_max_bnode(bnode* root){
	while(root->right != NULL){
		root = root->right;
	}
	return root;
}

bnode* get_min_bnode(bnode* root){
	while(root->left != NULL){
		root = root->left;
	}
	return root;
}

bnode* insert_bnode(bnode* root, int key, void* data){
	if (root == NULL) {
		return create_new_bnode(key, data);
	}
	if (key >= root->key) {
		root->right = insert_bnode(root->right, key, data);
	} else {
		root->left = insert_bnode(root->left, key, data);
	}

	return root;
}

bnode* create_new_bnode(int key, void* data){
	bnode* node = malloc(sizeof(bnode));
	node->key = key;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

bool node_exists(bnode* root, int key){
	if (root == NULL) {
		return false;
	}

	if (root->key == key) {
		return true;
	} else if (key >= root->key) {
		return node_exists(root->right, key);
	} else {
		return node_exists(root->left, key);
	}
}

void* get_data(bnode* root, int key){
	if (root == NULL) {
		return NULL;
	}

	if (root->key == key) {
		return root->data;
	} else if (key >= root->key) {
		return get_data(root->right, key);
	} else {
		return get_data(root->left, key);
	}
}
bnode* delete_bnode_with_key(bnode* root, int key){
	if (root == NULL) {
		return NULL;
	}

	bnode* new_child = root;

	if (root->key == key) {
		if (root->left == NULL && root->right == NULL) {
			new_child = NULL;
		} else if(root->right == NULL){
			new_child = root->left;
		} else if(root->left == NULL){
			new_child = root->right;
		} else {
			//TODO: this can be optimized. Rather than picking left by default, pick smallest one
			//picking left atm because we'll want to tranverse this path a lot -> might as well make it slightly smaller
			//any simple self-balancing trees online? Do I even need this?
			new_child = root->left;
			bnode* tmp = root->right;
			bnode* curr = get_max_bnode(new_child);
			curr->right = tmp;
		}
		free_bnode(root, false);
	} else if (key >= root->key) {
		root->right = delete_bnode_with_key(root->right, key);
	} else {
		root->left = delete_bnode_with_key(root->left, key);
	}

	return new_child;
}

//same as delete_bnode_with_key, but adds condition of v_id as well
bnode* delete_bnode_with_v_id(bnode* root, int key, int v_id){
	if (root == NULL) {
		return NULL;
	}

	bnode* new_child = root;

	if (root->key == key) {
		astar_node* curr = (astar_node*)root->data;
		if (curr->v_id != v_id) {
			// didnt find the right node
			// go right because thats where we put keys that are equal
			root->right = delete_bnode_with_v_id(root->right, key, v_id);
		} else {
			if (root->left == NULL && root->right == NULL) {
				new_child = NULL;
			} else if(root->right == NULL){
				new_child = root->left;
			} else if(root->left == NULL){
				new_child = root->right;
			} else {
				new_child = root->left;
				bnode* tmp = root->right;
				bnode* curr = get_max_bnode(new_child);
				curr->right = tmp;
			}
			free_bnode(root, false);
		}
	} else if (key >= root->key) {
		root->right = delete_bnode_with_v_id(root->right, key, v_id);
	} else {
		root->left = delete_bnode_with_v_id(root->left, key, v_id);
	}

	return new_child;
}

void free_tree(bnode* root, bool free_data){
	if (root == NULL) {
		return;
	}
	if (root->left) {
		free_tree(root->left, free_data);
	}
	if (root->right) {
		free_tree(root->right, free_data);
	}
	free_bnode(root, free_data);
}

void free_bnode(bnode* root, bool free_data){
	if (root == NULL) {
		return;
	}
	if (free_data && root->data){
		free(root->data);
	}
	free(root);
}
