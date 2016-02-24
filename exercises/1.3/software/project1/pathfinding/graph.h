#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>
#include <stdio.h>
#include "misc_helpers.h"
#include "image.h"

#define DEFAULT_NUM_NEIGHBOURS 4
#define DEFAULT_GRAPH_SIZE 64

#define ROAD_COST 0
#define PATH_COST 1

typedef struct __name_list{
	char* name;
	struct __name_list* next;
} name_list;

typedef struct __path_points{
	Point* ordered_point_arr;
	Point min_corner;
	Point max_corner;
	int size; //Better way to do this?
	int actual_size; //Better way to do this?
} path_points;

typedef struct __astar_node{
	int v_id;
	int f_val; //estimated total cost from start, through this, to goal
	int g_val; //cost so far, from start to current
	int h_val; //heuristic val based on distance to goal
} astar_node;

typedef struct __adjacencyList{
	int max_neighbours;
	int num_neighbours;
	bool* roads;
	//too much work to sort, not worth it, max neighbours will probably be ~10
	int* neighbours;
} adjacencyList;

//vertex id should be unique. vertices[vertex.id] == vertex
//doesnt cover case if vertex is removed -> dont think this is necessary atm
typedef struct __vertex {
	int id;
	char* name;
	//TODO: look over this
	//obviously these aren't ints, but im worried about floats/double seeping into astar,
	//and not being able to find the value we need.
	//we should multiply lat/long/alt on creation by some constant(defined above)
	//to maintain precision
	int latitude, longitude, altitude;
    int zo_x, zo_y;
    int zi_x, zi_y;
    adjacencyList* adjList;
} vertex;

typedef struct __graph {
	int max_vertices;
    int num_vertices;
    name_list* names_head;
    name_list* names_tail;
    vertex** vertices;
} graph;

graph* full_map_graph;
//const static Point NULL_CORNER = {-1,-1};
Point prev_min_corner, prev_max_corner;

/* basics */
graph* init_graph(int inital_num_vertices);
void destroy_graph(graph* graph);
//returns id of added vertex
vertex* init_vertex(int latitude, int longitude, float altitude, char* name,
		int zoomed_in_x, int zoomed_in_y, int zoomed_out_x, int zoomed_out_y);
int add_vertex(graph* graph, vertex* v);
vertex* get_vertex(graph* graph, int id);
void add_edge(graph* graph, int v0_id, int v1_id, bool road);
bool remove_edge(graph* graph, int v0_id, int v1_id);
bool vertex_has_edge(vertex* v, int v1_id);
bool graph_has_edge(graph* graph, int v0_id, int v1_id);
Point get_vertex_xy(vertex* v);
bool edge_is_road(graph* graph, int v0_id, int v1_id);

/* pathfinding */
int* a_star(graph* graph, int start, int goal, bool roads_only);
void print_path_console(graph* graph, int start, int goal, bool roads_only);
path_points* get_path_points(graph* graph, int start, int goal, bool roads_only);
void destroy_path_points(path_points* path);
void draw_graph_path(graph* graph, int start, int goal, bool roads_only, int colour);

/* other */
vertex* find_vertex_by_name(graph* graph, char* name);
vertex* find_vertex_by_coords(graph* graph, int latitude, int longitude);

void draw_graph(graph* graph, int v_colour, int edge_colour);
void draw_node(int colour, vertex* v);

void print_name_list(name_list* nl);
name_list* get_names(graph* graph);

#endif
