#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include <math.h>
#include "misc_helpers.h"

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
void do_dir(){
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
				do_dir();
			}
			else if(what_do == PHOTO){
				do_photo();
			}
			else if(what_do == ABOUT){
				do_about();
			}
		}
}


