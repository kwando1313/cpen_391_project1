#include "misc_helpers.h"
#include "graphics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   			(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   			(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   			(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg   			(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg   		(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg (*(volatile unsigned short int *)(0x84000010))

// constants representing values we write to the graphics 'command' register
#define DrawHLine				0x1
#define DrawVLine				0x2
#define DrawLine				0x3
#define	PutAPixel				0xA
#define	GetAPixel				0xB
#define	ProgramPaletteColour 	0x10

// pauses until the graphics chip status register indicates that it is idle
#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

// This function writes a single pixel to the x,y coords specified using the specified colour
// Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
void WriteAPixel(int x, int y, int Colour){
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x;
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = PutAPixel;
}

/*********************************************************************************************
* This function read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/
int ReadAPixel(int x, int y){
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x;
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel;
	WAIT_FOR_GRAPHICS;			// is graphics done reading pixel
	return (int)(GraphicsColourReg) ;
}


/**********************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
************************************************************************************/
void ProgramPalette(int PaletteNumber, int RGB){
    WAIT_FOR_GRAPHICS;
    GraphicsColourReg = PaletteNumber;
    GraphicsX1Reg = RGB >> 16   ;        // program red value in ls.8 bit of X1 reg
    GraphicsY1Reg = RGB ;                // program green and blue into ls 16 bit of Y1 reg
    GraphicsCommandReg = ProgramPaletteColour; // issue command
}

/* Fast draw of horizontal line, will not draw past screen end
 * requires: x1, y1, length >= 0
 */
void HLine(int x1, int y1, int length, int Colour){
	if (length <= 0) {
		return;
	}

	int x2 = min(x1 + length - 1, XRES);

	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x1;
	GraphicsX2Reg = x2;
	GraphicsY1Reg = y1;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawHLine;
}

/* Fast draw of vertical line, will not draw past screen end
 * requires: x1, y1, length >= 0
 */
void VLine(int x1, int y1, int length, int Colour){
	if (length <= 0) {
		return;
	}

	int y2 = min(y1 + length - 1, YRES);

	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawVLine;
}

// fast draw of line from (x1, y1) to (x2, y2)
// assumes x1,y1,x2,y2 fit within screen bounds:
// 0 <= x <= XRES, 0 <= y <= YRES
void Line(int x1, int y1, int x2, int y2, int Colour){
	if (x1 == x2 && y1 == y2) {
		WriteAPixel(x1, y1, Colour);
		return;
	}

	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawLine;
}

//covers screen in "colour"
void clear_screen(int colour){
	for (int x1 = 0; x1<=XRES; x1++){
		VLine(x1, 0, YRES+1, colour);
	}
}

void draw_rectangle(Point topLeft, Point topRight, Point botLeft, Point botRight, int colour){
	int width = topRight.x - topLeft.x + 1;
	int height = botLeft.y - topLeft.y + 1;

	HLine(topLeft.x, topLeft.y, width, colour);
	HLine(botLeft.x, botLeft.y, width, colour);
	VLine(topLeft.x, topLeft.y, height, colour);
	VLine(topRight.x, topRight.y, height, colour);
}

void draw_filled_rectangle(Point topLeft, Point topRight, Point botLeft, Point botRight, int colour){
	int width = topRight.x - topLeft.x + 1;

	for (int y = topLeft.y; y<=botLeft.y; y++){
		HLine(topLeft.x, y, width, colour);
	}
}

void draw_filled_rectangle_border(Point topLeft, Point topRight, Point botLeft, Point botRight,
		int colour, int borderColour, int borderWidth){
	for(int i = 0; i<borderWidth; i++) {
		draw_rectangle(topLeft, topRight, botLeft, botRight, borderColour);
		topLeft.x++;
		topLeft.y++;
		topRight.x--;
		topRight.y++;
		botLeft.x++;
		botLeft.y--;
		botRight.x--;
		botRight.y--;
	}
	draw_filled_rectangle(topLeft, topRight, botLeft, botRight, colour);
}

