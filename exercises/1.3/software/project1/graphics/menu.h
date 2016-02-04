#ifndef MENU_H_
#define MENU_H_

#include "graphics.h"
#include "alt_up_"

#define IL 500
#define IR 650
#define IU 330
#define ID 405

#define DL 650
#define DR 800
#define DU 330
#define DD 405

#define PL 500
#define PR 650
#define PU 405
#define PD 480

#define AL 650
#define AR 800
#define AU 405
#define AD 480

void load_image(Point bottomLeft, char* filename);//, int bmpheight, int bmpwidth);

void draw_button(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize);
void draw_menu(Point leftCorner, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, int fontSize, char* menuText[]);
void draw_text_box(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize);
void draw_information_box(char* text);
void about_screen();
void info_screen();
void directions_screen();
void photo_screen();
void init_screen();
#endif /* MENU_H_ */
