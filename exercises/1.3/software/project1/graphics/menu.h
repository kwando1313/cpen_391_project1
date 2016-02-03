#ifndef MENU_H_
#define MENU_H_

#include "graphics.h"

void draw_button(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize);
void draw_menu(Point leftCorner, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, int fontSize, char* menuText[]);
void draw_text_box(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize);
void draw_information_box(char* text);
void draw_arrow(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int direction);
void draw_arrows();
void about_screen();
void info_screen();
void directions_screen();
void photo_screen();
void init_screen();

#endif /* MENU_H_ */