void draw_triangle(Point a, Point b, Point c, int colour){
	Line(a.x, a.y, b.x, b.y, colour);
	Line(a.x, a.y, c.x, c.y, colour);
	Line(c.x, c.y, b.x, b.y, colour);
}

void draw_filled_triangle(Point a, Point b, Point c, int colour){
	Line(a.x, a.y, b.x, b.y, colour);
	Line(a.x, a.y, c.x, c.y, colour);
	Line(c.x, c.y, b.x, b.y, colour);
	Fill(avg_val(a.x,b.x,c.x), avg_val(a.y,b.y,c.y), colour, colour);
}

void draw_filled_triangle_border(Point a, Point b, Point c, int colour, int borderColour){
	Line(a.x, a.y, b.x, b.y, borderColour);
	Line(a.x, a.y, c.x, c.y, borderColour);
	Line(c.x, c.y, b.x, b.y, borderColour);
	Fill(avg_val(a.x,b.x,c.x), avg_val(a.y,b.y,c.y), colour, borderColour);
}

/* for shapes that don't fit into the other draw functions
 * lines connect points[0] to points[1], points[1] to points[2],
 * ..., points[num_points-1] to points[0]
 * assumes num_points >= 3
 * Note: if you find yourself drawing the same shape over & over with this,
 * we should probably write a new function for that shape in particular
*/
void draw_shape(Point points[], int num_points, int colour){
	draw_path(points, num_points, colour);
	Line(points[0].x, points[0].y, points[num_points-1].x, points[num_points-1].y, colour);
}

void draw_path(Point points[], int num_points, int colour){
	for(int i = 1; i<num_points; i++){
		Line(points[i-1].x, points[i-1].y, points[i].x, points[i].y, colour);
	}
}

// see notes for draw_shape
// let me know if filling doesn't work - it might have problems with weird shapes
void draw_filled_shape(Point points[], int num_points, int colour){
	int xTot = points[0].x;
	int yTot = points[0].y;
	for(int i = 1; i<num_points; i++){
		Line(points[i-1].x, points[i-1].y, points[i].x, points[i].y, colour);
		xTot += points[i].x;
		yTot += points[i].y;
	}
	Line(points[0].x, points[0].y, points[num_points-1].x, points[num_points-1].y, colour);
	Fill(xTot/num_points, yTot/num_points, colour, colour);
}

// see notes for draw_shape
// let me know if filling doesn't work - it might have problems with weird shapes
void draw_filled_shape_border(Point points[], int num_points, int colour, int borderColour){
	int xTot = points[0].x;
	int yTot = points[0].y;
	for(int i = 1; i<num_points; i++){
		Line(points[i-1].x, points[i-1].y, points[i].x, points[i].y, borderColour);
		xTot += points[i].x;
		yTot += points[i].y;
	}
	Line(points[0].x, points[0].y, points[num_points-1].x, points[num_points-1].y, borderColour);
	Fill(xTot/num_points, yTot/num_points, colour, borderColour);
}

void WriteAPixelArcWrapper(int x, int y, int Colour, int min_x, int max_x, int min_y, int max_y){
	if (falls_between(x, min_x, max_x) && falls_between(y, min_y, max_y)) {
		WriteAPixel(x, y, Colour);
	}
}

