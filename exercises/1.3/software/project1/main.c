#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

int main(void) {
	 printf("start\n");
	 clear_screen(YELLOW);
	 Point corner_a = {0, 0};
	 Point corner_b = {XRES, 0};
	 Point corner_c = {0, YRES};
	 Point corner_d = {XRES, YRES};

	 //	Point out_a = {100, 100};
	 //	Point out_b = {700, 100};
	 //	Point out_c = {100, 400};
	 //	Point out_d = {700, 400};
	 //
	 //	Point in_a = {300, 200};
	 //	Point in_b = {400, 200};
	 //	Point in_c = {300, 300};
	 //	Point in_d = {400, 300};

	//oblique
	Point tri_a = {52, 63};
	Point tri_b = {652, 363};
	Point tri_c = {152, 263};

	Point tri_d = {100, 100};
	Point tri_e = {400, 200};
	//right
 //	Point tri_d = {100, 100};
 //	Point tri_e = {100, 400};
	Point tri_f = {500, 400};

	//acute
	Point tri_g = {352, 63};
	Point tri_h = {652, 363};
	Point tri_i = {152, 263};

	draw_filled_rectangle_border(corner_a, corner_b, corner_c, corner_d, BLACK, CYAN, 2);
 //	draw_filled_rectangle_border(out_a, out_b, out_c, out_d, RED, YELLOW, 1);
 //	draw_filled_rectangle_border(in_a, in_b, in_c, in_d, LIME, BLACK, 5);
//	int ticks_start = alt_nticks();

	/*
	 * void draw_filled_triangle(Point a, Point b, Point c, int colour);
 void draw_filled_triangle_border(Point a, Point b, Point c, int colour, int borderColour);
	 */
	Point points[] = {tri_a, tri_d, tri_e, tri_b, tri_c};
	//draw_shape(points, 5, LIME);
 //	draw_shape(tri_e, tri_d, tri_f, YELLOW);
 //	draw_shape(tri_g, tri_h, tri_i, BLUE);
 //

	WriteAPixel(0, 0, CYAN);


	Point point0 = {200, 200};
	Point point1 = {500, 100};
	Point point2 = {400, 300};

	draw_circle(point0, 100, RED);
	//draw_arc(point0, 100, BLUE, 0, 180);
	draw_arc(point0, 100, BLUE, 120, 300);

	draw_circle(point1, 100, RED);
	draw_arc(point1, 100, LIME, 0, 120);

	draw_circle(point2, 100, RED);
	draw_arc(point2, 100, YELLOW, 30, 300);


//	draw_filled_circle(point1, 100, RED);
//	draw_filled_circle_border(point2, 20, LIME, YELLOW);

	clear_screen(WHITE);
	OutGraphicsCharFont1(50, 50, BLACK, YELLOW, (int)('c'), 1);
	OutGraphicsCharFont2a(200, 200, BLACK, YELLOW, (int)('A'), 0);

	printf("end\n");
	return 0;
}
