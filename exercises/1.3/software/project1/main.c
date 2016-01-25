#include <stdio.h>
#include <stdlib.h>
#include "Bresenhams_Line_Drawing_Algorithm.h"

int main(void) {
	printf("start");
	int test_colours[] = {BLACK, CYAN, YELLOW, RED, LIME};
	while(1){
		clear_screen(BLACK);
		WriteAPixel(0, 0, RED);
		WriteAPixel(0, MAX_Y, RED);
		WriteAPixel(MAX_X, 0, RED);
		WriteAPixel(MAX_X, MAX_Y, RED);
		Line(1, 1, MAX_X-1, MAX_Y-1, LIME);
		Line(1, MAX_Y-1, MAX_X-1, 1, LIME);
		clear_screenSW(BLACK);
		WriteAPixel(0, 0, RED);
		WriteAPixel(0, MAX_Y, RED);
		WriteAPixel(MAX_X, 0, RED);
		WriteAPixel(MAX_X, MAX_Y, RED);
		LineSW(1, 1, MAX_X-1, MAX_Y-1, LIME);
		LineSW(1, MAX_Y-1, MAX_X-1, 1, LIME);
		clear_screenSW(YELLOW);
	}
	return 0;
}