// total distance between angles must be <= 180. It may occasionally work, but to be safe,
// always call arcs > 180 in two calls, like below:
// draw_arc(point0, 100, BLUE, 0, 180);
// draw_arc(point0, 100, BLUE, 180, 230);
// Let me know if this is slow -> it can probably be vastly improved
void draw_arc(Point centre, int radius, int colour, double angleStart, double angleEnd){
	int x0 = centre.x;
	int y0 = centre.y;
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x;

	int tmp_x_1 = centre.x + radius*cos(convert_to_radians(angleEnd));
	int tmp_x_2 = centre.x + radius*cos(convert_to_radians(angleStart));
	int tmp_y_1 = centre.y + radius*sin(convert_to_radians(angleStart));
	int tmp_y_2 = centre.y + radius*sin(convert_to_radians(angleEnd));

	int min_x = min(tmp_x_1, tmp_x_2);
	int max_x = max(tmp_x_1, tmp_x_2);
	int min_y = min(tmp_y_1, tmp_y_2);
	int max_y = max(tmp_y_1, tmp_y_2);

	//TODO: optimize all of this
	if (falls_between(90, angleStart, angleEnd)) {
		max_y = centre.y + radius;
	}
	if (falls_between(270, angleStart, angleEnd)) {
		min_y = centre.y - radius;
	}

	if (falls_between(180, angleStart, angleEnd)) {
		min_x = centre.x - radius;
	}

	if (falls_between(0, angleStart, angleEnd)) {
		max_x = centre.x + radius;
	}


	while( y <= x ) {
		WriteAPixelArcWrapper( x + x0,  y + y0, colour, min_x, XRES, min_y, YRES);
		WriteAPixelArcWrapper( y + x0,  x + y0, colour, min_x, XRES, min_y, YRES);
		WriteAPixelArcWrapper(-x + x0,  y + y0, colour, min_x, XRES, min_y, YRES);
		WriteAPixelArcWrapper(-y + x0,  x + y0, colour, min_x, XRES, min_y, YRES);
		WriteAPixelArcWrapper(-x + x0, -y + y0, colour, min_x, XRES, min_y, YRES);
		WriteAPixelArcWrapper(-y + x0, -x + y0, colour, min_x, XRES, min_y, YRES);
		WriteAPixelArcWrapper( x + x0, -y + y0, colour, min_x, XRES, min_y, YRES);
		WriteAPixelArcWrapper( y + x0, -x + y0, colour, min_x, XRES, min_y, YRES);
		y++;

		if (decisionOver2<=0) {
		  decisionOver2 += 2 * y + 1;
		}
		else {
		  x--;
		  decisionOver2 += 2 * (y - x) + 1;
		}
	}
}

// stolen from https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void draw_circle(Point centre, int radius, int colour){
	int x0 = centre.x;
	int y0 = centre.y;
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

	while( y <= x ) {
		WriteAPixel( x + x0,  y + y0, colour); // Octant 1
		WriteAPixel( y + x0,  x + y0, colour); // Octant 2
		WriteAPixel(-x + x0,  y + y0, colour); // Octant 4
		WriteAPixel(-y + x0,  x + y0, colour); // Octant 3
		WriteAPixel(-x + x0, -y + y0, colour); // Octant 5
		WriteAPixel(-y + x0, -x + y0, colour); // Octant 6
		WriteAPixel( x + x0, -y + y0, colour); // Octant 7
		WriteAPixel( y + x0, -x + y0, colour); // Octant 8
		y++;

		if (decisionOver2<=0) {
		  decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
		}
		else {
		  x--;
		  decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
		}
	}
}

void draw_filled_circle(Point centre, int radius, int colour){
	draw_circle(centre, radius, colour);
	Fill(centre.x, centre.y, colour, colour);
}

void draw_filled_circle_border(Point centre, int radius, int colour, int borderColour){
	draw_circle(centre, radius, borderColour);
	Fill(centre.x, centre.y, colour, borderColour);
}

// Bresenham's line drawing algorithm, copy and pasted from Connect
// Does not take advantage of HW accelerated graphics
// Only use this method for testing Line()
void LineSW(int x1, int y1, int x2, int y2, int Colour){
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);
    int i, temp, interchange = 0, error ;

    // if x1=x2 and y1=y2 then it is a line of zero length
    if(dx == 0 && dy == 0) {
        return ;
    }

    // must be a complex line so use bresenhams algorithm
    else    {

    	// swap delta x and delta y depending upon slop of line
        if(dy > dx) {
            temp = dx ;
            dx = dy ;
            dy = temp ;
            interchange = 1 ;
        }

        // initialise the error term to compensate for non-zero intercept
        error = (dy << 1) - dx ;    // (2 * dy) - dx

        // main loop
        for(i = 1; i <= dx; i++)    {
            WriteAPixel(x, y, Colour);

            while(error >= 0)   {
                if(interchange == 1)
                    x += s1 ;
                else
                    y += s2 ;

                error -= (dx << 1) ;    // times 2
            }

            if(interchange == 1)
                y += s2 ;
            else
                x += s1 ;

            error += (dy << 1) ;    // times 2
        }
    }
}

