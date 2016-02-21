#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "misc_helpers.h"
#include "button.h"
#include "menu.h"
#include "touchscreen.h"
#include "control.h"
#include "Directions.h"
#include "search.h"
#include "gps.h"
#include <stdbool.h>

bool zoom = false;

const char KEYS[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '-',
			  	  	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '+',
			  	  	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', '<',
			  	  	'!', '@', '#', '$', '%',
			  	  	'a', 'd', 'w', 's'};

void init_kb_button(char key, int id){
	keyboard[id].key = key;
	keyboard[id].id = id;

	// We can use the id to know where to draw
	int i;
	int j;
	// Del, Enter, Space, and Back are special cases
	if(id < DEL_BUTT.id){
		i = id;
		j = 0;
	}
	else if(id == DEL_BUTT.id){
		DEL_BUTT.left = 430;
		DEL_BUTT.right = 470;
		DEL_BUTT.top = 330;
		DEL_BUTT.bottom = 370;
		DEL_BUTT.p = do_del;
		return;
	}
	else if(id < ENTER_BUTT.id){
		i = id - 11;
		j = 1;
	}
	else if(id == ENTER_BUTT.id){
		ENTER_BUTT.left = 390;
		ENTER_BUTT.right = 470;
		ENTER_BUTT.top = 370;
		ENTER_BUTT.bottom = 410;
		ENTER_BUTT.ent_p = do_enter;
		return;
	}
	else if(id >= 21 && id < SPACE_BUTT.id){
		i = id - 21;
		j = 2;
	}
	else if(id == SPACE_BUTT.id){
		SPACE_BUTT.left = 310;
		SPACE_BUTT.right = 390;
		SPACE_BUTT.top = 410;
		SPACE_BUTT.bottom = 450;
		SPACE_BUTT.kb_p = do_key;
		return;
	}
	else if(id == BACK_BUTT.id){
		BACK_BUTT.left = 390;
		BACK_BUTT.right = 470;
		BACK_BUTT.top = 410;
		BACK_BUTT.bottom = 450;
		BACK_BUTT.p = do_back;
		return;
	}
	keyboard[id].left = 30 + 40*i;
	keyboard[id].right = 70 + 40*i;
	keyboard[id].top = 330 + 40*j;
	keyboard[id].bottom = 370 + 40*j;
	keyboard[id].kb_p = do_key;
}

void init_s_button(char key, int id){
	keyboard[id].key = key;
	keyboard[id].id = id;

	switch (id){
	case 30:
		INFO_BUTT.top = IT;
		INFO_BUTT.bottom = IB;
		INFO_BUTT.left = IL;
		INFO_BUTT.right = IR;
		INFO_BUTT.p = do_info;
	break;

	case 31:
		DIR_BUTT.top = DT;
		DIR_BUTT.bottom = DB;
		DIR_BUTT.left = DL;
		DIR_BUTT.right = DR;
		//DIR_BUTT.p = do_dir;
		DIR_BUTT.p = do_dir; // REMOVE AFTER
	break;

	case 32:
		ZOOM_BUTT.top = PT;
		ZOOM_BUTT.bottom = PB;
		ZOOM_BUTT.left = PL;
		ZOOM_BUTT.right = PR;
		ZOOM_BUTT.p = do_zoom;
	break;

	case 33:
		ABOUT_BUTT.top = AT;
		ABOUT_BUTT.bottom = AB;
		ABOUT_BUTT.left = AL;
		ABOUT_BUTT.right = AR;
		ABOUT_BUTT.p = do_about;
	break;

	case 34:
		POP_BUTT.top = POPT;
		POP_BUTT.bottom = POPB;
		POP_BUTT.left = POPL;
		POP_BUTT.right = POPR;
		POP_BUTT.p = do_pop;
	break;

	case 35:
		WEST_BUTT.top = WT;
		WEST_BUTT.bottom = WB;
		WEST_BUTT.left = WL;
		WEST_BUTT.right = WR;
		WEST_BUTT.p = do_west;
	break;

	case 36:
		EAST_BUTT.top = ET;
		EAST_BUTT.bottom = EB;
		EAST_BUTT.left = EL;
		EAST_BUTT.right = ER;
		EAST_BUTT.p = do_east;
	break;

	case 37:
		NORTH_BUTT.top = NT;
		NORTH_BUTT.bottom = NB;
		NORTH_BUTT.left = NL;
		NORTH_BUTT.right = NR;
		NORTH_BUTT.p = do_north;
	break;

	case 38:
		SOUTH_BUTT.top = ST;
		SOUTH_BUTT.bottom = SB;
		SOUTH_BUTT.left = SL;
		SOUTH_BUTT.right = SR;
		SOUTH_BUTT.p = do_south;
	break;

	default:
		return;
	break;
	}
}

