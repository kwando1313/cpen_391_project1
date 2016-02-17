#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "misc_helpers.h"
#include "button.h"
#include "menu.h"
#include "touchscreen.h"
#include "control.h"

const char KEYS[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '-',
			  	  	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '+',
			  	  	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', '<',
			  	  	'!', '@', '#', '$', '%',
			  	  	'a', 'd', 'w', 's'};

void init_kb_button(char key, int id){
	keyboard[id].key = key;
	keyboard[id].id = id;

	/*TODO: We can use the id to know where to draw.
			Use the key to initialise the fcn ptr is. */
	keyboard[id].left = 0;
	keyboard[id].right = 0;
	keyboard[id].top = 0;
	keyboard[id].bottom = 0;
	keyboard[id].kb_p = do_key;
}

void init_s_button(char key, int id){
	keyboard[id].key = key;
	keyboard[id].id = id;
}

void init_keyboard(){
	Button* keyboard = malloc(sizeof(Button)*N_KEYS);

	// KB buttons
	for(int i = 0; i < KB_KEYS; i++){
		init_kb_button(KEYS[i], i);
	}
	DEL_BUTT.p = do_del;
	ENTER_BUTT.ent_p = do_enter;
	BACK_BUTT.p = do_back;

	// Screen buttons
	for(int i = KB_KEYS; i < N_KEYS - 1; i++){
		init_s_button(KEYS[i], i);
	}
	INFO_BUTT.p = do_info;
	INFO_BUTT.top = IT;
	INFO_BUTT.bottom = IB;
	INFO_BUTT.left = IL;
	INFO_BUTT.right = IR;

	//DIR_BUTT.p = do_dir;
	DIR_BUTT.top = DT;
	DIR_BUTT.bottom = DB;
	DIR_BUTT.left = DL;
	DIR_BUTT.right = DR;

	PHOTO_BUTT.p = do_photo;
	PHOTO_BUTT.top = PT;
	PHOTO_BUTT.bottom = PB;
	PHOTO_BUTT.left = PL;
	PHOTO_BUTT.right = PR;

	ABOUT_BUTT.p = do_about;
	ABOUT_BUTT.top = AT;
	ABOUT_BUTT.bottom = AB;
	ABOUT_BUTT.left = AL;
	ABOUT_BUTT.right = AR;

	POP_BUTT.p = do_pop;
	POP_BUTT.top = ST;
	POP_BUTT.bottom = SB;
	POP_BUTT.left = SL;
	POP_BUTT.right = SR;

	WEST_BUTT.p = do_west;
	WEST_BUTT.top = WT;
	WEST_BUTT.bottom = WB;
	WEST_BUTT.left = WL;
	WEST_BUTT.right = WR;

	EAST_BUTT.p = do_east;
	EAST_BUTT.top = ET;
	EAST_BUTT.bottom = EB;
	EAST_BUTT.left = EL;
	EAST_BUTT.right = ER;

	NORTH_BUTT.p = do_north;
	NORTH_BUTT.top = NT;
	NORTH_BUTT.bottom = NB;
	NORTH_BUTT.left = NL;
	NORTH_BUTT.right = NR;

	SOUTH_BUTT.p = do_south;
	SOUTH_BUTT.top = ST;
	SOUTH_BUTT.bottom = SB;
	SOUTH_BUTT.left = SL;
	SOUTH_BUTT.right = SR;
}

void destroy_keyboard(Button* keyboard){
//	for(int i = 0; i < N_KEYS; i++){
//		free(keyboard[i]);
//	}
	free(keyboard);
}

/* Assumption: all of our buttons are rectangles. Aside: nodes aren't buttons but they are circles right now.
 * Returns true if the point is inside the button
 */
int falls_inside(Point p, Button b){
	return(falls_between(p.x, b.left, b.right) &&
		   falls_between(p.y, b.top, b.bottom));
}

// Returns the button that was pressed. Do we want better search despite fixed small keyboard?
Button* get_button(Point p){
	for(int i = 0; i < N_KEYS; i++){
		if(falls_inside(p, keyboard[i])){
			Point p_f = GetRelease();
			printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

			if(falls_inside(p_f, keyboard[i]))
				return &keyboard[i];
			else
				return NULL;
		}
	}
	// Return the invalid button
	return NULL;
}

// Display info of the next node touched
void do_info(void* nothing){
	// TODO: Need to load up some info text for each node.
	info_screen();
	//int node = get_node();
	return;
}

//// Ask for a start and end node and find the best directions
//void do_dir(void* graph){
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
//	printf("done do dir\n");
//}

// Display photo of the next node touched
void do_photo(void* nothing){
	// TODO: Need to load up a photo for each node
	photo_screen();
	//int node = get_node();

}

// Display app about
void do_about(void* nothing){
	about_screen();
}

// Translate the map left
void do_west(){
	// TODO:
}

// Translate the map east
void do_east(){
	// TODO:
}

// Translate the map north
void do_north(){
	// TODO:
}

// Translate the map south
void do_south(){
	// TODO:
}

// Pop up the keyboard
void do_pop(void* nothing){
	pop_screen();
	kb_listen();
}

// Draws the character on the search bar (buffer) and updates the search matcher
void do_key(char key){
	// TODO:
	printf("%c\n", key);
}

// Deletes the front of the search bar (buffer) and updates the search matcher
void do_del(){
	// TODO:
}

/* On valid search, go to and highlight the searched node? Re-draw the map.
	On invalid search, display invalid search and keep listening for keyboard inputs */
bool do_enter(){
	// TODO: first check validity of search
	do_back();
	return 1;
}

// Redraw the map
void do_back(){
	// TODO:
}
