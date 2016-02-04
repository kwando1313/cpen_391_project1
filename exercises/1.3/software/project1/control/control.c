#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include <math.h>
#include "misc_helpers.h"
#include "control.h"

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
int get_node(){
	// TODO:
	Point p_i = GetPress();
	int a = p_i.x;
	int b = p_i.y;

	Point p_f = GetRelease();
	int c = p_f.x;
	int d = p_f.y;

	do{
	p_i = GetPress();
	a = p_i.x;
	b = p_i.y;

	p_f = GetRelease();
	c = p_f.x;
	d = p_f.y;
	} while(sqrt(pow((c-a),2) + pow((d-b),2)) > RADIUS);

	// vertex p = init_vertex(c, d, 0, "press", c, d);

	// assuming we read have access to the graph data

	// IF WE CAN (especially for sprint2): create node in graph with coords a,b; find nearest node and check if distance < RADIUS

	// ELSE: iterate through the nodes in the graph like a dumbass and check if shortest distance < RADIUS

	// return p

	return 0;
}


// Display info of the next node touched
void do_info(){
	// TODO: SPRINT2
	info_screen();
	int node = get_node();
	return;
}

// Ask for a start and end node and find the best directions
void do_dir(graph* graph){
	path_points* path = get_path_points(graph, 9, 13);
	draw_path(path->ordered_point_arr, path->actual_size, BLUE);
	destroy_path_points(path);
	// TODO:
	directions_screen();
	draw_information_box("PLEASE SELECT STARTING POINT");
	// vertex start_node = get_node();
	draw_information_box("PLEASE SELECT DESTINATION");
	// vertex end_node = get_node();
	// Now use a*star using nodes
}

// Display photo of the next node touched
void do_photo(){
	// TODO: SPRINT2
	photo_screen();
	int node = get_node();

}

// Display app about
void do_about(){
	about_screen();
}

// Listen for button inputs
void listen(){
		graph* graph = draw_test_graph();

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
graph* draw_test_graph(void){
	cost default_cost = {0};
	graph* graph = init_graph(30);

	int v0id = add_vertex(graph, init_vertex(5, 5, 0, "v0", 4, 425));
	int v1id = add_vertex(graph, init_vertex(50, 400, 0, "v1", 6, 260));
	int v2id = add_vertex(graph, init_vertex(10000, 10000, 0, "v2", 15, 214));
	int v3id = add_vertex(graph, init_vertex(200, 200, 0, "v3", 35, 178));
	int v4id = add_vertex(graph, init_vertex(300, 300, 0, "v4", 105, 132));
	int v5id = add_vertex(graph, init_vertex(300, 300, 0, "v5", 181, 92));
	add_edge(graph, v0id, v1id, default_cost);
	add_edge(graph, v1id, v2id, default_cost);
	add_edge(graph, v2id, v3id, default_cost);
	add_edge(graph, v3id, v4id, default_cost);
	add_edge(graph, v4id, v5id, default_cost);

	//going down
	int v6id = add_vertex(graph, init_vertex(5, 5, 0, "v6", 179, 249));
	int v7id = add_vertex(graph, init_vertex(50, 400, 0, "v7", 103, 251));
	int v8id = add_vertex(graph, init_vertex(10000, 10000, 0, "v8", 105, 428));
	int v9id = add_vertex(graph, init_vertex(200, 200, 0, "v9", 181, 424));
	add_edge(graph, v5id, v6id, default_cost);
	add_edge(graph, v6id, v7id, default_cost);
	add_edge(graph, v7id, v8id, default_cost);
	add_edge(graph, v6id, v9id, default_cost);

	//back to intersection
	//going right along top road
	int v10id = add_vertex(graph, init_vertex(5, 5, 0, "v10id", 394, 75));
	int v11id = add_vertex(graph, init_vertex(50, 400, 0, "v11id", 272, 8));
	int v12id = add_vertex(graph, init_vertex(10000, 10000, 0, "v12id", 172, 46));
	int v13id = add_vertex(graph, init_vertex(200, 200, 0, "v13id", 455, 75));
	add_edge(graph, v5id, v10id, default_cost);
	add_edge(graph, v10id, v11id, default_cost);
	add_edge(graph, v11id, v12id, default_cost);
	add_edge(graph, v10id, v13id, default_cost);

	//going down
	int v14id = add_vertex(graph, init_vertex(200, 200, 0, "v14id", 455, 249));
	add_edge(graph, v13id, v14id, default_cost);

	//going left
	int v15id = add_vertex(graph, init_vertex(200, 200, 0, "v15id", 305, 248));
	add_edge(graph, v14id, v15id, default_cost);
	add_edge(graph, v15id, v9id, default_cost);

	//going left
	int v16id = add_vertex(graph, init_vertex(200, 200, 0, "v16id", 226, 249));
	add_edge(graph, v16id, v15id, default_cost);

	//going up
	int v17id = add_vertex(graph, init_vertex(200, 200, 0, "v17id", 306, 160));
	add_edge(graph, v15id, v17id, default_cost);
	add_edge(graph, v17id, v5id, default_cost);

	//going down
	int v18id = add_vertex(graph, init_vertex(5, 5, 0, "v18id", 306, 346));
	int v19id = add_vertex(graph, init_vertex(50, 400, 0, "v19id", 306, 432));
	int v20id = add_vertex(graph, init_vertex(10000, 10000, 0, "v20id", 456, 347));
	int v21id = add_vertex(graph, init_vertex(200, 200, 0, "v21id", 456, 436));
	add_edge(graph, v15id, v18id, default_cost);
	add_edge(graph, v18id, v19id, default_cost);
	add_edge(graph, v18id, v20id, default_cost);
	add_edge(graph, v20id, v21id, default_cost);
	add_edge(graph, v14id, v20id, default_cost);

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

	return graph;
}
