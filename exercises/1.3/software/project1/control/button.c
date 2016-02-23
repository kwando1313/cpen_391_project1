#include <stdio.h>
#include <stdlib.h>
#include "button.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "misc_helpers.h"
#include "menu.h"
#include "touchscreen.h"
#include "control.h"
#include "Directions.h"
#include "search.h"
#include "gps.h"
#include "graph.h"

extern Point curr_image_pos;
extern int zoom_level;
extern int button_iteration;

const char KEYS[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '<',
			  	  	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '+',
			  	  	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', '>',
			  	  	'!', '@', '#', '$', '%',
			  	  	'a', 'd', 'w', 's', '^'};

// Initialise buttons on the keyboard
void init_kb_button(char key, int id){
	keyboard[id].key = key;
	keyboard[id].id = id;
	keyboard[id].pressed = false;
	keyboard[id].prs_p = flicker;

	// We can use the id to know where to draw
	int i = 0;
	int j = 0;
	// Del, Enter, Space, and Back are special cases
	if(id < DEL_BUTT.id){
		i = id;
		j = 0;
	}
	else if(id == DEL_BUTT.id){
		i = id;
		j = 0;
		keyboard[id].left = KB_LEFT + KEY_SIZE*i;
		keyboard[id].right = (KB_LEFT+KEY_SIZE) + KEY_SIZE*i;
		keyboard[id].top = KB_TOP + KEY_SIZE*j;
		keyboard[id].bottom = (KB_TOP + KEY_SIZE) + KEY_SIZE*j;
		DEL_BUTT.p = do_del;
		DEL_BUTT.text = "<-";
		return;
	}
	else if(id < ENTER_BUTT.id){
		i = id - 11;
		j = 1;
	}
	else if(id == ENTER_BUTT.id){
		i = id - 11;
		j = 1;
		keyboard[id].left = KB_LEFT + KEY_SIZE*i;
		keyboard[id].right = (KB_LEFT+KEY_SIZE*2) + KEY_SIZE*i;
		keyboard[id].top = KB_TOP + KEY_SIZE*j;
		keyboard[id].bottom = (KB_TOP + KEY_SIZE) + KEY_SIZE*j;
		ENTER_BUTT.ent_p = do_enter;
		ENTER_BUTT.text = "ENTER";
		return;
	}
	else if(id >= 21 && id < SPACE_BUTT.id){
		i = id - 21;
		j = 2;
	}
	else if(id == SPACE_BUTT.id){
		i = id - 21;
		j = 2;
		keyboard[id].left = KB_LEFT + KEY_SIZE*i;
		keyboard[id].right = (KB_LEFT+KEY_SIZE*2) + KEY_SIZE*i;
		keyboard[id].top = KB_TOP + KEY_SIZE*j;
		keyboard[id].bottom = (KB_TOP + KEY_SIZE) + KEY_SIZE*j;
		SPACE_BUTT.kb_p = do_key;
		SPACE_BUTT.text = "SPACE";
		return;
	}
	else if(id == BACK_BUTT.id){
		i = id - 21;
		j = 2;
		keyboard[id].left = (KB_LEFT+KEY_SIZE) + KEY_SIZE*i;
		keyboard[id].right = (KB_LEFT+KEY_SIZE*2) + KEY_SIZE*i;
		keyboard[id].top = KB_TOP + KEY_SIZE*j;
		keyboard[id].bottom = (KB_TOP + KEY_SIZE) + KEY_SIZE*j;
		BACK_BUTT.p = do_back;
		BACK_BUTT.text = "BACK";
		return;
	}
	keyboard[id].left = KB_LEFT + KEY_SIZE*i;
	keyboard[id].right = (KB_LEFT+KEY_SIZE) + KEY_SIZE*i;
	keyboard[id].top = KB_TOP + KEY_SIZE*j;
	keyboard[id].bottom = (KB_TOP + KEY_SIZE) + KEY_SIZE*j;
	keyboard[id].kb_p = do_key;
}

