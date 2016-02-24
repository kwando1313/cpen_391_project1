#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "gps.h"
#include "control.h"
#include "graphics.h"
#include "touchscreen.h"
#include <math.h>
#include "load_node.h"
#include "misc_helpers.h"
#include "button.h"

const static Point NULL_CORNER = {-1,-1};
extern Point curr_image_pos, prev_min_corner, prev_max_corner;
extern int zoom_level;

// Initialise and load up graphics on touchscreen
void init_control(){
	init_globals();
	Init_GPS();
	init_touch();
	init_screen();
	init_keyboard();
}

void init_globals(){
	prev_min_corner = NULL_CORNER;
	prev_max_corner = NULL_CORNER;
	zoom_level = ZOOM_OUT;
	Point p = {0,0};
	curr_image_pos = p;
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

		} while(sqrt(pow((c-a),2) + pow((d-b),2)) > RADIUS); //check for valid press & release

		node_id = get_valid_vertex(graph, p_f);
		if (node_id == -1) {
			printf("x: %d, y: %d", p_f.x, p_f.y);
			printf("Not a valid node\n");
			draw_information_box("NOT A VALID NODE.");
		}
	}
	printf("returning node: %d\n", node_id);
	return node_id;
}

/* Returns the node if we pressed a point sufficiently close to the node. Assumption: Each node has
   a finite metric in relation to every other node, i.e there is a maximum of one node sufficiently close.*/
//TODO optimize this shit yo
int get_valid_vertex(graph* graph, Point p){
	printf("started valid vertex\n");
	for(int i = 0; i<graph->num_vertices; i++) {
		vertex v = *graph->vertices[i];
		Point vertex_p = get_vertex_xy(&v);
		if (sqrt((pow((vertex_p.x-p.x),2) + pow((vertex_p.y-p.y),2))) <= RADIUS ){
			return v.id;
		}
	}
	return -1;
}

// Listen for screen button presses
void s_listen(){
	while(1){
		Button* butt;
		do{
			Point p_i = GetPress();
			printf("Pressed Coordinates: (%i, %i)\n", p_i.x, p_i.y);
			butt = get_s_button(p_i);
		}
		while(butt == NULL);
		butt->prs_p(*butt);
		butt->p();
	}
}

// Listen for keyboard + NORTH/SOUTH + ROAD button presses
void kb_listen(){
	while(1){
		Button* butt;
		do{
			Point p_i = GetPress();
			printf("Pressed Coordinates: (%i, %i)\n", p_i.x, p_i.y);
			butt = get_kb_button(p_i);
		}
		while(butt == NULL );

		butt->prs_p(*butt);
		if(butt->id != BACK_BUTT.id && butt->id != ENTER_BUTT.id && butt->id != DEL_BUTT.id && butt->id != ROAD_BUTT.id){
			butt->kb_p(butt->key);
		}

		// We are done with the keyboard upon BACK
		else if(butt->id == BACK_BUTT.id){
			butt->p();
			break;
		}

		// We are done with the keyboard upon valid search input
		else if(butt->id == ENTER_BUTT.id){
			if(butt->ent_p(*butt)){
				break;
			}
		}

		else if(butt->id == DEL_BUTT.id || butt->id == ROAD_BUTT.id){
			butt->p();
		}
	}
}

void load_from_sd(){
	load_zoom_in_image("zoomin.bmp");
	load_zoom_out_image("zoomout.bmp");
	draw_full_image();
	load_graph("nodes.txt");
}
