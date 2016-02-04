#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"

// initialize and load up graphics on touchscreen
void init_control(){
	init_touch();
	init_screen();
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

// Display info of the next node touched
void do_info(){
	// TODO:
	info_screen();
	int node = get_node();

}

// Ask for a start and end node and find the best directions
void do_dir(){
	// TODO:
	directions_screen();
	int start_node = get_node();
	int end_node = get_node();
	// Now use a*star using nodes
}

// Display photo of the next node touched
void do_photo(){
	// TODO:
	photo_screen();
	int node = get_node();

}

// Display app about
void do_about(){
	about_screen();
}

// Get the node from where we pressed
int get_node(){
	// TODO:
	Point p = GetRelease();
	int a = p.x;
	int b = p.y;

	// IF WE CAN: create node in graph with coords a,b; find nearest node and check if distance is good
	// ELSE: iterate through the nodes in the graph like a dumbass and check if shortest distance is good
	// return node

	return 0;
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




