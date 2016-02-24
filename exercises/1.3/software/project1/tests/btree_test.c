#include "b_tree.h"

int btree_test(void){
	bnode* root;

	printf("Starting btree tests...\n");
	root = insert_bnode(NULL, 5, "test");

	if (!node_exists(root, 5)){
		printf("Test failed. Node does not exist.");
		return -1;
	}
	char* word = get_data(root, 5);

	if (strcmp(word, "test") != 0){
		printf("Test failed. Incorrect value stored.");
		return -1;
	}

	root = insert_bnode(root, 3, "test2");
	root = insert_bnode(root, 9, 3);
	root = insert_bnode(root, 6, 4);
	root = insert_bnode(root, 293939, 'c');
	root = insert_bnode(root, -2, 49);

	bnode* bnode;
	bnode = get_min_bnode(root);
	if (bnode->key != -2){
		printf("Test failed. Failed to get the smallest bnode's key.");
		return -1;
	}
	bnode = get_max_bnode(root);
	if (bnode->key != 293939){
		printf("Test failed. Failed to get the largest bnode's key.");
		return -1;
	}
	root = delete_bnode_with_key(root, -2);
	root = delete_bnode_with_key(root, 3);

	bnode = get_min_bnode(root);

	if (bnode->key != 5){
		printf("Test failed. Tree failed to self balance.");
		return -1;
	}

	root = delete_bnode_with_key(root, 6);

	if (node_exists(root, 6)){
		printf("Test failed. Deleting node did not work.");
		return -1;
	}
	if (!node_exists(root, 9)){
		printf("Test failed. Deleting node removed the rest of the subtree.");
		return -1;
	}

	if (get_data(root, 123131) != NULL){
		printf("Test failed. We're getting phantom data that doesn't exist.");
		return -1;
	}

	if (delete_bnode_with_key(root, 1213213) != root){
		printf("Test failed. We're deleting a node that doesn't exist.");
		return -1;
	}

	free_tree(root, true);

	if(node_exists(root, 6)){
		printf("Test failed. Data did not get freed in the end.");
		return -1;

	}
	astar_node * a =init_astar_node(1, 0, 0);
	astar_node * b = init_astar_node(2, 0, 0);

	root = insert_bnode(root, 13, a);
	root = insert_bnode(root, 13, b);

	root = delete_bnode_with_v_id(root, 13, 1);

	if (!node_exists(root, 13)){
		printf("Test failed. We deleted all the nodes.");
		return -1;
	}
	astar_node* c = get_data(root, 13);
	if (c->v_id != 2){
		printf("Test failed. We deleted the wrong node.");
		return -1;
	}

	root = delete_bnode_with_v_id(root, 13, 3);

	if (!node_exists(root, 13)){
		printf("Test failed. We deleted a node we should not have deleted.");
		return -1;
	}

	root = delete_bnode_with_v_id(root, 13, 2);
	if (node_exists(root, 13)){
		printf("Test failed. We failed to delete the node.");
		return -1;
	}



	printf("All tests passed!");
	return 0;
}

