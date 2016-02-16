#ifndef BUTTON_H_
#define BUTTON_H_

#include "misc_helpers.h"
#include <string.h>
#include "graph.h"

typedef struct Button {
    int left;
    int right;
    int top;
    int bottom;
    char key;
    int id;
    int mode; // 0 or 1 for pop up keyboard; 1 is active
    int (*p)(void *); // what each button does
} Button ;

Button* keyboard;

// screen buttons
#define DEL_BUTT keyboard[10]
#define ENTER_BUTT keyboard[20]
#define BACK_BUTTON keyboard[29]
#define INFO_BUTT keyboard[30]
#define DIR_BUTT keyboard[31]
#define PHOTO_BUTT keyboard[32]
#define ABOUT_BUTT keyboard[33]
#define POP_BUTT keyboard[34]
#define WEST_BUTT keyboard[35]
#define EAST_BUTT keyboard[36]
#define NORTH_BUTT keyboard[37]
#define SOUTH_BUTT keyboard[38]

// keyboard variables
#define N_KEYS 39
#define KB_KEYS 30
#define S_KEYS 9
#define ACTIVE 1

Button init_button(char key, int id, int mode);

// Button availability will be fixed dependent on mode. Unless we don't implement popup keyboard like I assumed.
void init_keyboard();
void destroy_keyboard();

// Sets pop up keyboard keys
void pop_up();
void pop_down();

// Gets the button upon input for control
int falls_inside(Point p, Button b);
Button* get_button(Point p);

// ptr fcns
void do_info(void *);
void do_dir(void *);
void do_photo(void *);
void do_about(void *);
void do_pop(void *);
void do_key(void *);

#endif /* BUTTON_H_ */
