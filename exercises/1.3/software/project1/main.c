#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

int main(void) {
	printf("start\n");
	int test_colours[] = {BLACK, CYAN, YELLOW, RED, LIME};

	clear_screen(BLACK);
	WriteAPixel(0, 0, RED);
	WriteAPixel(0, MAX_Y, RED);
	WriteAPixel(MAX_X, 0, RED);
	WriteAPixel(MAX_X, MAX_Y, RED);
	Line(1, 1, MAX_X-1, MAX_Y-1, LIME);
	int colour = ReadAPixel(MAX_X-1, MAX_Y-1);
	Line(1, MAX_Y-1, MAX_X-1, 1, colour);

	printf("end\n");
	return 0;
}
