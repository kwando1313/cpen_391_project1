#include "graph.h"
#include "b_tree.h"
#include "hashmap.h"
#include "misc_helpers.h"
#include <math.h>

#define DEFAULT_PATH_SIZE 10

astar_node* init_astar_node(int v_id, int g_val, int h_val);
int get_distance_heuristic(graph* graph, int start, int goal);
int get_cost(graph* graph, int curr, int neighbour);
astar_node* pop_smallest(bnode** root);
int* reconstruct_path(hashmap* path_map, int start, int current_id);
int append_to_array(int** arr, int i, int arr_size, int to_add);

/*
 * Notes on datastructures chosen
 *
 * closed_set:
 * - searchable by v_id
 * - insert a v_id
 * - chosen btree(O(logn)), should change to hashset(O(1))
 *
 * path:
 * - hashmap
 *
 * open_set:
 * - find smallest f val, remove smallest f val
 * - add item
 * - searchable
 * - chosen btree(O(logn) for all). Heap would be O(n) to search, O(logn) for find/remove, O(logn) to add.
 */


int* a_star(graph* graph, int start, int goal){
	//TODO: closed_set should be replaced with hashset
	bnode* closed_set = NULL;
	hashmap* path = hashmapCreate(DEFAULT_PATH_SIZE);

	astar_node* curr_node = init_astar_node(start, 0, get_distance_heuristic(graph, start, goal));
	//maps fval to astar_node
	bnode* open_set = create_new_bnode(curr_node->f_val, curr_node);
	//should be hashmap-> for now, using btrees
	bnode* vid_to_astar_node = NULL;
	vid_to_astar_node = insert_bnode(vid_to_astar_node, curr_node->v_id, curr_node);


	while(open_set != NULL) {
		curr_node = pop_smallest(&open_set); //pop off the (estimated) best node
		vid_to_astar_node = delete_bnode_with_key(vid_to_astar_node, curr_node->v_id);

		astar_node* next_node;

		if (curr_node->v_id == goal) {
			free_tree(closed_set, true);
			free_tree(open_set, true);
			free_tree(vid_to_astar_node, true);
			free(curr_node);
			return reconstruct_path(path, start, goal);
		}

		closed_set = insert_bnode(closed_set, curr_node->v_id, NULL);
		vertex* curr_vertex = get_vertex(graph, curr_node->v_id);

		int num_neighbours = curr_vertex->adjList->num_neighbours;

		for (int i = 0; i < num_neighbours; i++){
			int neighbour_id = curr_vertex->adjList->neighbours[i];

			if (node_exists(closed_set, neighbour_id)) {
				//already explored node
				continue;
			}

			int tentative_g = curr_node->g_val + get_cost(graph, curr_node->v_id, neighbour_id);

			//node hasnt been explored. Either in our list to explore, or completely brand new
			if (!node_exists(vid_to_astar_node, neighbour_id)) {
				next_node = init_astar_node(neighbour_id, tentative_g, get_distance_heuristic(graph, neighbour_id, goal));
				open_set = insert_bnode(open_set, neighbour_id, next_node);
				vid_to_astar_node = insert_bnode(vid_to_astar_node, neighbour_id, next_node);
			} else {
				//get g score of neighbour
				next_node = (astar_node*) get_data(open_set, neighbour_id);
				if (tentative_g >= next_node->g_val) {
					// this path is not better
					continue;
				} else {
					//found a better path to that node
					next_node = init_astar_node(neighbour_id, tentative_g, get_distance_heuristic(graph, neighbour_id, goal));
					open_set = insert_bnode(open_set, neighbour_id, next_node);
					vid_to_astar_node = delete_bnode_with_key(vid_to_astar_node, neighbour_id);
					vid_to_astar_node = insert_bnode(vid_to_astar_node, neighbour_id, next_node);
				}
			}

			hashmapInsert(path, curr_vertex, next_node->v_id);
		}
	}
	printf("couldn't find a path");
	return NULL;
}

int* reconstruct_path(hashmap* path_map, int start, int current_id){
	printf("found the goal\n");
	int path_size = DEFAULT_PATH_SIZE;
	int array_index = 0;
	int* total_path = malloc(path_size*sizeof(int));
	total_path[array_index] = current_id;
	printf("current_id: %d\n", current_id);

	while(hashmapGet(path_map, current_id) != -1 && current_id != start) {
		astar_node* v = (astar_node*)hashmapGet(path_map, current_id);
		current_id = v->v_id;
		array_index++;
		printf("current_id: %d\n", current_id);
		append_to_array(&total_path, array_index, path_size, current_id);
	}

	if (current_id != start) {
		printf("path didnt have start...\n");
		return NULL;
	} else {
		path_size = append_to_array(&total_path, array_index, path_size, current_id);
	}
	hashmapDelete(path_map);
	return total_path;
}

int append_to_array(int** arr, int i, int arr_size, int to_add){
	if (i == arr_size) {
		arr_size *= 2;
		*arr = realloc(*arr, arr_size);
	}
	(*arr)[i] = to_add;
	return arr_size;
}

astar_node* init_astar_node(int v_id, int g_val, int h_val){
	astar_node* node = malloc(sizeof(astar_node));
	node->v_id = v_id;
	node->g_val = g_val;
	node->h_val = h_val;
	node->f_val = g_val + h_val;
	return node;
}

astar_node* pop_smallest(bnode** root){
	bnode* min = get_min_bnode(*root);
	astar_node* data = (astar_node*)(min->data);
	*root = delete_bnode_with_v_id(*root, min->key, data->v_id);
	return data;
}

//ans^2 = sqrt(x^2 + y^2 + z^2)
//at such a small scale, curvature of earth shouldn't matter
int get_distance_heuristic(graph* graph, int start, int goal){
	vertex* v_c = get_vertex(graph, start);
	vertex* v_n = get_vertex(graph, goal);
	int ans = sub_and_sqre(v_c->latitude, v_n->latitude) + sub_and_sqre(v_c->longitude, v_n->longitude)
			+ sub_and_sqre(v_c->altitude, v_n->altitude);

	return sqrt(ans);
}

int get_cost(graph* graph, int curr, int neighbour){
	vertex* v_c = get_vertex(graph, curr);
	adjacencyList* adjList = v_c->adjList;
	for (int i = 0; i<adjList->num_neighbours; i++) {
		if (adjList->neighbours[i] == neighbour) {
			return adjList->costs[i].distance_cost;
		}
	}
	//TODO: could this cause an overflow?
	return INT_MAX;
}

void print_path(graph* graph, int start, int goal){
	int* path = a_star(graph, start, goal);
	if (path == NULL) {
		return;
	}

	int curr = 0;
	while(path[curr] != start) {
		printf("step: %d, vid: %d\n", curr, path[curr]);
		curr++;
	}
	printf("step: %d, vid: %d\n\n", curr, path[curr]);
	free(path);
}
