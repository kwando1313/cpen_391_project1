#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

int main(void) {
	printf("start\n");
	clear_screen(YELLOW);
	Point corner_a = {0, 0};
	Point corner_b = {MAX_X, 0};
	Point corner_c = {0, MAX_Y};
	Point corner_d = {MAX_X, MAX_Y};

	Point out_a = {100, 100};
	Point out_b = {700, 100};
	Point out_c = {100, 400};
	Point out_d = {700, 400};

	Point in_a = {300, 200};
	Point in_b = {400, 200};
	Point in_c = {300, 300};
	Point in_d = {400, 300};

	draw_filled_rectangle_border(corner_a, corner_b, corner_c, corner_d, BLACK, CYAN, 2);
	draw_filled_rectangle_border(out_a, out_b, out_c, out_d, RED, YELLOW, 1);
	draw_filled_rectangle_border(in_a, in_b, in_c, in_d, LIME, BLACK, 5);

	printf("end\n");
	return 0;
}
