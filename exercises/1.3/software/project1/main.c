#include <stdio.h>
#include <stdlib.h>
#include "Bresenhams_Line_Drawing_Algorithm.h"

int main(void) {

	//Init_Touch();

	printf("start");
	//void WriteAPixel(int x, int y, int Colour);
	//WriteAPixel(10, 10, YELLOW);
	//while(1){
	clear_screen(CYAN);
	//clear_screen(YELLOW);
	//}

	//Line(100, 100, 300, 100, CYAN); //void Line(int x1, int y1, int x2, int y2, int Colour);
	//HLine(100, 101, 200, BLACK); //HLine(int x1, int y1, int length, int Colour)
//void VLine(int x1, int y1, int length, int Colour)
	/*
	for (int i = 0; i<=800; i++){
		HLine(0, i, 1000, YELLOW);
	}
	*/
	 for (int i = 0; i<=800; i++){
		VLine(i, 0, 600, RED);
	}

	//}
	//printf("done all");
	return 0;
}
