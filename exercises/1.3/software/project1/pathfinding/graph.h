#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>
#include <stdio.h>
#include "misc_helpers.h"

#define DEFAULT_NUM_NEIGHBOURS 4
#define DEFAULT_GRAPH_SIZE 32
#define DOUBLE_TO_INT_MULTIPLIER 100

typedef struct __path_points{
	Point* ordered_point_arr;
	int size; //Better way to do this?
	int actual_size; //Better way to do this?
} path_points;

typedef struct __astar_node{
	int v_id;
	int f_val; //estimated total cost from start, through this, to goal
	int g_val; //cost so far, from start to current
	int h_val; //heuristic val based on distance to goal
} astar_node;

typedef struct __cost{
	//TODO: replace this with some other bs. We already cover distance with get_distance_heuristic
	int distance_cost;
} cost;

typedef struct __adjacencyList{
	int max_neighbours;
	int num_neighbours;
	// TODO find better solution to this if memory is an issue
	// costs are symmetric
	cost* costs;
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
    int x, y;
    adjacencyList* adjList;
} vertex;

typedef struct __graph {
	int max_vertices;
    int num_vertices;
    vertex** vertices;
} graph;

graph* init_graph(int inital_num_vertices);
void destroy_graph(graph* graph);
//returns id of added vertex
vertex* init_vertex(int latitude, int longitude, int altitude, char* name, int x, int y);
int add_vertex(graph* graph, vertex* v);
vertex* get_vertex(graph* graph, int id);
void add_edge(graph* graph, int v0_id, int v1_id, cost cost_between_nodes);
bool remove_edge(graph* graph, int v0_id, int v1_id);
bool vertex_has_edge(vertex* v, int v1_id);
bool graph_has_edge(graph* graph, int v0_id, int v1_id);

//int find_vertex(graph* graph, char* name);

int* a_star(graph* graph, int start, int goal);
void print_path_console(graph* graph, int start, int goal);
path_points* get_path_points(graph* graph, int start, int goal);
void destroy_path_points(path_points* path);
void draw_graph(graph* graph, int v_colour, int edge_colour);

#endif
