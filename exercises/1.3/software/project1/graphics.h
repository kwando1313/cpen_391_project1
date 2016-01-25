#ifndef BRESENHAMS_LINE_DRAWING_ALGORITHM_H_
#define BRESENHAMS_LINE_DRAWING_ALGORITHM_H_

// defined constants representing colours pre-programmed into colour palette
// there are 256 colours but only 8 are shown below, we write these to the colour registers
//
// the header files "Colours.h" contains constants for all 256 colours
// while the course file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into the palette
#define	BLACK			0
#define	WHITE			1
#define	RED				2
#define	LIME			3
#define	BLUE			4
#define	YELLOW			5
#define	CYAN			6
#define	MAGENTA			7

// should redo these for the touchscreen -> these numbers are for the lab's monitors
#define MAX_X 800
#define MAX_Y 479

typedef struct{
	int x;
	int y;
} Point;

//TODO: input validation
// rectangle, triangles
// rest will be drawshape
// circles
void draw_rectangle(Point topLeft, Point topRight, Point botLeft, Point botRight, int colour);
void draw_filled_rectangle(Point topLeft, Point topRight, Point botLeft, Point botRight, int colour);
void draw_filled_rectangle_border(Point topLeft, Point topRight, Point botLeft, Point botRight,
		int colour, int borderColour, int borderWidth);
void draw_triangle(Point a, Point b, Point c, int colour);
void draw_filled_triangle(Point a, Point b, Point c, int colour);
void draw_filled_triangle_border(Point a, Point b, Point c, int colour, int borderColour, int borderWidth);

/*
 *
 * Build a small library of functions to draw things line 'rectangles,' 'filled rectangles', 'filled
rectangles with a border', 'triangles' etc. There is also a 'circle' and 'arc' drawing algorithm
that Bresenham came up with, see if you can dig that out on the web and implement it.
(Check out http://en.wikipedia.org/wiki/Midpoint_circle_algorithm ). The circle algorithm is
based on drawing a set of 8 x 45 degree arcs in opposite quadrants and is pretty easy to
implement so why not add 'arc' and 'circle' drawing functions to your library.
 *
 *
 *
 *
 */






/*******************************************************************************************
* This function writes a single pixel to the x,y coords specified using the specified colour
* Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
********************************************************************************************/
void WriteAPixel(int x, int y, int Colour);

/*********************************************************************************************
* This function read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/
int ReadAPixel(int x, int y);

/**********************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
**
************************************************************************************/
void ProgramPalette(int PaletteNumber, int RGB);

void HLine(int x1, int y1, int length, int Colour);
void VLine(int x1, int y1, int length, int Colour);

void Line(int x1, int y1, int x2, int y2, int Colour);
void LineSW(int x1, int y1, int x2, int y2, int Colour);

void clear_screen(int colour);
void clear_screenSW(int colour);

void rand_lines_test(int num);

#endif /* BRESENHAMS_LINE_DRAWING_ALGORITHM_H_ */
