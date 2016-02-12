#ifndef BUTTON_H_
#define BUTTON_H_

#include "misc_helpers.h"
#include <string.h>

// screen buttons
#define INFO_BUTT keyboard[29]
#define DIR_BUTT keyboard [30]
#define PHOTO_BUTT keyboard [31]
#define ABOUT_BUTT keyboard [32]
#define POP_BUTT keyboard [33]
#define INVALID_BUTT keyboard [34]

// keyboard variables
#define N_KEYS 34
#define KB_KEYS 28
#define S_KEYS 6
#define ACTIVE 1

const char KEYS[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
			  	  	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '<',
			  	  	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ',
			  	  	'@', '^', '$', '#', '_', '!'};

Button keyboard[];

typedef struct Button {
    int left;
    int right;
    int top;
    int bottom;
    char key;
    int id;
    int mode; // 0 or 1 for pop up keyboard; 1 is active
    int (*p)(); // what each button does
} Button ;

void init_button(char key, int id, int mode);

// Button availability will be fixed dependent on mode. Unless we don't implement popup keyboard like I assumed.
void init_keyboard();
void destroy_keyboard();

// Sets pop up keyboard keys
void pop_up();
void pop_down();

// Gets the button upon input for control
int falls_inside(Point p, Button b);
Button get_button(Point p);

#endif /* BUTTON_H_ */
