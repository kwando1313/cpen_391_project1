#include "misc_helpers.h"
#include "graphics.h"

#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   			(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   			(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   			(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg   			(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg   		(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   	(*(volatile unsigned short int *)(0x84000010))

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
	WAIT_FOR_GRAPHICS;				// is graphics ready for new command

	GraphicsX1Reg = x;				// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;			// set pixel colour
	GraphicsCommandReg = PutAPixel;			// give graphics "write pixel" command
}

/*********************************************************************************************
* This function read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/
int ReadAPixel(int x, int y){
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS;			// is graphics done reading pixel
	return (int)(GraphicsColourReg) ;	// return the palette number (colour)
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

	int x2 = min(x1 + length - 1, MAX_X);

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

	int y2 = min(y1 + length - 1, MAX_Y);

	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawVLine;
}

// fast draw of line from (x1, y1) to (x2, y2)
// assumes x1,y1,x2,y2 fit within screen bounds:
// 0 <= x <= MAX_X, 0 <= y <= MAX_Y
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
	for (int x1 = 0; x1<=MAX_X; x1++){
		for(int y1 = 0; y1 <= MAX_Y ; y1++ ){
			WriteAPixel(x1, y1, colour);
		}
	}
}

//covers screen in "colour"
void clear_screen(int colour){
	for (int x1 = 0; x1<=MAX_X; x1++){
		VLine(x1, 0, MAX_Y+1, colour);
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
void draw_filled_triangle(Point a, Point b, Point c, int colour);
void draw_filled_triangle_border(Point a, Point b, Point c, int colour, int borderColour, int borderWidth);

//draws random lines, prints coords
void rand_lines_test(int num){
	int test_colours[] = {CYAN, YELLOW, RED, LIME};
	clear_screen(BLACK);
	for (int i = 0; i<num; i++) {
		int x1 = rand()%MAX_X;
		int x2 = rand()%MAX_X;
		int y1 = rand()%MAX_Y;
		int y2 = rand()%MAX_Y;
		printf("(%d, %d), (%d, %d)", x1,x2,y1,y2);
		printf("colour = %d\n\n", test_colours[i % 4]);
		Line(x1,y1,x2,y2,test_colours[i%4]);
	}
}
