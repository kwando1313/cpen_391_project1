#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>

#define DEFAULT_NUM_NEIGHBOURS 2

typedef struct __cost{
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
	double latitude, longitude, altitude;
    int x, y;
    adjacencyList* adjList;
} vertex;

typedef struct __graph {
	int max_vertices;
    int num_vertices;
    vertex* vertices;
} graph;

graph* init_graph(int inital_num_vertices);
void destroy_graph(graph* graph);
//returns id of added vertex
int add_vertex(graph* graph);
vertex* get_vertex(graph* graph, int id);
void add_edge(graph* graph, int v0_id, int v1_id, cost cost_between_nodes);
bool remove_edge(graph* graph, int v0_id, int v1_id);
bool vertex_has_edge(vertex* v, int v1_id);
bool graph_has_edge(graph* graph, int v0_id, int v1_id);

#endif
