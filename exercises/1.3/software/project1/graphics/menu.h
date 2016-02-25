#ifndef MENU_H_
#define MENU_H_

#include "graphics.h"
#include "Directions.h"
#include "button.h"

//button coords
//info
#define IL 600
#define IR 700
#define IT 380
#define IB 430
//direction
#define DL 700
#define DR 800
#define DT 380
#define DB 430
//zoom
#define PL 600
#define PR 700
#define PT 430
#define PB 480
//about
#define AL 700
#define AR 800
#define AT 430
#define AB 480
//pop
#define POPL 600
#define POPR 700
#define POPT 330
#define POPB 380
//road
#define RL 700
#define RR 800
#define RT 330
#define RB 380
//west
#define WL 615
#define WR 665
#define WT 240
#define WB 290
//east
#define EL 735
#define ER 785
#define ET 240
#define EB 290
//north
#define NL 675
#define NR 725
#define NT 210
#define NB 260
//south
#define SL 675
#define SR 725
#define ST 270
#define SB 320

#define ORIGIN 0
#define KEY_SIZE 50
#define ARROW_SIZE 50
#define ARR_BUTT_HEIGHT 130
#define SBUTT_WIDTH 100
#define SBUTT_HEIGHT 50
#define BOX_WIDTH 200
#define BOX_HEIGHT 200
#define MAP_WIDTH 600
#define SEARCH_TOP 200
#define SEARCH_HEIGHT 80
#define KB_LEFT 25
#define KB_TOP 305
#define BORD_TOP 280
#define BORD_HEIGHT 200

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
void info_screen(char* info);
void zoom_screen();
void init_screen();
void pop_screen();
void match_screen(int sel, int mn_count);
//TODO: need fcn to redraw the map after finished with keyboard
void map_screen();
void highlight(Button b);
void unhighlight(Button b);

#endif /* MENU_H_ */
