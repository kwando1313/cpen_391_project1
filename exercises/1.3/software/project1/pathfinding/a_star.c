#include "graph.h"
#include "b_tree.h"
#include "hashmap.h"
#include "misc_helpers.h"
#include <math.h>
#include <assert.h>

#define DEFAULT_PATH_SIZE 8

astar_node* init_astar_node(int v_id, int g_val, int h_val);
int get_distance_heuristic(graph* graph, int start, int goal);
int get_cost(graph* graph, int curr, int neighbour);
astar_node* pop_smallest(bnode** root);
int* reconstruct_path(hashmap* path_map, int start, int current_id);
int append_to_array(int** arr, int i, int arr_size, int to_add);
void append_to_path_points_array(path_points* path, int i, Point to_add);

//debugging only
void print_astar_node(astar_node* node);

/*
 * Notes on datastructures chosen
 *
 * closed_set:
 * - searchable by v_id
 * - insert a v_id
 * - hashset
 *
 * path:
 * - map random vertices to each other
 * - hashmap
 *
 * open_set:
 * - find smallest f val, remove smallest f val
 * - add item
 * - searchable
 * - chosen btree(O(logn) for all). Heap would be O(n) to search, O(logn) for find/remove, O(logn) to add.
 */
int* a_star(graph* graph, int start, int goal){
	hashmap* closed_set = hashmapCreate(DEFAULT_PATH_SIZE);
	hashmap* path = hashmapCreate(DEFAULT_PATH_SIZE);

	astar_node* curr_node = init_astar_node(start, 0, get_distance_heuristic(graph, start, goal));

	//maps fval to astar_node
	bnode* open_set = create_new_bnode(curr_node->f_val, curr_node);

	hashmap* vid_to_astar_node = hashmapCreate(DEFAULT_PATH_SIZE);
	hashmapInsert(vid_to_astar_node, curr_node, curr_node->v_id);

	while(open_set != NULL) {
		curr_node = pop_smallest(&open_set); //pop off the (estimated) best node
		hashmapRemove(vid_to_astar_node, curr_node->v_id);

		astar_node* next_node;

		if (curr_node->v_id == goal) {
			hashmapDelete(closed_set);
			free_tree(open_set, true);
			hashmapDelete(vid_to_astar_node);
			free(curr_node);
			return reconstruct_path(path, start, goal);
		}

		hashmapInsert(closed_set, NULL, curr_node->v_id);
		vertex* curr_vertex = get_vertex(graph, curr_node->v_id);

		int num_neighbours = curr_vertex->adjList->num_neighbours;

		for (int i = 0; i < num_neighbours; i++){
			int neighbour_id = curr_vertex->adjList->neighbours[i];

			if (hashmapGet(closed_set, neighbour_id) != HASHMAP_ERROR) {
				//already explored node
				continue;
			}

			int tentative_g = curr_node->g_val + get_cost(graph, curr_node->v_id, neighbour_id);

			//node hasnt been explored. Either in our list to explore, or completely brand new
			if (hashmapGet(vid_to_astar_node, neighbour_id) == HASHMAP_ERROR) {
				next_node = init_astar_node(neighbour_id, tentative_g, get_distance_heuristic(graph, neighbour_id, goal));
				open_set = insert_bnode(open_set, next_node->f_val, next_node);
				hashmapInsert(vid_to_astar_node, next_node, neighbour_id);
			} else {
				//get g score of neighbour
				next_node = (astar_node*) hashmapGet(vid_to_astar_node, neighbour_id);
				assert(next_node != HASHMAP_ERROR);

				if (tentative_g >= next_node->g_val) {
					// this path is not better
					continue;
				} else {
					//found a better path to that node
					open_set = delete_bnode_with_v_id(open_set, next_node->f_val, next_node->v_id);
					hashmapRemove(vid_to_astar_node, neighbour_id);

					next_node = init_astar_node(neighbour_id, tentative_g, get_distance_heuristic(graph, neighbour_id, goal));

					open_set = insert_bnode(open_set, next_node->f_val, next_node);
					hashmapInsert(vid_to_astar_node, next_node, neighbour_id);
				}
			}

			hashmapInsert(path, curr_vertex, next_node->v_id);
		}
	}
	printf("couldn't find a path %d, %d\n", start, goal);
	return NULL;
}

int* reconstruct_path(hashmap* path_map, int start, int current_id){
	int path_size = DEFAULT_PATH_SIZE;
	int array_index = 0;
	int* total_path = malloc(path_size*sizeof(int));
	total_path[array_index] = current_id;

	while(hashmapGet(path_map, current_id) != HASHMAP_ERROR && current_id != start) {
		astar_node* v = (astar_node*)hashmapGet(path_map, current_id);
		current_id = v->v_id;
		array_index++;
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
		int* tmp_arr = realloc(*arr, arr_size*sizeof(int));
		*arr = tmp_arr;
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
	return get_distance_heuristic(graph, curr, neighbour);
}

void print_path_console(graph* graph, int start, int goal){
	int* path = a_star(graph, start, goal);
	if (path == NULL) {
		return;
	}

	int curr = 0;
	printf("Going from %d to %d\n", goal, start);
	while(path[curr] != start) {
		printf("step: %d, vid: %d\n", curr, path[curr]);
		curr++;
	}
	printf("step: %d, vid: %d\n\n", curr, path[curr]);
	free(path);
}

path_points* get_path_points(graph* graph, int start, int goal){
	int* path_ids = a_star(graph, start, goal);
	assert(path_ids != NULL);
	int curr = 0;

	path_points* path = malloc(sizeof(path_points));
	path->ordered_point_arr = malloc(DEFAULT_PATH_SIZE*sizeof(Point));
	path->size = DEFAULT_PATH_SIZE;
	path->actual_size = 0;

	while(1) {
		vertex* v = get_vertex(graph, path_ids[curr]);
		Point to_add = get_vertex_xy(v);
		append_to_path_points_array(path, curr, to_add);
		if (path_ids[curr] == start) {
			break;
		}
		curr++;
	}

	free(path_ids);
	return path;
}

void append_to_path_points_array(path_points* path, int i, Point to_add){
	if (i == path->size) {
		path->size *= 2;
		path->ordered_point_arr = realloc(path->ordered_point_arr, path->size);
	}
	path->actual_size++;
	path->ordered_point_arr[i] = to_add;
}

void print_astar_node(astar_node* node){
	printf("v_id: %d, f_val %d, g_val %d, h_val %d\n", node->v_id, node->f_val, node->g_val, node->h_val);
}
