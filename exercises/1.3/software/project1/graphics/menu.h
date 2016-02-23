#ifndef MENU_H_
#define MENU_H_

#include "graphics.h"
#include "Directions.h"
#include "button.h"

//button coords
//info
#define IL 500
#define IR 650
#define IT 380
#define IB 430
//direction
#define DL 650
#define DR 800
#define DT 380
#define DB 430
//zoom
#define PL 500
#define PR 650
#define PT 430
#define PB 480
//about
#define AL 650
#define AR 800
#define AT 430
#define AB 480
//west
#define WL 550
#define WR 600
#define WT 240
#define WB 290
//pop
#define POPL 500
#define POPR 650
#define POPT 330
#define POPB 380
//east
#define EL 700
#define ER 750
#define ET 240
#define EB 290
//north
#define NL 625
#define NR 675
#define NT 210
#define NB 260
//south
#define SL 625
#define SR 675
#define ST 270
#define SB 320
//road
#define RL 650
#define RR 800
#define RT 330
#define RB 380

#define BUTT_SIZE 40
#define ARROW_SIZE 50
#define ARR_BUTT_HEIGHT 130
#define SBUTT_WIDTH 150
#define SBUTT_HEIGHT 50
#define BOX_WIDTH 300
#define BOX_HEIGHT 200
#define MAP_WIDTH 500
#define KB_HEIGHT 180
#define SEARCH_HEIGHT 70
#define ORIGIN 0

void draw_keyboard(Point leftCorner, int size);

void draw_button(Point topLeft, int width, int height, int borderWidth,
		int borderColour, int fillColour, int textColour, char* text, FontSize fontSize);
void draw_menu(Point leftCorner, int width, int height, int borderWidth,
		int borderColour, int fillColour, int textColour, FontSize fontSize, char* menuText[]);
void draw_text_box(Point topLeft, int width, int height, int borderWidth,
		int borderColour, int fillColour, int textColour, char* text, FontSize fontSize);
void draw_information_box(char* text);
void draw_arrow(Point topLeft, int width, int height, int borderWidth,
		int borderColour, int fillColour, Direction direction, int invert);
void draw_arrows();

void about_screen();
void info_screen();
void directions_screen();
void zoom_screen();
void init_screen();
void pop_screen();
void match_screen(int sel, int mn_count);
//TODO: need fcn to redraw the map after finished with keyboard
void map_screen();
void highlight(Button b);
void unhighlight(Button b);

#endif /* MENU_H_ */
