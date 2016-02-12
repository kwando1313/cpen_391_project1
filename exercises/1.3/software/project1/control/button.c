#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "misc_helpers.h"
#include "button.h"
#include "menu.h"

init_button(char key, int id, int mode){
	keyboard[id].key = key;
	keyboard[id].id = id;
	keyboard[id].mode = mode;

	if(!mode){
		//TODO: set coords after choosing where to draw shit; decide what the fcn to call for kb buttons
	}
}

void init_keyboard(){
	keyboard = malloc(sizeof(Button)*N_KEYS);

	// KB buttons
	for(int i = 0; i < KB_KEYS; i++){
		init_button(KEYS(i), i, !ACTIVE);
	}

	// Screen buttons
	for(int i = KB_KEYS; i < N_KEYS; i++){
		init_button(KEYS(i), i, ACTIVE);
	}

	INFO_BUTT.p = do_info();
	INFO_BUTT.top = IU;
	INFO_BUTT.bottom = ID;
	INFO_BUTT.left = IL;
	INFO_BUTT.right = IR;

	DIR_BUTT.p = do_dir();
	DIR_BUTT.top = DU;
	DIR_BUTT.bottom = DD;
	DIR_BUTT.left = DL;
	DIR_BUTT.right = DR;

	PHOTO_BUTT.p = do_photo();
	PHOTO_BUTT.top = PU;
	PHOTO_BUTT.bottom = PD;
	PHOTO_BUTT.left = PL;
	PHOTO_BUTT.right = PR;

	ABOUT_BUTT.p = do_about();
	ABOUT_BUTT.top = AU;
	ABOUT_BUTT.bottom = AD;
	ABOUT_BUTT.left = AL;
	ABOUT_BUTT.right = AR;
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
		keyboard[i].mode = ACTIVE;
	}
	// TODO: display the pop up keyboard graphics
}

// Deactivates pop up keyboard
void pop_down(){
	for(int i = 0; i < KB_KEYS; i++){
		keyboard[i].mode = !ACTIVE;
	}
	// TODO: remove the pop up keyboard graphics
}

/* Assumption: all of our buttons are rectangles. Aside: nodes aren't buttons but they are circles right now.
 * Returns true if the point is inside the button
 */
int falls_inside(Point p, Button b){
	return(falls_between(p.x, b.left, b.right) &&
		   falls_between(p.y, b.top, b.bottom));
}

// Returns the button that was pressed. Do we want better search despite fixed small keyboard?
struct Button get_button(Point p){
	for(int i = 0; i < N_KEYS; i++){
		if(falls_inside(p, keyboard[i])){
			Point p_f = GetRelease();
			printf("Released Coordinates: (%i, %i)\n", p_f.x, p_f.y);

			if(falls_inside(p_f, keyboard[i]))
				return keyboard[i];
			else
				return INVALID_BUTT;
		}
	}
	// Return the invalid button
	return INVALID_BUTT;
}

