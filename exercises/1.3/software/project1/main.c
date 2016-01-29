#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "menu.h"

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

	clear_screen(WHITE);

	Point point4 = {100,0};

	Point point5 = {50, 300};

	draw_button(point4, 300, 100, 1, BLACK, LIME, BLACK, "Longer text", SMALL);
	draw_button(point5, 200, 100, 1, BLACK, BLUE, RED, "What happens when I have text overflow?", MEDIUM);

	clear_screen(WHITE);

	Point point6 = {0, 0};

	char* textArray[] = {"Item 1", "Longer Item", "Die the DEATH", "!!!!!!!!!", NULL};

	draw_menu(point6, 100, 50, 1, BLACK, LIME, BLACK, SMALL, textArray);

	draw_menu(point4, 100, 50, 3, BLUE, BLACK, WHITE, SMALL, textArray);

	printf("end\n");
	return 0;
}

/********************
 * The following lines are for testing the SD Card, hence why they are commented out for now.

#include <stdio.h>
#include <altera_up_sd_card_avalon_interface.h>
int main(void){
	alt_up_sd_card_dev* device_reference = NULL;
	int connected = 0;
	printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL){
		printf("SDCard Open FAILED\n");
		return 0 ;
	}
	else
		printf("SDCard Open PASSED\n");

	if(device_reference != NULL ) {
		while(1) {
			if((connected == 0) && (alt_up_sd_card_is_Present())){
				printf("Card connected.\n");

				if(alt_up_sd_card_is_FAT16()) {
					printf("FAT16 file system detected.\n");
				}


				else{
					printf("Unknown file system.\n");
				}
				connected = 1;
			} else if((connected == 1) && (alt_up_sd_card_is_Present() == false)){
				printf("Card disconnected.\n");
				connected =0;
			}
		}
	}
	else{
		printf("Can't open device\n");
	}
	return 0;
}

 *
 */