// Initialise buttons on the screen not on the keyboard
void init_s_button(char key, int id){
	keyboard[id].key = key;
	keyboard[id].id = id;
	keyboard[id].pressed = false;

	switch (id){
	case 30:
		INFO_BUTT.top = IT;
		INFO_BUTT.bottom = IB;
		INFO_BUTT.left = IL;
		INFO_BUTT.right = IR;
		INFO_BUTT.p = do_info;
		INFO_BUTT.prs_p = flicker;
		INFO_BUTT.text = "INFO";
	break;

	case 31:
		DIR_BUTT.top = DT;
		DIR_BUTT.bottom = DB;
		DIR_BUTT.left = DL;
		DIR_BUTT.right = DR;
		DIR_BUTT.p = do_dir;
		DIR_BUTT.prs_p = flicker;
		DIR_BUTT.text = "DIRECTIONS";
	break;

	case 32:
		ZOOM_BUTT.top = PT;
		ZOOM_BUTT.bottom = PB;
		ZOOM_BUTT.left = PL;
		ZOOM_BUTT.right = PR;
		ZOOM_BUTT.p = do_zoom;
		ZOOM_BUTT.prs_p = toggle;
		ZOOM_BUTT.text = "ZOOM";
	break;

	case 33:
		ABOUT_BUTT.top = AT;
		ABOUT_BUTT.bottom = AB;
		ABOUT_BUTT.left = AL;
		ABOUT_BUTT.right = AR;
		ABOUT_BUTT.p = do_about;
		ABOUT_BUTT.prs_p = flicker;
		ABOUT_BUTT.text = "ABOUT";
	break;

	case 34:
		POP_BUTT.top = POPT;
		POP_BUTT.bottom = POPB;
		POP_BUTT.left = POPL;
		POP_BUTT.right = POPR;
		POP_BUTT.p = do_pop;
		POP_BUTT.prs_p = toggle;
		POP_BUTT.text = "SEARCH";
	break;

	case 35:
		WEST_BUTT.top = WT;
		WEST_BUTT.bottom = WB;
		WEST_BUTT.left = WL;
		WEST_BUTT.right = WR;
		WEST_BUTT.p = do_west;
		WEST_BUTT.prs_p = flicker;
		WEST_BUTT.dir = LEFT;
	break;

	case 36:
		EAST_BUTT.top = ET;
		EAST_BUTT.bottom = EB;
		EAST_BUTT.left = EL;
		EAST_BUTT.right = ER;
		EAST_BUTT.p = do_east;
		EAST_BUTT.prs_p = flicker;
		EAST_BUTT.dir = RIGHT;
	break;

	case 37:
		NORTH_BUTT.top = NT;
		NORTH_BUTT.bottom = NB;
		NORTH_BUTT.left = NL;
		NORTH_BUTT.right = NR;
		NORTH_BUTT.p = do_north;
		NORTH_BUTT.kb_p = do_sel;
		NORTH_BUTT.prs_p = flicker;
		NORTH_BUTT.dir = UP;
	break;

	case 38:
		SOUTH_BUTT.top = ST;
		SOUTH_BUTT.bottom = SB;
		SOUTH_BUTT.left = SL;
		SOUTH_BUTT.right = SR;
		SOUTH_BUTT.p = do_south;
		SOUTH_BUTT.kb_p = do_sel;
		SOUTH_BUTT.prs_p = flicker;
		SOUTH_BUTT.dir = DOWN;
	break;

	case 39:
		ROAD_BUTT.top = RT;
		ROAD_BUTT.bottom = RB;
		ROAD_BUTT.left = RL;
		ROAD_BUTT.right = RR;
		ROAD_BUTT.p = do_nothing;
		ROAD_BUTT.prs_p = toggle;
		ROAD_BUTT.text = "ROADS";
	break;

	default:
		return;
	break;
	}
}

void init_keyboard(){
	keyboard = malloc(sizeof(Button)*N_KEYS);

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
	free(keyboard);
}

 // Returns true if the point is inside the button
int falls_inside(Point p, Button b){
	return(falls_between(p.x, b.left, b.right) &&
		   falls_between(p.y, b.top, b.bottom));
}

// Returns the screen button that was pressed and NULL if no valid button was pressed
Button* get_s_button(Point p){
	for(int i = KB_KEYS; i < N_KEYS; i++){
		if(falls_inside(p, keyboard[i])){
			Point p_f = GetRelease();
			printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

			if(falls_inside(p_f, keyboard[i])){
				return &keyboard[i];
			}
			else {
				printf("Invalid button\n");
				return NULL;
			}
		}
	}

	printf("Invalid button\n");
	return NULL;
}

