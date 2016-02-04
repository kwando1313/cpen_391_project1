// The following lines are for testing the SD Card, hence why they are commented out for now.

#include <stdio.h>
#include "menu.h"
#include <touchscreen.h>
#include <graphics.h>
#include <string.h>
#include <altera_up_sd_card_avalon_interface.h>

int main(void){
	//test_graphics();
	Point topLeft = {0,0};
	clear_screen(WHITE);
	char* name = "TEST.BMP";
	load_image(topLeft);//, name, 459, 500);
	init_screen();
	//photo_screen();

//	alt_up_sd_card_dev* device_reference = NULL;
//	Init_Touch();
//	clear_screen(WHITE);
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
//					char * image = "test.bmp";
//					char header;
//
//					if (alt_up_sd_card_find_first("/", name) == 0){
//						printf(name);
//						short int file = alt_up_sd_card_fopen(name, false);
//						if (file == -1){
//							printf("This file could not be opened.\n");
//						}
//						else if (file == -2){
//							printf("This file is already opened.\n");
//						}
//						else {
//							printf("Reading file...\n");
//							while(alt_up_sd_card_read(file) > 0){
//								printf("Continuing to read file...\n");
//							}
//							printf("Finished reading file!\n");
//						}
//						while(alt_up_sd_card_find_next(name) == 0){
//							printf(name);
//							char* name2;
//							strcpy(name2, name);
//							short int file = alt_up_sd_card_fopen(name, false);
//							if (file == -1){
//								printf("This file could not be opened.\n");
//							}
//							else if (file == -2){
//								printf("This file is already opened.\n");
//							}
//							else {
//
//								char pixel[BMPHEIGHT][BMPWIDTH];
//
//								printf("Reading file...\n");
//								for(int x=0 ; x<54 ; x++){
//									header=(unsigned char)(alt_up_sd_card_read(file));
//									printf ("%hhx ",header & 0xff);
//								}
//								printf("\n");
//								short data =0;
//								printf("%s\n", name);
//								if (strcmp(name, "TEST.BMP")== 0){
//									for (int j = 0; j < BMPHEIGHT; j++){
//										for (int i = 0; i < BMPWIDTH; i++){
//												data = alt_up_sd_card_read(file);
//												pixel[j][i] = (char)data;
//												data = alt_up_sd_card_read(file);
//												data = alt_up_sd_card_read(file);
//										}
//									}
//
//
//
//
//									for (int y = 0; y < BMPHEIGHT; y++){
//										for (int x = 0; x < BMPWIDTH; x++){
//											if (pixel[y][x] !=  (char)0xff){
//												//printf ("%hhx ", pixel[0] & 0xff);
//												WriteAPixel(x,BMPHEIGHT-y, BLACK);
//											}
//											else{
//												WriteAPixel (x,BMPWIDTH-y, WHITE);
//											}
//										}
//									}
//									printf("Finished reading file!!!!\n");
//									//return 0;
//								}
//								printf("Finished reading file!\n");
//							}
//						}
//					}
//					else if (alt_up_sd_card_find_first("/", name) == 1){
//						printf("This is an invalid directory.\n");
//					}
//					else if (alt_up_sd_card_find_first("/", name) == 2){
//						printf("The SD card has either been disconnected, or is NOT a FAT16 type.\n");
//					}
//				}
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
}


