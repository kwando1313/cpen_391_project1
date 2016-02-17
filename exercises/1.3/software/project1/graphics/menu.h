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

#define WL 550
#define WR 600
#define WT 240
#define WB 290

#define EL 700
#define ER 750
#define ET 240
#define EB 290

#define NL 625
#define NR 675
#define NT 210
#define NB 260

#define SL 625
#define SR 675
#define ST 270
#define SB 320

//TODO do we need these?
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

void draw_image(Point topLeft, short file);//, int bmpWidth, int bmpHeight);
void load_image(Point bottomLeft, char* filename);//, int bmpWidth, int bmpHeight);

void load_image(Point bottomLeft, char* filename);//, char* filename, int bmpheight, int bmpwidth);
void draw_keyboard(Point leftCorner, int size);

void get_header (short file);
void get_pixels (short file);
void draw_img (Point topLeft, short file, int xstart, int ystart);

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
//TODO: need fcn to redraw the map after finished with keyboard
void map_screen();

#endif /* MENU_H_ */