/* Returns the keyboard button that was pressed and NULL if no valid button was pressed
 * North/south buttons used during search mode to select search matching
 * Road button always active
 */
Button* get_kb_button(Point p){
	for(int i = 0; i < KB_KEYS; i++){
		if(falls_inside(p, keyboard[i])){
			Point p_f = GetRelease();
			printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

			if(falls_inside(p_f, keyboard[i])){
				return &keyboard[i];
			}
			else {
				printf("Invalid button\n");
				return NULL;
			}
		}
	}

	if(falls_inside(p, NORTH_BUTT)){
		Point p_f = GetRelease();
		printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

		if(falls_inside(p_f, NORTH_BUTT)){
			return &NORTH_BUTT;
		}
		else{
			printf("Invalid button\n");
			return NULL;
		}
	}
	else if(falls_inside(p, SOUTH_BUTT)){
		Point p_f = GetRelease();
		printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

		if(falls_inside(p_f, SOUTH_BUTT)){
			return &SOUTH_BUTT;
		}
		else{
			printf("Invalid button\n");
			return NULL;
		}
	}
	else if(falls_inside(p, ROAD_BUTT)){
		Point p_f = GetRelease();
		printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

		if(falls_inside(p_f, ROAD_BUTT)){
			return &ROAD_BUTT;
		}
		else{
			printf("Invalid button\n");
			return NULL;
		}
	}

	printf("Invalid button\n");
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
//	directions_screen();
//	int start_node = get_node(graph);
	int curr_lat, curr_long;
	switch (button_iteration){
		case 0:
			get_current_coordinates(&curr_lat, &curr_long);
			break;
		case 1:
			curr_lat = 2504654;
			curr_long = 2656412;
			break;
		case 2:
			curr_lat = 2565916;
			curr_long = 2676995;
			break;
		case 3:
			curr_lat = 2453370;
			curr_long = 2645000;
			break;
	}

	int start_node = find_vertex_by_coords(full_map_graph, curr_long, curr_lat)->id;
	draw_information_box("PLEASE SELECT DESTINATION");
	int end_node = find_vertex_by_coords(full_map_graph, 2616925, 2533514)->id;//get_node(graph); //Actually use get_node when we are implementing this on touchscreen
	path_points* path = get_path_points(full_map_graph, start_node, end_node, false); //ROAD_TOG); //replace with ROAD_TOG once it gets merged in
	draw_path(path->ordered_point_arr, path->actual_size, BLUE);
	destroy_path_points(path);
	draw_information_box("HAVE A FUN TRIP!");
}

//Toggle between zoom in and zoom out
void do_zoom(){
	Point sel = {0,0};
	if (zoom_level == ZOOM_IN){
		zoom_level = ZOOM_OUT;
	}
	else {
		zoom_level = ZOOM_IN;

		do{
			sel = GetPress();
		//} while(sel.y > image_height[ZOOM_OUT] || sel.x > image_width[ZOOM_OUT]);
		} while(sel.y > image_height[ZOOM_OUT] || sel.x > 500); //temporary, until we shift boundary to 600

		//printf("sel pre convert %d, %d\n", sel.x, sel.y);
		sel = convert_pnt_to_zoom_in(sel);
		//printf("sel post convert %d, %d\n", sel.x, sel.y);

		//we pass draw_image in the top left corner, sel should be the centre of the image
		sel.x -= DISPLAY_WIDTH/2;
		sel.y -= DISPLAY_HEIGHT/2;

		if(sel.x < DISPLAY_WIDTH/2)
			sel.x = DISPLAY_WIDTH/2;
		// else if(sel.x > image_width[ZOOM_OUT] - (DISPLAY_WIDTH/2))
		else if(sel.x > (500 - DISPLAY_WIDTH/2)) //temporary, until we shift boundary to 600
			sel.x = image_width[ZOOM_OUT]  - (DISPLAY_WIDTH/2);

		if(sel.y < DISPLAY_HEIGHT/2)
			sel.y = DISPLAY_HEIGHT/2;
		else if(sel.y > (image_height[ZOOM_OUT] - DISPLAY_HEIGHT/2))
			sel.y = image_height[ZOOM_OUT] - (DISPLAY_HEIGHT/2);


	}
	printf("sel final %d, %d\n", sel.x, sel.y);
	curr_image_pos = sel;
	draw_full_image();
}

