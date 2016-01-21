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
#define	RED			2
#define	LIME			3
#define	BLUE			4
#define	YELLOW			5
#define	CYAN			6
#define	MAGENTA			7

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

/*********************************************************************************************
This function draw a horizontal line, 1 pixel at a time starting at the x,y coords specified
*********************************************************************************************/

void HLine(int x1, int y1, int length, int Colour);

/*********************************************************************************************
This function draw a vertical line, 1 pixel at a time starting at the x,y coords specified
*********************************************************************************************/

void VLine(int x1, int y1, int length, int Colour);

/*******************************************************************************
** Implementation of Bresenhams line drawing algorithm
*******************************************************************************/


// Implementation of Bresenhams line drawing algorithm
void Line(int x1, int y1, int x2, int y2, int Colour);

void clear_screen(colour);


#endif /* BRESENHAMS_LINE_DRAWING_ALGORITHM_H_ */
