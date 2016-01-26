#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "sys/alt_alarm.h"

int main(void) {
	printf("start\n");
	clear_screen(YELLOW);
	Point corner_a = {0, 0};
	Point corner_b = {MAX_X, 0};
	Point corner_c = {0, MAX_Y};
	Point corner_d = {MAX_X, MAX_Y};

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
	int ticks_start = alt_nticks();

	/*
	 * void draw_filled_triangle(Point a, Point b, Point c, int colour);
void draw_filled_triangle_border(Point a, Point b, Point c, int colour, int borderColour);
	 */
	Point points[] = {tri_a, tri_d, tri_e, tri_b, tri_c};
	draw_filled_shape_border(points, 5, BLUE, LIME);
//	draw_shape(tri_e, tri_d, tri_f, YELLOW);
//	draw_shape(tri_g, tri_h, tri_i, BLUE);
//

	WriteAPixel(0, 0, CYAN);
	int ticks_end = alt_nticks();
	int ticks_per_s = alt_ticks_per_second();
	int ticks_duration = ticks_end - ticks_start;
	float duration = (float) ticks_duration / (float) ticks_per_s;
	printf("%f seconds\n\n", duration);

	printf("end\n");
	return 0;
}


// The following lines are for testing the SD Card, hence why they are commented out for now.

//#include <stdio.h>
//#include <altera_up_sd_card_avalon_interface.h>
//int main(void){
//	alt_up_sd_card_dev* device_reference = NULL;
//	int connected = 0;
//	printf("Opening SDCard\n");
//	if ((device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL){
//		printf("SDCard Open FAILED\n");
//		return 0 ;
//	}
//	else
//		printf("SDCard Open PASSED\n");
//
//	if(device_reference != NULL ) {
//		while(1) {
//			if((connected == 0) && (alt_up_sd_card_is_Present())){
//				printf("Card connected.\n");
//
//				if(alt_up_sd_card_is_FAT16()) {
//					printf("FAT16 file system detected.\n");
//
//					char * name;
//					if (alt_up_sd_card_find_first("/", name) == 0){
//						printf(name);
//						short int file = alt_up_sd_card_fopen(name, false);
//						if (file == -1){
//							printf("This file could not be opened.");
//						}
//						else if (file == -2){
//							printf("This file is already opened.");
//						}
//						else {
//							printf("Reading file...");
//							while(alt_up_sd_card_read(file) > 0){
//								printf("Continuing to read file...");
//							}
//							printf("Finished reading file!");
//						}
//						while(alt_up_sd_card_find_next(name) == 0){
//							printf(name);
//							short int file = alt_up_sd_card_fopen(name, false);
//							if (file == -1){
//								printf("This file could not be opened.");
//							}
//							else if (file == -2){
//								printf("This file is already opened.");
//							}
//							else {
//								printf("Reading file...");
//								while(alt_up_sd_card_read(file) > 0){
//									continue;
//								}
//								printf("Finished reading file!");
//							}
//						}
//					}
//					else if (alt_up_sd_card_find_first("/", name) == -1){
//						printf("No files were found in this directory.");
//						printf("Going to create a file in this directory...");
//						short int file = alt_up_sd_card_fopen("test.txt", true);
//
//						if (file == -1){
//							printf("This file could not be opened.");
//						}
//						else if (file == -2){
//							printf("This file is already opened.");
//						}
//						else {
//							printf("File created!");
//							for (int x = 0; x < 1024; x++){
//								if (alt_up_sd_card_write(file, 'A') == 0){
//									printf("There was an error writing to the file...");
//									return 0;
//								}
//							}
//							alt_up_sd_card_fclose(file);
//						}
//
//					}
//					else if (alt_up_sd_card_find_first("/", name) == 1){
//						printf("This is an invalid directory.");
//					}
//					else if (alt_up_sd_card_find_first("/", name) == 2){
//						printf("The SD card has either been disconnected, or is NOT a FAT16 type.");
//					}
//				}
//
//
//				else{
//					printf("Unknown file system.\n");
//				}
//				connected = 1;
//			} else if((connected == 1) && (alt_up_sd_card_is_Present() == 0)){
//				printf("Card disconnected.\n");
//				connected =0;
//			}
//		}
//	}
//	else{
//		printf("Can't open device\n");
//	}
//	return 0;
//}


