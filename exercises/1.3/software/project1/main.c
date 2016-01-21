#include <stdio.h>
#include "rs232.h"
#include "Bresenhams_Line_Drawing_Algorithm.h"

int main(void) {
	printf("start");
	clear_screen(CYAN);
	printf("done clear");
	Line(100, 200, 300, 100, RED); //void Line(int x1, int y1, int x2, int y2, int Colour);
	HLine(100, 100, 300, BLUE); //HLine(int x1, int y1, int length, int Colour)
	printf("done all");
	return 0;
}
