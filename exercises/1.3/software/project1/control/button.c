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
		DIR_BUTT.p = do_dir;
	break;

	case 32:
		PHOTO_BUTT.top = PT;
		PHOTO_BUTT.bottom = PB;
		PHOTO_BUTT.left = PL;
		PHOTO_BUTT.right = PR;
		PHOTO_BUTT.p = do_photo;
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
		NORTH_BUTT.kb_p = do_up;
	break;

	case 38:
		SOUTH_BUTT.top = ST;
		SOUTH_BUTT.bottom = SB;
		SOUTH_BUTT.left = SL;
		SOUTH_BUTT.right = SR;
		SOUTH_BUTT.p = do_south;
		SOUTH_BUTT.p = do_down;
	break;

	default:
		return;
	break;
	}
}

void init_keyboard(){
	//keyboard = malloc(sizeof(Button)*N_KEYS); // MIGHT NOT NEED THIS

	// KB buttons
	for(int i = 0; i < KB_KEYS; i++){
		init_kb_button(KEYS[i], i);
	}

	// Screen buttons
	for(int i = KB_KEYS; i < N_KEYS; i++){
		init_s_button(KEYS[i], i);
	}
}

// MIGHT NOT NEED THIS
// void destroy_keyboard(Button* keyboard){
//	for(int i = 0; i < N_KEYS; i++){
//		free(keyboard[i]);
//	}
//	free(keyboard);
//}

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

	// North and South buttons used in search mode to select matching search entry
	for(int j = N_KEYS-2; j < N_KEYS; j++){
		Point p_f = GetRelease();
		printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

		if(falls_inside(p_f, keyboard[j])){
			return &keyboard[j];
		}
		else
			return NULL;
	}

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
	directions_screen();
	read_gps();
	printf("done do dir\n");

}

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
	move_img (LEFT);
}

// Translate the map east
void do_east(){
	move_img (RIGHT);
}

// Translate the map north
void do_north(){
	move_img (UP);
}

// Translate the map south
void do_south(){
	move_img (DOWN);
}

// Select the search match entry above the current selected
void do_up(char key){
	//printf("%c is up", key);
	if(si > 0)
		si--;
	else
		si++;
}

// Select the search match entry below the current selected
void do_down(char key){
	//printf("%c is down", key);
	if(si < mni)
		si++;
	else
		si--;
}

// Pop up the keyboard
void do_pop(){
	pop_screen();
	reset_query();
	kb_listen();
}

// Draws the character on the search bar and updates the search matcher
void do_key(char key){
	add_letter(key);

	/* Ignore the matcher if the string query length is below the threshhold to provide mathcings
	   Update and delete matches when we add letters */
	if(length() > SEARCH_THRESHHOLD){
		del_matches();
	}
	if(length() == SEARCH_THRESHHOLD){
		add_matches();
	}
}

// Deletes the front of the search bar and updates the search matcher
void do_del(){
	del_letter();

	/* Ignore the matcher if the string query is below the threshhold
	   Update and add matches when we delete letters  */
	if(length() >= SEARCH_THRESHHOLD){
		add_matches();
	}
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
	reset_query();

	init_screen(); //replace this
}
