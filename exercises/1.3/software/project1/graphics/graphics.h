#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Colours.h"
#include "FontSize.h"
#include "misc_helpers.h"

extern const unsigned int ColourPalletteData[256];

#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14				// height of Font2 characters in pixels (no spacing)

#define WHITE 255

// should redo these for the touchscreen -> these numbers are for the lab's monitors
#define XRES 800
#define YRES 479

// "COLOUR" is always a palette number(0-255), NOT a RGB value

//TODO: colour switching to sneakily load pictures OR HW acceleration of shapes

/**************************************** SHAPES *********************************/
// Responsibility of caller to do any sort of input validation
// Draw rectangle, triangle, are slightly faster than draw_shape -> use these if you can
void draw_rectangle(Point topLeft, Point topRight, Point botLeft, Point botRight, int colour);
void draw_filled_rectangle(Point topLeft, Point topRight, Point botLeft, Point botRight, int colour);
void draw_filled_rectangle_border(Point topLeft, Point topRight, Point botLeft, Point botRight,
		int colour, int borderColour, int borderWidth);

void draw_triangle(Point a, Point b, Point c, int colour);
void draw_filled_triangle(Point a, Point b, Point c, int colour);
void draw_filled_triangle_border(Point a, Point b, Point c, int colour, int borderColour);

void draw_shape(Point points[], int num_points, int colour);
void draw_filled_shape(Point points[], int num_points, int colour);
void draw_filled_shape_border(Point points[], int num_points, int colour, int borderColour);

void draw_circle(Point centre, int radius, int colour);
void draw_filled_circle(Point centre, int radius, int colour);
void draw_filled_circle_border(Point centre, int radius, int colour, int borderColour);
void draw_arc(Point centre, int radius, int colour, double angleStart, double angleEnd);

void draw_path(Point points[], int num_points, int colour);

/**************************** Core Functionality *******************************/
void ProgramPalette(int PaletteNumber, int RGB);
void WriteAPixel(int x, int y, int Colour);
int ReadAPixel(int x, int y);
void HLine(int x1, int y1, int length, int Colour);
void VLine(int x1, int y1, int length, int Colour);
void Line(int x1, int y1, int x2, int y2, int Colour);
void clear_screen(int colour);

/************************* Others **************************************/
void Fill(int _x, int _y, int _FillColour, int _BoundaryColour);
void draw_font(int x, int y, int colour, int backgroundcolour, int c, int Erase, FontSize size);
int get_font_width(FontSize size);
int get_font_height(FontSize size);

//useless methods
void LineSW(int x1, int y1, int x2, int y2, int Colour);
void clear_screenSW(int colour);
void test_graphics(void);
void rand_v_line(int min_x, int max_x, int min_y, int max_y, int colour);
void rand_h_line(int min_x, int max_x, int min_y, int max_y, int colour);
void rand_line(int min_x, int max_x, int min_y, int max_y, int colour);

#endif /* GRAPHICS_H_ */
