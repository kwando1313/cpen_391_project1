#ifndef BUTTON_H_
#define BUTTON_H_

#include "misc_helpers.h"
#include <string.h>

//I don't think the keyboard should be dynamic.
const char KEYS[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
			  	  	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '<',
			  	  	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', '@', '^', '$', '#'};

#define N_KEYS 33
#define KB_KEYS 28
#define S_KEYS 5

Button keyboard[];

typedef struct Button {
    int left; //these boundaries should be defined
    int right;
    int top;
    int bottom;
    char key;
    int id;
    int mode; // 0 or 1 for pop up keyboard
    int (*p)(); // either kb or screen button
} Button ;

void init_button(char key, int id);

// Button availability will be fixed dependent on mode. Unless we don't implement popup keyboard like I assumed.
void init_keyboard();
void destroy_keyboard();

// Sets pop up keyboard keys
void pop_up();
void pop_down();

// Gets the button upon input for control
int falls_inside(Point p, Button b);
Button get_button(Point p);

// ptr fcns
kb_button();
screen_button();


#endif /* BUTTON_H_ */
