#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include <math.h>
#include "misc_helpers.h"
#include "control.h"

#define ACCEPTABLE_DISTANCE 25

int get_valid_vertex(graph* graph, Point p);

// initialize and load up graphics on touchscreen
void init_control(){
	init_touch();
	init_screen();
}


// Display accordingly upon successfully pressing a button and return screen mode
int get_button(int a, int b){
	// Info Button
		if(a >= IL && a <= IR && b > IU && b <= ID){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c >= IL && c <= IR && d > IU && d <= ID){
				return INFO;
			}
		}
	// Directions Button
		else if(a > DL && a <= DR && b >= DU && b < DD){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c > DL && c <= DR && d >= DU && d < DD){
				return DIR;
			}
		}

		// Photo Button
		else if(a >= PL && a <= PR && b >= PU && b <= PD){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c >= PL && c <= PR && d >= PU && d <= PD){
				return PHOTO;
			}
		}

		// About Button
		else if(a > AL && a <= AR && b >= AU && b <= AD){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c > AL && c <= AR && d >= AU && d <= AD){
				return ABOUT;
			}
		}

		return NO_RESPONSE;
}

// Get the node from where we pressed
int get_node(graph* graph){

	int node_id = -1;

	while(node_id == -1){
		int a,b,c,d;
		Point p_i, p_f;
		do{
			p_i = GetPress();
			a = p_i.x;
			b = p_i.y;

			p_f = GetRelease();
			c = p_f.x;
			d = p_f.y;

		} while(sqrt(pow((c-a),2) + pow((d-b),2)) > RADIUS); //check for valid press&release

		// vertex p = init_vertex(c, d, 0, "press", c, d);
		// assuming we read have access to the graph data
		// IF WE CAN (especially for sprint2): create node in graph with coords a,b; find nearest node and check if distance < RADIUS
		// ELSE: iterate through the nodes in the graph like a dumbass and check if shortest distance < RADIUS
		node_id = get_valid_vertex(graph, p_f);
		if (node_id == -1) {
			printf("x: %d, y: %d", p_f.x, p_f.y);
			printf("Not a valid node\n");
		}
	}
	printf("returning node: %d\n", node_id);
	return node_id;
}

int get_valid_vertex(graph* graph, Point p){
	printf("started valid vertex\n");
	for(int i = 0; i<graph->num_vertices; i++) {
		vertex v = graph->vertices[i];
		if ((abs(v.x-p.x) < ACCEPTABLE_DISTANCE) && (abs(v.y-p.y) < ACCEPTABLE_DISTANCE) ){
			return v.id;
		}
	}
	return -1;
}


// Display info of the next node touched
void do_info(){
	// TODO: SPRINT2
	info_screen();
	//int node = get_node();
	return;
}

// Ask for a start and end node and find the best directions
void do_dir(graph* graph){
	directions_screen();
	draw_information_box("PLEASE SELECT STARTING POINT");
	int start_node = get_node(graph);
	draw_information_box("PLEASE SELECT DESTINATION");
	int end_node = get_node(graph);
	path_points* path = get_path_points(graph, start_node, end_node);
	draw_path(path->ordered_point_arr, path->actual_size, BLUE);
	destroy_path_points(path);
	draw_information_box("HAVE A FUN TRIP!");
}

// Display photo of the next node touched
void do_photo(){
	// TODO: SPRINT2
	photo_screen();
	//int node = get_node();

}

// Display app about
void do_about(){
	about_screen();
}

// Listen for button inputs
void listen(){
		graph* graph = create_test_graph(false);

		while(1){
			// Wait for button input
			Point p_i = GetPress();
			int a = p_i.x;
			int b = p_i.y;
			printf("Pressed Coordinates: (%i, %i)\n", a, b);

			int what_do = get_button(a, b);

			if(what_do == INFO){
				do_info();
			}
			else if(what_do == DIR){
				do_dir(graph);
			}
			else if(what_do == PHOTO){
				do_photo();
			}
			else if(what_do == ABOUT){
				do_about();
			}
		}
}


