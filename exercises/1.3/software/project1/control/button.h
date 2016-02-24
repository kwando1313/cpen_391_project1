#ifndef BUTTON_H_
#define BUTTON_H_

#include "misc_helpers.h"
#include <string.h>
#include "graph.h"

#define FLICKER_DELAY 100000
#define TOGGLE_DELAY 10000

typedef struct Button{
	bool* pressed;
    int left;
    int right;
    int top;
    int bottom;
    char key;
    int id;
    int dir;
    char* text;
    // Button fcns
    void (*p)();
    void (*prs_p)(struct Button b);
    bool (*ent_p)();
    void (*kb_p)(char key);
} Button;

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
#define ROAD_BUTT keyboard[39]

// keyboard variables
#define N_KEYS 40
#define KB_KEYS 30

// initialise keyboard
void init_kb_button(char key, int id);
void init_s_button(char key, int id);
void init_keyboard();
void destroy_keyboard();

// Gets the button upon input for control
int falls_inside(Point p, Button b);
Button* get_s_button(Point p);
Button* get_kb_button(Point p);

bool is_kb_butt(Button b);
bool is_big_kb(Button b);
bool is_arrow_butt(Button b);
bool is_screen_butt(Button b);
int get_arrow_dir(Button b);
char* get_butt_text(Button b);

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
void do_sel(char key);
void do_west();
void do_east();
void do_north();
void do_up();
void do_south();
void do_down();
void flicker(Button b);
void toggle(Button b);
void do_nothing();
bool road_mode();

bool road_only;

//helper function
int get_start_node();

#endif /* BUTTON_H_ */
