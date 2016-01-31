#include <stdlib.h>
#include <assert.h>

#include "graph.h"

adjacencyList* init_adjList(void);
void add_directed_edge(adjacencyList* adjList, int vertex_id, cost cost);
//
//typedef struct __cost{
//	int distance_cost;
//} cost;
//
//typedef struct __adjacencyList{
//	int max_neighbours;
//	int num_neighbours;
//	cost* costs;
//	struct __vertex* neighbours;
//} adjacencyList;
//
//typedef struct __vertex {
//	char* name;
//	double latitude, longitude, altitude;
//  int x, y;
//  struct __adjacencyList adjList;
//} vertex;
//
//typedef struct __graph {
//	int max_vertices;
//    int num_vertices;
//    vertex* vertices;
//} graph;

graph* init_graph(int inital_max_vertices){
	graph* new_graph = malloc(sizeof(graph));
	new_graph->num_vertices = 0;
	new_graph->max_vertices = inital_max_vertices;
	new_graph->vertices = malloc(inital_max_vertices*sizeof(vertex));
	return new_graph;
}

//TODO - should all things be initialized here?
vertex init_vertex(int id){
	vertex new_vertex;
	new_vertex.id = id;
	new_vertex.adjList = init_adjList();
	return new_vertex;
}

adjacencyList* init_adjList(void){
	adjacencyList* adjList = malloc(sizeof(adjacencyList));
	adjList->max_neighbours = DEFAULT_NUM_NEIGHBOURS;
	adjList->num_neighbours = 0;
	adjList->costs = malloc(DEFAULT_NUM_NEIGHBOURS*sizeof(cost));
	adjList->neighbours = malloc(DEFAULT_NUM_NEIGHBOURS*sizeof(int));
	return adjList;
}

int add_vertex(graph* graph){
	int num_vertices = graph->num_vertices;
	if (num_vertices == graph->max_vertices) {
		//TODO better value for this? realloc is expensive, but NIOS II is shit
		graph->max_vertices *= 1.5;
		graph->vertices = realloc(graph->vertices, graph->max_vertices);
	}
	graph->vertices[num_vertices] = init_vertex(num_vertices);
	graph->num_vertices++;
	return num_vertices;
}

void add_edge(graph* graph, int vertex0_id, int vertex1_id, cost cost_0_to_1, cost cost_1_to_0){
	assert(vertex0_id < graph->num_vertices && vertex1_id < graph->num_vertices);
	vertex v0 = graph->vertices[vertex0_id];
	vertex v1 = graph->vertices[vertex1_id];
	add_directed_edge(v0.adjList, vertex1_id, cost_0_to_1);
	add_directed_edge(v1.adjList, vertex0_id, cost_1_to_0);
}

void add_directed_edge(adjacencyList* adjList, int vertex_id, cost cost){
	//TODO check for adding existing neighbour
	if (adjList->num_neighbours == adjList->max_neighbours){
		adjList->max_neighbours *= 1.5;
		adjList->costs = realloc(adjList->max_neighbours, adjList->costs);
		adjList->neighbours = realloc(adjList->max_neighbours, adjList->neighbours);
	}
	adjList->costs[adjList->num_neighbours] = cost;
	adjList->neighbours[adjList->num_neighbours] = vertex_id;
	adjList->num_neighbours++;
}

void destroy_graph(graph* graph){
	for (int i = 0; i < graph->num_vertices; i++) {
		vertex* curr = &graph->vertices[i];
		free(curr->adjList->costs);
		free(curr->adjList->neighbours);
		free(curr->adjList);
		free(curr->name);
	}
	free(graph->vertices);
	free(graph);
}

