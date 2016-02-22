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
    void (*p)();
    bool (*ent_p)();
    void (*kb_p)(char key); // what each button does
} Button ;

Button* keyboard;

// screen buttons
#define DEL_BUTT keyboard[10]
#define ENTER_BUTT keyboard[20]
#define SPACE_BUTT keyboard[28]
#define BACK_BUTT keyboard[29]
#define INFO_BUTT keyboard[30]
#define DIR_BUTT keyboard[31]
#define ZOOM_BUTT keyboard[32]
#define ABOUT_BUTT keyboard[33]
#define POP_BUTT keyboard[34]
#define WEST_BUTT keyboard[35]
#define EAST_BUTT keyboard[36]
#define NORTH_BUTT keyboard[37]
#define SOUTH_BUTT keyboard[38]

// keyboard variables
#define N_KEYS 39
#define KB_KEYS 30

// initialise keyboard
void init_kb_button(char key, int id);
void init_s_button(char key, int id);
void init_keyboard();
//void destroy_keyboard();


// Gets the button upon input for control
int falls_inside(Point p, Button b);
Button* get_s_button(Point p);
Button* get_kb_button(Point p);

// ptr fcns
void do_key(char key);
void do_del();
void do_back();
bool do_enter();
void do_info();
void do_dir();
void do_zoom();
void do_about();
void do_pop();
void do_west();
void do_east();
void do_north();
void do_up(char key);
void do_south();
void do_down(char key);


#endif /* BUTTON_H_ */