//TODO: remove after sprint 1
graph* create_test_graph(bool draw){
	cost default_cost = {0};
	graph* graph = init_graph(30);

	int v0id = add_vertex(graph, init_vertex(5, 5, 0, "v0", 3, 440));
	int v1id = add_vertex(graph, init_vertex(50, 400, 0, "v1", 10, 265));
	int v2id = add_vertex(graph, init_vertex(10000, 10000, 0, "v2", 26, 197));
	int v3id = add_vertex(graph, init_vertex(200, 200, 0, "v3", 51, 152));
	int v4id = add_vertex(graph, init_vertex(300, 300, 0, "v4", 107, 115));
	int v5id = add_vertex(graph, init_vertex(300, 300, 0, "v5", 181, 99));
	add_edge(graph, v0id, v1id, default_cost);
	add_edge(graph, v1id, v2id, default_cost);
	add_edge(graph, v2id, v3id, default_cost);
	add_edge(graph, v3id, v4id, default_cost);
	add_edge(graph, v4id, v5id, default_cost);

	//going down
	int v6id = add_vertex(graph, init_vertex(5, 5, 0, "v6", 180, 255));
	int v7id = add_vertex(graph, init_vertex(50, 400, 0, "v7", 104, 256));
	int v8id = add_vertex(graph, init_vertex(10000, 10000, 0, "v8", 104, 447));
	int v9id = add_vertex(graph, init_vertex(200, 200, 0, "v9", 180, 448));
	add_edge(graph, v5id, v6id, default_cost);
	add_edge(graph, v6id, v7id, default_cost);
	add_edge(graph, v7id, v8id, default_cost);
	add_edge(graph, v6id, v9id, default_cost);

	//back to intersection
	//going right along top road
	int v10id = add_vertex(graph, init_vertex(5, 5, 0, "v10id", 378, 89));
	int v11id = add_vertex(graph, init_vertex(50, 400, 0, "v11id", 242, 11));
	int v12id = add_vertex(graph, init_vertex(10000, 10000, 0, "v12id", 173, 53));
	int v13id = add_vertex(graph, init_vertex(200, 200, 0, "v13id", 460, 89));
	add_edge(graph, v5id, v10id, default_cost);
	add_edge(graph, v10id, v11id, default_cost);
	add_edge(graph, v11id, v12id, default_cost);
	add_edge(graph, v10id, v13id, default_cost);

	//going down
	int v14id = add_vertex(graph, init_vertex(200, 200, 0, "v14id", 459, 251));
	add_edge(graph, v13id, v14id, default_cost);

	//going left
	int v15id = add_vertex(graph, init_vertex(200, 200, 0, "v15id", 303, 252));
	add_edge(graph, v14id, v15id, default_cost);
	add_edge(graph, v15id, v9id, default_cost);

	//going left
	int v16id = add_vertex(graph, init_vertex(200, 200, 0, "v16id", 218, 254));
	add_edge(graph, v16id, v15id, default_cost);

	//going up
	int v17id = add_vertex(graph, init_vertex(200, 200, 0, "v17id", 303, 175));
	add_edge(graph, v15id, v17id, default_cost);
	add_edge(graph, v17id, v5id, default_cost);

	//going down
	int v18id = add_vertex(graph, init_vertex(5, 5, 0, "v18id", 303, 344));
	int v19id = add_vertex(graph, init_vertex(50, 400, 0, "v19id", 302, 442));
	int v20id = add_vertex(graph, init_vertex(10000, 10000, 0, "v20id", 459, 344));
	int v21id = add_vertex(graph, init_vertex(200, 200, 0, "v21id", 461, 440));
	add_edge(graph, v15id, v18id, default_cost);
	add_edge(graph, v18id, v19id, default_cost);
	add_edge(graph, v18id, v20id, default_cost);
	add_edge(graph, v20id, v21id, default_cost);
	add_edge(graph, v14id, v20id, default_cost);

	if (draw) {
		for(int i = 0; i<graph->num_vertices; i++) {
			vertex* v = get_vertex(graph, i);
			WriteAPixel(v->x, v->y, CYAN);
			adjacencyList* adjList = v->adjList;
			int num_edges = adjList->num_neighbours;
			for (int j = 0; j<num_edges; j++) {
				vertex* w = get_vertex(graph, adjList->neighbours[j]);
				Line(v->x, v->y, w->x, w->y, RED);
			}
		}

		for(int i = 0; i<graph->num_vertices; i++) {
			vertex* v = get_vertex(graph, i);
			WriteAPixel(v->x, v->y, YELLOW);
		}
	}

	return graph;
}