// Does not take advantage of HW accelerated graphics
// Only use this for testing
void clear_screenSW(int colour){
	for (int x1 = 0; x1<=XRES; x1++){
		for(int y1 = 0; y1 <= YRES ; y1++ ){
			WriteAPixel(x1, y1, colour);
		}
	}
}

void test_graphics(void){
	clear_screen(WHITE);

	Point h_a = {50, 100};
	Point h_b = {200, 100};
	Point h_c = {50, 450};
	Point h_d = {200, 450};

	Point v_a = {300, 100};
	Point v_b = {450, 100};
	Point v_c = {300, 450};
	Point v_d = {450, 450};

	Point l_a = {550, 100};
	Point l_b = {700, 100};
	Point l_c = {550, 450};
	Point l_d = {700, 450};

	draw_filled_rectangle_border(h_a, h_b, h_c, h_d, WHITE, BLACK, 2);
	draw_filled_rectangle_border(v_a, v_b, v_c, v_d, WHITE, BLACK, 2);
	draw_filled_rectangle_border(l_a, l_b, l_c, l_d, WHITE, BLACK, 2);

	Point tri_a = {150, 20};
	Point tri_b = {250, 40};
	Point tri_c = {200, 80};
	draw_filled_triangle_border(tri_a, tri_b, tri_c, YELLOW, BLUE);

	Point circ0 = {500, 40};
	draw_filled_circle_border(circ0, 40, 23, PURPLE);
	draw_arc(circ0, 40, 25, 0, 120);

	char str0[] = "Horizontal Lines";
	for (int i = 0; i<strlen(str0); i++) {
		int letter = (int)str0[i];
		OutGraphicsCharFont2a(45+i*FONT2_XPIXELS, 80, BLACK, WHITE, letter, 0);
	}

	char str1[] = "Vertical Lines";
	for (int i = 0; i<strlen(str1); i++) {
		int letter = (int)str1[i];
		OutGraphicsCharFont2a(300+i*FONT2_XPIXELS, 80, BLACK, WHITE, letter, 0);
	}

	char str2[] = "Other Lines";
	for (int i = 0; i<strlen(str2); i++) {
		int letter = (int)str2[i];
		OutGraphicsCharFont2a(550+i*FONT2_XPIXELS, 80, BLACK, WHITE, letter, 0);
	}

	int i = 0;
	int colour;
	while(1){
		colour = i % 12;
		switch(i % 3){
			case 0: rand_h_line(52, 199, 102, 448, colour); break;
			case 1:	rand_v_line(302, 449, 102, 449, colour); break;
			case 2: rand_line(552, 699, 102, 448, colour); break;
		}
		i++;
	}
}

void rand_v_line(int min_x, int max_x, int min_y, int max_y, int colour){
	int x = (rand() % (max_x + 1 - min_x)) + min_x;
	int y = (rand() % (max_y + 1 - min_y)) + min_y;
	int height = rand() % (max_y - y + 1);
	VLine(x, y, height, colour);
}

void rand_h_line(int min_x, int max_x, int min_y, int max_y, int colour){
	int x = (rand() % (max_x + 1 - min_x)) + min_x;
	int y = (rand() % (max_y + 1 - min_y)) + min_y;
	int width = rand() % (max_x - x + 1);
	HLine(x, y, width, colour);
}

void rand_line(int min_x, int max_x, int min_y, int max_y, int colour){
	int x1 = (rand() % (max_x + 1 - min_x)) + min_x;
	int y1 = (rand() % (max_y + 1 - min_y)) + min_y;
	int x2 = (rand() % (max_x + 1 - min_x)) + min_x;
	int y2 = (rand() % (max_y + 1 - min_y)) + min_y;
	Line(x1,y1,x2,y2,colour);
}

