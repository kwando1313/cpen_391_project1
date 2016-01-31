#ifndef GRAPH_H_
#define GRAPH_H_

#define DEFAULT_NUM_NEIGHBOURS 2

typedef struct __cost{
	int distance_cost;
} cost;

typedef struct __adjacencyList{
	int max_neighbours;
	int num_neighbours;
	//TODO should these be sorted by id?
	cost* costs;
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
//returns id of added vertex
int add_vertex(graph* graph);
//TODO better names for cost
void add_edge(graph* graph, int v0, int v1, cost cost01, cost cost10);
//graph_has_edge or edge exists
void destroy_graph(graph* graph);

#endif
