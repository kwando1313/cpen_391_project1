#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "misc_helpers.h"
#include "button.h"

//TODO
init_button(char key, int id){

}

void init_keyboard(){
	keyboard = malloc(sizeof(Button)*N_KEYS);

	for(int i = 0; i < N_KEYS; i++){
		keyboard[i] = init_button(KEYS(i), i);
	}
}

void destroy_keyboard(){
	for(int i = 0; i < N_KEYS; i++){
		free(keyboard[i]);
	}

	free(keyboard);
}

// Activates pop up keyboard
void pop_up(){
	for(int i = 0; i < KB_KEYS; i++){
		keyboard[i].mode = 1;
	}
}

// Deactivates pop up keyboard
void pop_down(){
	for(int i = 0; i < KB_KEYS; i++){
		keyboard[i].mode = 0;
	}
}

/* Assumption: all of our buttons are rectangles. Aside: nodes aren't buttons but they are circles right now.
 * Returns true if the point is inside the button
 */
int falls_inside(Point p, Button b){
	return(falls_between(p.x, b.left, b.right) &&
		   falls_between(p.y, b.top, b.bottom));
}

// TODO
kb_button(){

}

// TODO: Move code from control
screen_button(){

}

// Returns the button that was pressed and 0 if invalid press. Do we want better search despite fixed small keyboard?
struct Button get_button(Point p){
	for(int i = 0; i < N_KEYS; i++){
		if(falls_inside(p, keyboard[i]))
			return keyboard[i];
	}

	// invalid press
	return 0;
}

