#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "graphics.h"
#include "misc_helpers.h"
#include "graph.h"

#define GPS_MULTIPLIER 1e6

adjacencyList* init_adjList(void);
void add_directed_edge(adjacencyList* adjList, int vertex_id, cost cost);
bool remove_directed_edge(adjacencyList* adjList, int vertex_id);
int make_latitude_usable(float latitude);
int make_longitude_usable(float latitude);
void add_name(graph* graph, char* name);

graph* init_graph(int inital_max_vertices){
	graph* new_graph = malloc(sizeof(graph));
	new_graph->num_vertices = 0;
	new_graph->max_vertices = inital_max_vertices;
	new_graph->names_head = NULL;
	new_graph->names_tail = NULL;
	new_graph->vertices = malloc(inital_max_vertices*sizeof(vertex*));
	return new_graph;
}

vertex* init_vertex(int latitude, int longitude, float altitude, char* name,
		int zoomed_in_x, int zoomed_in_y, int zoomed_out_x, int zoomed_out_y){
	vertex* new_vertex = malloc(sizeof(vertex));
	new_vertex->id = -1;
	new_vertex->adjList = init_adjList();

	new_vertex->latitude = latitude;
	new_vertex->longitude = longitude;
	new_vertex->altitude = altitude;
	new_vertex->name = malloc(strlen(name));
	strcpy(new_vertex->name, name);

	new_vertex->name = strdup(name);
	new_vertex->zo_x = zoomed_out_x;
	new_vertex->zo_y = zoomed_out_y;
	new_vertex->zi_x = zoomed_in_x;
	new_vertex->zi_y = zoomed_in_y;
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

int add_vertex(graph* graph, vertex* v){
	int num_vertices = graph->num_vertices;
	if (num_vertices == graph->max_vertices) {
		graph->max_vertices *= 2;
		vertex** new_vertices = NULL;
		new_vertices = realloc(graph->vertices, sizeof(vertex*)*graph->max_vertices);
		graph->vertices = new_vertices;
	}
	add_name(graph, v->name);
	v->id = num_vertices;
	graph->vertices[num_vertices] = v;
	graph->num_vertices++;
	return num_vertices;
}

void add_edge(graph* graph, int v0_id, int v1_id, cost cost_between_nodes){
	// v0, v1 should exist in the graph
	assert(v0_id < graph->num_vertices && v1_id < graph->num_vertices);

	if (v0_id == v1_id) {
		printf("ERROR: trying add connect node (%d) to itself. Exiting.", v0_id);
		return;
	}

	vertex* v0 = get_vertex(graph, v0_id);
	vertex* v1 = get_vertex(graph, v1_id);
	if (vertex_has_edge(v0, v1_id) || vertex_has_edge(v1, v0_id)){
		printf("ERROR: trying to re-add edge %d, %d\n", v0_id, v1_id);
		return;
	}
	add_directed_edge(v0->adjList, v1_id, cost_between_nodes);
	add_directed_edge(v1->adjList, v0_id, cost_between_nodes);
}

void add_directed_edge(adjacencyList* adjList, int vertex_id, cost cost){
	if (adjList->num_neighbours == adjList->max_neighbours){
		adjList->max_neighbours *= 2;
		//wtf? why does eclipse not recognize my typedef...
		struct __cost* new_costs = realloc(adjList->costs, sizeof(cost)*adjList->max_neighbours);
		adjList->costs = new_costs;
		int* new_neighbours = realloc(adjList->neighbours, sizeof(int)*adjList->max_neighbours);
		adjList->neighbours = new_neighbours;
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

	vertex* v = graph->vertices[id];
	return v;
}

void destroy_graph(graph* graph){
	for (int i = 0; i < graph->num_vertices; i++) {
		vertex* curr = graph->vertices[i];
		free(curr->adjList->costs);
		free(curr->adjList->neighbours);
		free(curr->adjList);
		free(curr->name);
		free(curr);
	}
	free(graph->vertices);
	free(graph);
}

void destroy_path_points(path_points* path){
	free(path->ordered_point_arr);
	free(path);
}

// Draws the edges and nodes of the graph
void draw_graph(graph* graph, int v_colour, int edge_colour){
	for(int i = 0; i<graph->num_vertices; i++) {
		vertex* v = get_vertex(graph, i);
		//draw_node(v_colour, v);
		adjacencyList* adjList = v->adjList;
		int num_edges = adjList->num_neighbours;
		for (int j = 0; j<num_edges; j++) {
			vertex* w = get_vertex(graph, adjList->neighbours[j]);
			Point p_v = get_vertex_xy(v);
			Point p_w = get_vertex_xy(w);
			Line(p_v.x, p_v.y, p_w.x, p_w.y, edge_colour);
		}
	}
}

// Draws a filled-in circle with fixed a radius at a node
void draw_node(int colour, vertex* v){
	draw_filled_circle(get_vertex_xy(v), RADIUS, colour);
}

//TODO replace these with some hashmap thing
vertex* find_vertex_by_name(graph* graph, char* name){
	for (int i = 0; i<graph->num_vertices; i++) {
		vertex* v = get_vertex(graph, i);
		if (strcmp(name, v->name) == 0) {
			return v;
		}
	}
	return NULL;
}

//TODO replace this if we have more than >100 nodes or so
//TODO should this include altitude?
vertex* find_vertex_by_coords(graph* graph, int latitude, int longitude){
	int lat_i = latitude; //make_latitude_usable(latitude);
	int long_i = longitude; //make_longitude_usable(longitude);
	vertex* min_v = get_vertex(graph, 0);

	int min_dist = (int)sqrt(sub_and_sqre(lat_i, min_v->latitude)
							+ sub_and_sqre(long_i, min_v->longitude));

	for (int i = 1; i<graph->num_vertices; i++) {
		vertex* v = get_vertex(graph, i);
		int dist = (int)sqrt(sub_and_sqre(lat_i, v->latitude)
							+ sub_and_sqre(long_i, v->longitude));
		if (dist < min_dist){
			min_dist = dist;
			min_v = v;
		}
	}

	return min_v;
}

// call these to convert from the lat/long from gps to the lat/long used by the graph
// latitude of everything on ubc is 49.xxxxxx
// therefore, we only care about the 6 digits after the decimal
int make_latitude_usable(float latitude){
	int lat_i = latitude * GPS_MULTIPLIER;
	lat_i = lat_i % (int)GPS_MULTIPLIER;
	return lat_i;
}

//longitude of everything on ubc is 123.xxxxxx
int make_longitude_usable(float longitude){
	int long_i = longitude * GPS_MULTIPLIER;
	long_i = long_i % (int)GPS_MULTIPLIER;
	return long_i;
}

name_list* get_names(graph* graph){
	return graph->names_head;
}

void add_name(graph* graph, char* name){
	if (name == NULL || name == ""){
		return;
	}

	name_list* new_name = malloc(sizeof(name_list));
	new_name->name = strdup(name);
	new_name->next = NULL;

	if (graph->names_head == NULL) {
		graph->names_head = new_name;
		graph->names_tail = new_name;
	} else if (alphaBetize(graph->names_tail->name, name) <= 0){
		graph->names_tail->next = new_name;
		graph->names_tail = new_name;
	} else if (alphaBetize(graph->names_head->name, name) >= 0){
		new_name->next = graph->names_head;
		graph->names_head = new_name;
	} else{
		name_list* prev = graph->names_head;
		name_list* curr = prev->next;
		while(curr && alphaBetize(curr->name, name) < 0){
			prev = curr;
			curr = curr->next;
		}

		prev->next = new_name;
		new_name->next = curr;
		if (curr == NULL){
			graph->names_tail = new_name;
		}

	}
}

void print_names(graph* graph){
	name_list* curr = graph->names_head;
	printf("node names:\n");
	while(curr != NULL){
		printf("%s\n", curr->name);
		curr = curr->next;
	}
}

Point get_vertex_xy(vertex* v){
	Point p;
	if (zoom_level == ZOOM_OUT){
		p.x = v->zo_x;
		p.y = v->zo_y;
	} else {
		p.x = v->zi_x;
		p.y = v->zi_y;
	}
	return p;
}
