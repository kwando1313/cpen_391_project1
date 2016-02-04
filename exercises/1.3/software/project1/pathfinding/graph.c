#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graph.h"

adjacencyList* init_adjList(void);
void add_directed_edge(adjacencyList* adjList, int vertex_id, cost cost);
bool remove_directed_edge(adjacencyList* adjList, int vertex_id);

graph* init_graph(int inital_max_vertices){
	graph* new_graph = malloc(sizeof(graph));
	new_graph->num_vertices = 0;
	new_graph->max_vertices = inital_max_vertices;
	new_graph->vertices = malloc(inital_max_vertices*sizeof(vertex));
	return new_graph;
}

vertex init_vertex(int latitude, int longitude, int altitude, char* name,
		int x, int y){
	vertex new_vertex;
	new_vertex.id = -1;
	new_vertex.adjList = init_adjList();
	new_vertex.latitude = latitude;
	new_vertex.longitude = longitude;
	new_vertex.altitude = altitude;
	new_vertex.name = name;
	new_vertex.x = x;
	new_vertex.y = y;
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

int add_vertex(graph* graph, vertex v){
	int num_vertices = graph->num_vertices;
	if (num_vertices == graph->max_vertices) {
		//TODO better value for this? realloc is expensive, but NIOS II is shit
		graph->max_vertices *= 1.5;
		graph->vertices = realloc(graph->vertices, graph->max_vertices);
	}
	v.id = num_vertices;
	graph->vertices[num_vertices] = v;
	graph->num_vertices++;
	return num_vertices;
}

void add_edge(graph* graph, int v0_id, int v1_id, cost cost_between_nodes){
	// v0, v1 should exist in the graph
	assert(v0_id < graph->num_vertices && v1_id < graph->num_vertices);

	vertex* v0 = get_vertex(graph, v0_id);
	vertex* v1 = get_vertex(graph, v1_id);
	if (vertex_has_edge(v0, v1_id) || vertex_has_edge(v1, v0_id)){
		printf("ERROR: trying to re-add an edge. Exiting.");
		return;
	}
	add_directed_edge(v0->adjList, v1_id, cost_between_nodes);
	add_directed_edge(v1->adjList, v0_id, cost_between_nodes);
}

void add_directed_edge(adjacencyList* adjList, int vertex_id, cost cost){
	if (adjList->num_neighbours == adjList->max_neighbours){
		adjList->max_neighbours *= 1.5;
		adjList->costs = realloc(adjList->costs, adjList->max_neighbours);
		adjList->neighbours = realloc(adjList->neighbours, adjList->max_neighbours);
	}
	adjList->costs[adjList->num_neighbours] = cost;
	adjList->neighbours[adjList->num_neighbours] = vertex_id;
	adjList->num_neighbours++;
}

bool remove_directed_edge(adjacencyList* adjList, int vertex_id){
	bool success = false;
	for(int i = 0; i < adjList->num_neighbours; i++) {
		int* neighbour = &adjList->neighbours[i];
		cost* curr_cost = &adjList->costs[i];
		if (*neighbour == vertex_id) {
			// since all we do is shift data from right to left to replace what we want to "delete",
			// there's no point in moving at the last spot
			if (i != adjList->num_neighbours-1){
				memmove(neighbour, neighbour+1, (adjList->num_neighbours-i-1)*sizeof(int));
				memmove(curr_cost, curr_cost+1, (adjList->num_neighbours-i-1)*sizeof(cost));
			}
			success = true;
			adjList->num_neighbours--;
			break;
		}
	}

	return success;
}

bool remove_edge(graph* graph, int v0_id, int v1_id){
	// v0, v1 should exist in the graph
	assert(v0_id < graph->num_vertices && v1_id < graph->num_vertices);

	vertex* v0 = get_vertex(graph, v0_id);
	vertex* v1 = get_vertex(graph, v1_id);
	bool success = remove_directed_edge(v0->adjList, v1_id) && remove_directed_edge(v1->adjList, v0_id);
	return success;
}

bool vertex_has_edge(vertex* v, int v1_id){
	adjacencyList* list = v->adjList;
	for(int i = 0; i < list->num_neighbours; i++) {
		if (list->neighbours[i] == v1_id){
			return true;
		}
	}

	return false;
}

bool graph_has_edge(graph* graph, int v0_id, int v1_id){
	assert(v0_id < graph->num_vertices && v1_id < graph->num_vertices);

	vertex* v0 = get_vertex(graph, v0_id);
	vertex* v1 = get_vertex(graph, v1_id);
	bool exists = vertex_has_edge(v0, v1_id) && vertex_has_edge(v1, v0_id);
	return exists;
}

vertex* get_vertex(graph* graph, int id){
	assert(id < graph->num_vertices);

	vertex* v = &graph->vertices[id];
	return v;
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


