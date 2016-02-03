#include "graph.h"
#include "b_tree.h"
#include "hashmap.h"
#include "misc_helpers.h"
#include <math.h>

#define DEFAULT_CLOSED_SET_SIZE

astar_node* init_astar_node(int g_val, int h_val);
int get_distance_heuristic(graph* graph, int start, int goal);
int get_cost(graph* graph, int curr, int neighbour);
astar_node* pop_smallest(bnode** root);

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


//need to return a list -> ints, size of list
void a_star(graph* graph, int start, int goal){
	//TODO: closed_set should be replaced with hashset
	bnode* closed_set = NULL;
	hashmap* path = hashmapCreate(10);

	astar_node* start_node = init_astar_node(0, get_distance_heuristic(graph, start,goal));
	//maps fval to astar_node
	bnode* open_set = create_new_bnode(start_node->f_val, start_node);
	hashmap* vid_to_astar_node = hashmapCreate(10);
	hashmapInsert(vid_to_astar_node, start_node, start_node->v_id);

	while(open_set != NULL) {
		astar_node* curr_node = pop_smallest(&open_set); //pop off the (estimated) best node
		hashmapRemove(vid_to_astar_node, curr_node->v_id);

		astar_node* next_node;

		if (curr_node->v_id == goal) {
			printf("found the goal");
			//return reconstruct_path(path, goal);
		}

		closed_set = insert_bnode(closed_set, curr_node->v_id, NULL);
		vertex* curr_vertex = get_vertex(graph, curr_node->v_id);

		int num_neighbours = curr_vertex->adjList->num_neighbours;
		int* neighbours = curr_vertex->adjList->neighbours;

		for (int i = 0; i < num_neighbours; i++){
			int neighbour_id = neighbours[i];

			if (node_exists(closed_set, neighbour_id)) {
				//already explored node
				continue;
			}

			int tentative_g = curr_node->g_val + get_cost(graph, curr_node->v_id, neighbour_id);

			//node hasnt been explored. Either in our list to explore, or completely brand new
			if (hashmapGet(vid_to_astar_node, curr_node->v_id) == NULL) {
				next_node = init_astar_node(tentative_g, get_distance_heuristic(graph, neighbour_id,goal));
				open_set = insert_bnode(open_set, neighbour_id, next_node);
				hashmapInsert(vid_to_astar_node, next_node, neighbour_id);
			} else {
				//get g score of neighbour
				next_node = (astar_node*) get_data(open_set, neighbour_id);
				if (tentative_g >= next_node->g_val) {
					// this path is not better
					continue;
				} else {
					//found a better path to that node
					next_node = init_astar_node(tentative_g, get_distance_heuristic(graph, neighbour_id,goal));
					open_set = insert_bnode(open_set, neighbour_id, next_node);
					hashmapInsert(vid_to_astar_node, next_node, neighbour_id);
				}
			}

			hashmapInsert(path, curr_vertex, curr_node->v_id);
		}
	}
	printf("couldn't find a path");
}


/*
function reconstruct_path(Came_From,current)
    total_path := [current]
    while current in Came_From.Keys:
        current := Came_From[current]
        total_path.append(current)
    return total_path
 */

astar_node* init_astar_node(int g_val, int h_val){
	astar_node* node = malloc(sizeof(astar_node));
	node->g_val = g_val;
	node->h_val = h_val;
	node->f_val = g_val + h_val;
	return node;
}

astar_node* pop_smallest(bnode** root){
	bnode* min = get_min_bnode(*root);
	astar_node* data = (astar_node*)min->data;
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

	return sqrtf(ans);
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
