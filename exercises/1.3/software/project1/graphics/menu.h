#ifndef MENU_H_
#define MENU_H_

#include "graphics.h"


#define IL 500
#define IR 650
#define IT 330
#define IB 405

#define DL 650
#define DR 800
#define DT 330
#define DB 405

#define PL 500
#define PR 650
#define PT 405
#define PB 480

#define AL 650
#define AR 800
#define AT 405
#define AB 480

#define SL 500
#define SR 800
#define ST 255
#define SB 330

void load_image(Point bottomLeft, char* filename);//, char* filename, int bmpheight, int bmpwidth);

void draw_button(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize);
void draw_menu(Point leftCorner, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, int fontSize, char* menuText[]);
void draw_text_box(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize);
void draw_information_box(char* text);

void about_screen();
void info_screen();
void directions_screen();
void photo_screen();
void init_screen();
void pop_screen();
#endif /* MENU_H_ */