// Display app about
void do_about(void* nothing){
	about_screen();
}

// Translate the map left
void do_west(){
	if (zoom_level == ZOOM_IN){
		move_img (LEFT);
	}
}

// Translate the map east
void do_east(){
	if (zoom_level == ZOOM_IN){
		move_img (RIGHT);
	}
}

// Translate the map north
void do_north(){
	if (zoom_level == ZOOM_IN){
		move_img (UP);
	}
}

// Translate the map south
void do_south(){
	if (zoom_level == ZOOM_IN){
		move_img (DOWN);
	}
}

void do_sel(char key){
	if (key == NORTH_BUTT.key){
		do_up();
	}
	else if(key == SOUTH_BUTT.key){
		do_down();
	}
}

// Select the search match entry above the current selected
void do_up(){
	if(MN_COUNT < SEARCH_THRESHHOLD)
		return;
	if(sel > 1)
		sel--;
	else
		sel = MN_COUNT;
	match_screen(sel, MN_COUNT);
}

// Select the search match entry below the current selected
void do_down(){
	if(MN_COUNT < SEARCH_THRESHHOLD)
		return;
	if(sel < MN_COUNT)
		sel++;
	else
		sel = 1;
	match_screen(sel, MN_COUNT);
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

	/* Ignore the matcher if the string query length is below the threshhold to provide matchings
	   Update and delete matches when we add letters */
	if(qs_length() < SEARCH_THRESHHOLD){
		draw_information_box("ENTER YOUR SEARCH!");
	}
	if(qs_length() > SEARCH_THRESHHOLD){
		del_matches();
	}
	if(qs_length() == SEARCH_THRESHHOLD){
		add_matches();
	}
}

// Deletes the front of the search bar and updates the search matcher
void do_del(){
	del_letter();

	/* Ignore the matcher if the string query is below the threshhold
	   Update and add matches when we delete letters  */
	if(qs_length() < SEARCH_THRESHHOLD){
		draw_information_box("ENTER YOUR SEARCH!");
	}
	if(qs_length() >= SEARCH_THRESHHOLD){
		add_matches();
	}
}

/* On valid search, find the path to the selected entry from current location. Re-draw the map.
	On invalid search, returns and keep listening for keyboard inputs */
bool do_enter(){
	bool retval = false;
	if(ready()){
		name_list* nl = matched_names.head;
		for(int i = 0; i < sel; i++){
			nl = nl->next;
		}
		char* name = nl->name;
		//TODO  Now do something using the name of the selected search entry
		do_back();
	}
	return retval;
}

// Leave search mode and redraw the map
void do_back(){
	reset_query();
	destroy_matches();

	init_screen(); //TODO replace this
	//map_screen();
}

void toggle(Button b){
	if(*b.pressed == false){
		*b.pressed = true;
		highlight(b);
		usleep(TOGGLE_DELAY);
	}
	else{
		*b.pressed = false;
		unhighlight(b);
		usleep(TOGGLE_DELAY);
	}
}

void flicker(Button b){
	highlight(b);
	usleep(FLICKER_DELAY);
	unhighlight(b);
}

bool is_kb_butt(Button b){
	return(b.id < KB_KEYS);
}

// Pre: b is a keyboard button
bool is_big_kb(Button b){
	return(b.id == ENTER_BUTT.id || b.id == SPACE_BUTT.id || b.id == BACK_BUTT.id);
}

bool is_arrow_butt(Button b){
	return(b.id >= WEST_BUTT.id && b.id <= SOUTH_BUTT.id);
}

bool is_screen_butt(Button b){
	return(!is_kb_butt(b) && !is_arrow_butt(b));
}

// Pre: b has a direction
int get_arrow_dir(Button b){
	return b.dir;
}

// Pre: b has text
char* get_butt_text(Button b){
	return b.text;
}

void do_nothing(){
}
