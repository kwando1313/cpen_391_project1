#include "graph.h"
//#include "min_heap.h"
#include "b_tree.h"
#include "hashmap.h"

#define DEFAULT_CLOSED_SET_SIZE

astar_node* init_astar_node(int g_val, int h_val);
int get_distance_heuristic(int start, int goal);
int get_cost(int curr, int neighbour);
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

	astar_node* start_node = init_astar_node(0, get_distance_heuristic(start,goal));
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

			int tentative_g = curr_node->g_val + get_cost(curr_node->v_id, neighbour_id);

			//node hasnt been explored. Either in our list to explore, or completely brand new
			if (hashmapGet(vid_to_astar_node, curr_node->v_id) == NULL) {
				next_node = init_astar_node(tentative_g, get_distance_heuristic(neighbour_id,goal));
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
					next_node = init_astar_node(tentative_g, get_distance_heuristic(neighbour_id,goal));
					open_set = insert_bnode(open_set, neighbour_id, next_node);
					hashmapInsert(vid_to_astar_node, next_node, neighbour_id);
				}
			}

			hashmapInsert(path, curr_vertex, curr_node->v_id);
		}
	}
		/*

		        for each neighbor of current
		            if neighbor in ClosedSet
		                continue		// Ignore the neighbor which is already evaluated.
		            tentative_g_score := g_score[current] + dist_between(current,neighbor) // length of this path.
		            if neighbor not in OpenSet	// Discover a new node
		                OpenSet.Add(neighbor)
		            else if tentative_g_score >= g_score[neighbor]
		                continue		// This is not a better path.

		            // This path is the best until now. Record it!
		            Came_From[neighbor] := current
		            g_score[neighbor] := tentative_g_score
		            f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)

		*/



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

//TODO implement this - just triangle distance for now?
int get_distance_heuristic(int start, int goal){
	return 1;
}

int get_cost(int curr, int neighbour){
	return 1;
}