void init_keyboard(){
	//keyboard = malloc(sizeof(Button)*N_KEYS);

	// KB buttons
	for(int i = 0; i < KB_KEYS; i++){
		init_kb_button(KEYS[i], i);
	}

	// Screen buttons
	for(int i = KB_KEYS; i < N_KEYS; i++){
		init_s_button(KEYS[i], i);
	}
}

void destroy_keyboard(Button* keyboard){
//	for(int i = 0; i < N_KEYS; i++){
//		free(keyboard[i]);
//	}
	//free(keyboard);
}

/* Assumption: all of our buttons are rectangles. Aside: nodes aren't buttons but they are circles right now.
 * Returns true if the point is inside the button
 */
int falls_inside(Point p, Button b){
	return(falls_between(p.x, b.left, b.right) &&
		   falls_between(p.y, b.top, b.bottom));
}

// Returns the button that was pressed.
Button* get_s_button(Point p){
	for(int i = KB_KEYS; i < N_KEYS; i++){
		if(falls_inside(p, keyboard[i])){
			Point p_f = GetRelease();
			printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

			if(falls_inside(p_f, keyboard[i])){
				return &keyboard[i];
			}
			else
				return NULL;
		}
	}
	// Return the invalid button
	return NULL;
}

Button* get_kb_button(Point p){
	for(int i = 0; i < KB_KEYS; i++){
		if(falls_inside(p, keyboard[i])){
			Point p_f = GetRelease();
			printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

			if(falls_inside(p_f, keyboard[i])){
				return &keyboard[i];
			}
			else
				return NULL;
		}
	}
		// Return the invalid button
	return NULL;
}


// Display info of the next node touched
void do_info(){
	// TODO: Need to load up some info text for each node.
	info_screen();
	//int node = get_node();
	return;
}

//// Ask for a start and end node and find the best directions
void do_dir(){
//	printf("do dir\n");
//	directions_screen();
//	draw_information_box("PLEASE SELECT STARTING POINT");
//	int start_node = get_node(graph);
//	draw_information_box("PLEASE SELECT DESTINATION");
//	int end_node = get_node(graph);
//	path_points* path = get_path_points(graph, start_node, end_node);
//	draw_path(path->ordered_point_arr, path->actual_size, CYAN);
//	destroy_path_points(path);
//	draw_information_box("HAVE A FUN TRIP!");
	printf("start do dir\n");
	read_gps();
	printf("done do dir\n");

}

//Toggle between zoom in and zoom out
void do_zoom(){
	if (zoom){
		draw_zoomout();
		zoom = false;
	}
	else {
		Point sel = GetPress();
		if(sel.x < BOXWIDTH/2)
			sel.x = BOXWIDTH/2;
		else if(sel.x > INWIDTH - (BOXWIDTH/2))
			sel.x = INWIDTH - (BOXWIDTH/2);
		else if(sel.y < BOXHEIGHT/2)
			sel.y = BOXHEIGHT/2;
		else if(sel.y > INHEIGHT - (BOXHEIGHT/2))
			sel.y = INHEIGHT - (BOXHEIGHT/2);
		draw_zoomin(sel.x,sel.y);
		zoom = true;
	}
}

// Display app about
void do_about(void* nothing){
	about_screen();
}

// Translate the map left
void do_west(){
	if (zoom)
		move_img (LEFT);
}

// Translate the map east
void do_east(){
	if (zoom)
		move_img (RIGHT);
}

// Translate the map north
void do_north(){
	if (zoom)
		move_img (UP);
}

// Translate the map south
void do_south(){
	if (zoom)
		move_img (DOWN);
}

// Pop up the keyboard
void do_pop(){
	pop_screen();
	kb_listen();
}

// Draws the character on the search bar (buffer) and updates the search matcher
void do_key(char key){
	// TODO:
	printf("%c\n", key);
//	add_letter(key);
//	draw_word();
}

// Deletes the front of the search bar (buffer) and updates the search matcher
void do_del(){
	// TODO:
	printf("In do_del\n");
//	del();
//	draw_word();
}

/* On valid search, go to and highlight the searched node? Re-draw the map.
	On invalid search, display invalid search and keep listening for keyboard inputs */
bool do_enter(){
	// TODO: first check validity of search, add a name for every node and check if the input hits a match
	printf("In do_enter\n");
	do_back();
	return 1;
}

// Redraw the map
void do_back(){
	// TODO:
	printf("In do_back\n");
	init_screen(); //replace this
}
