#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "misc_helpers.h"
#include "button.h"
#include "menu.h"
#include "touchscreen.h"

const char KEYS[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '-',
			  	  	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '+',
			  	  	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', '<',
			  	  	'!', '@', '#', '$', '%',
			  	  	'a', 'd', 'w', 's'};

Button init_button(char key, int id, int mode){
	Button button;

	button.key = key;
	button.id = id;
	button.mode = mode;

	if(!mode){
		/*TODO: set coords after choosing where to draw shit; decide what the fcn to call for kb buttons
				We can use the id to know where to draw.
				Use the key to initialise the fcn ptr is. */
		//TODO: make the fcn ptr.
		button.left = 0;
		button.right = 0;
		button.top = 0;
		button.bottom = 0;
		//button.p = do_key;
	}
	return button;
}

void init_keyboard(){
	Button* keyboard = malloc(sizeof(Button)*N_KEYS);

	// KB buttons
	for(int i = 0; i < KB_KEYS; i++){
		keyboard[i] = init_button(KEYS[i], i, !ACTIVE);
	}

	// Screen buttons
	for(int i = KB_KEYS; i < N_KEYS - 1; i++){
		keyboard[i] = init_button(KEYS[i], i, ACTIVE);
	}

//	// Invalid button
//	keyboard[N_KEYS-1] = init_button(KEYS[N_KEYS-1], (N_KEYS-1), 0);

	// TODO: make the ptr fcns
	// Fix screen buttons
	//INFO_BUTT.p = &do_info;
	INFO_BUTT.top = IT;
	INFO_BUTT.bottom = IB;
	INFO_BUTT.left = IL;
	INFO_BUTT.right = IR;

	//DIR_BUTT.p = do_dir();
	DIR_BUTT.top = DT;
	DIR_BUTT.bottom = DB;
	DIR_BUTT.left = DL;
	DIR_BUTT.right = DR;

	//PHOTO_BUTT.p = &do_photo;
	PHOTO_BUTT.top = PT;
	PHOTO_BUTT.bottom = PB;
	PHOTO_BUTT.left = PL;
	PHOTO_BUTT.right = PR;

	//ABOUT_BUTT.p = &do_about;
	ABOUT_BUTT.top = AT;
	ABOUT_BUTT.bottom = AB;
	ABOUT_BUTT.left = AL;
	ABOUT_BUTT.right = AR;

	//POP_BUTT.p = &do_pop;
	POP_BUTT.top = ST;
	POP_BUTT.bottom = SB;
	POP_BUTT.left = SL;
	POP_BUTT.right = SR;
}

void destroy_keyboard(Button* keyboard){
//	for(int i = 0; i < N_KEYS; i++){
//		free(keyboard[i]);
//	}
	free(keyboard);
}

// Activates pop up keyboard
void pop_up(Button* keyboard){
	for(int i = 0; i < KB_KEYS; i++){
		keyboard[i].mode = ACTIVE;
	}
}

// Deactivates pop up keyboard
void pop_down(Button* keyboard){
	for(int i = 0; i < KB_KEYS; i++){
		keyboard[i].mode = !ACTIVE;
	}
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

// Pop up the keyboard
void do_pop(void* nothing){
	pop_up(keyboard);
	pop_screen();
	// TODO: wait until a search query is entered and then do some stuff before pop_down();
	//pop_down();
	//re-draw the map
}

//void do_key(void* key){
//	// TODO: special cases of KB buttons
//
//	// delete
//	if(key == '-'){
//		// delete the letter in the front and go back to the position of that letter
//	}
//	// enter
//	else if(key == '+'){
//		// returns the search input; inform the user of an invalid input and request them to try again
//	}
//	// back
//	else if(key == '<'){
//		// pop down the keyboard and redraw the map; reusable in do_pop so write a fcn to do this
//	}
//	else{
//		// find out where to draw next key and then draw it.
//	}
//}
