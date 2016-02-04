/*
 * menu.c
 *
 *  Created on: 2016-01-28
 *      Author: kwando1313
 */

#include "misc_helpers.h"
#include "graphics.h"
#include "FontSize.h"
#include <stdio.h>
#include <string.h>
#include <touchscreen.h>
#include <graphics.h>
#include <altera_up_sd_card_avalon_interface.h>

#define BMPHEIGHT 480
#define BMPWIDTH 500

void load_image(Point topLeft, char* filename){//, int bmpheight, int bmpwidth){
	alt_up_sd_card_dev* device_reference = NULL;
		//Init_Touch();
		//clear_screen(WHITE);
		int connected = 0;
		printf("Opening SDCard\n");
		if ((device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL){
			printf("SDCard Open FAILED\n");
			return;
		}
		else
			printf("SDCard Open PASSED\n");

		if(device_reference != NULL ) {
			while(1) {
				if((connected == 0) && (alt_up_sd_card_is_Present())){
					printf("Card connected.\n");

					if(alt_up_sd_card_is_FAT16()) {
						printf("FAT16 file system detected.\n");

						char * name = "A";
						char header;

						if (alt_up_sd_card_find_first("/", name) == 0){

							short int file = alt_up_sd_card_fopen(name, false);
							if (file == -1){
								printf("This file could not be opened.\n");
							}
							else if (file == -2){
								printf("This file is already opened.\n");
							}
							else {
								char pixel[BMPHEIGHT][BMPWIDTH][3];
								char B[BMPHEIGHT][BMPWIDTH];
								char G[BMPHEIGHT][BMPWIDTH];
								char R[BMPHEIGHT][BMPWIDTH];

								printf("Reading file...\n");
								for(int x=0 ; x<54 ; x++){
									header=(unsigned char)(alt_up_sd_card_read(file));
									printf ("%hhx ",header & 0xff);
								}
								printf("\n");
								short data =0;
								printf("Current file: %s\n", name);
								printf("My name: %s\n", filename);
								if (strcmp(name, filename)== 0){
									for (int j = 0; j < BMPHEIGHT; j++){
										for (int i = 0; i < BMPWIDTH; i++){
												data = alt_up_sd_card_read(file);
												B[j][i] = (char)data;
												data = alt_up_sd_card_read(file);
												G[j][i] = (char)data;
												data = alt_up_sd_card_read(file);
												R[j][i] = (char)data;
												pixel[j][i][0] = R[j][i];
												pixel[j][i][1] = G[j][i];
												pixel[j][i][2] = B[j][i];
										}
									}




									for (int y = 0; y < BMPHEIGHT; y++){
										for (int x = 0; x < BMPWIDTH; x++){
											int colour = check_colour(pixel[y][x]);
											WriteAPixel(topLeft.x + x, topLeft.y + BMPHEIGHT-y, colour);

										}
									}
									printf("Finished reading file!!!!\n");
								}
								alt_up_sd_card_fclose(file);
							}
							while(alt_up_sd_card_find_next(name) == 0){
								printf("NOW I FOUND: %s\n", name);
								if (strcmp(name, filename) == 0){
									short int file = alt_up_sd_card_fopen(name, false);
									if (file == -1){
										printf("This file could not be opened.\n");
									}
									else if (file == -2){
										printf("This file is already opened.\n");
									}
									else {

										char pixel[BMPHEIGHT][BMPWIDTH][3];
										char B[BMPHEIGHT][BMPWIDTH];
										char G[BMPHEIGHT][BMPWIDTH];
										char R[BMPHEIGHT][BMPWIDTH];

										printf("Reading file...\n");
										for(int x=0 ; x<54 ; x++){
											header=(unsigned char)(alt_up_sd_card_read(file));
											printf ("%hhx ",header & 0xff);
										}
										printf("\n");
										short data =0;
										printf("NAME: %s\n", name);
										printf("FILENAME: %s\n", filename);
										if (strcmp(name, filename)== 0){
											for (int j = 0; j < BMPHEIGHT; j++){
												for (int i = 0; i < BMPWIDTH; i++){
														data = alt_up_sd_card_read(file);
														B[j][i] = (char)data;
														//printf("%hhx ", data & 0xff);
														data = alt_up_sd_card_read(file);
														G[j][i] = (char)data;
														//printf("%hhx ", data & 0xff);
														data = alt_up_sd_card_read(file);
														R[j][i] = (char)data;
														//printf("%hhx ", data & 0xff);
														pixel[j][i][0] = R[j][i];
														pixel[j][i][1] = G[j][i];
														pixel[j][i][2] = B[j][i];
												}
											}




											for (int y = 0; y < BMPHEIGHT; y++){
												for (int x = 0; x < BMPWIDTH; x++){
													int colour = check_colour(pixel[y][x]);
													WriteAPixel(topLeft.x + x, topLeft.y + BMPHEIGHT-y, colour);

												}
											}
											printf("Finished reading file!!!!\n");
											//return;
											//return 0;
										}
										else {
											printf("Finished reading file!\n");
										}
									}
									alt_up_sd_card_fclose(file);
								}
							}
							return;

						}
						else if (alt_up_sd_card_find_first("/", name) == 1){
							printf("This is an invalid directory.\n");
						}
						else if (alt_up_sd_card_find_first("/", name) == 2){
							printf("The SD card has either been disconnected, or is NOT a FAT16 type.\n");
						}
					}

					else{
						printf("Unknown file system.\n");
					}
					connected = 1;
				} else if((connected == 1) && (alt_up_sd_card_is_Present() == 0)){
					printf("Card disconnected.\n");
					connected =0;
				}
			}
		}
		else{
			printf("Can't open device\n");
		}
		return;
}

//Text box is left aligned and has text wrapping
void draw_text_box(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize){
	int textLength = (int) strlen(text);
	Point topRight = {topLeft.x + width, topLeft.y};
	Point bottomLeft = {topLeft.x, topLeft.y + height};
	Point bottomRight = {topLeft.x + width, topLeft.y + height};

	draw_filled_rectangle_border(topLeft, topRight, bottomLeft, bottomRight, fillColour, borderColour, borderWidth);
	int initialX = 0;
	int initialY = 0;


	int fontSizePixelsWidth = 5;
	int fontSizePixelsHeight = 7;

	if (fontSize == MEDIUM){
		fontSizePixelsWidth = 10;
		fontSizePixelsHeight = 14;
	}

	initialX = topLeft.x + 10; //give 10 pixels margin
	initialY = topLeft.y + 10; //May make this an adjustable variable

	char* temp_text;
	strcpy(temp_text, text);

	char * token = strtok(temp_text, " ");

	while (token != NULL){
		int stringLength = (int) strlen(token);
		if (initialX + (stringLength * (fontSizePixelsWidth + 1)) > topRight.x - 10){
			initialX = topLeft.x + 10;
			initialY = initialY + fontSizePixelsHeight + 1;
		}
		for (int x = 0; x < stringLength; x++){
			if (token[x] == '\n'){
				initialX = topLeft.x + 4;
				initialY = initialY + fontSizePixelsHeight + 1;
			}
			if (fontSize == MEDIUM){
				OutGraphicsCharFont2a(initialX, initialY, textColour, textColour, (int)token[x], 0);
			}
			else {
				OutGraphicsCharFont1(initialX, initialY, textColour, textColour, (int)token[x], 0);
			}
			initialX = initialX + fontSizePixelsWidth + 1;
		}
		if (fontSize == MEDIUM){
			OutGraphicsCharFont2a(initialX, initialY, textColour, textColour, (int)" ", 0);
		}
		else {
			OutGraphicsCharFont1(initialX, initialY, textColour, textColour, (int)" ", 0);
		}
		initialX = initialX + fontSizePixelsWidth + 1;
		token = strtok(NULL, " ");
	}

}

//draw the info box on the RHS of the touchscreen
void draw_information_box(char* text){
	Point point8;

	point8.x = 500;
	point8.y = 0;
	draw_text_box(point8, 300, 330,2, BLACK, WHITE, BLACK, text, SMALL);

}

//button is center aligned and has no text wrapping
void draw_button(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, char* text, int fontSize){
	int textLength = (int) strlen(text);

	Point topRight = {topLeft.x + width, topLeft.y};
	Point bottomLeft = {topLeft.x, topLeft.y + height};
	Point bottomRight = {topLeft.x + width, topLeft.y + height};

	draw_filled_rectangle_border(topLeft, topRight, bottomLeft, bottomRight, fillColour, borderColour, borderWidth);
	int initialX = 0;
	int initialY = 0;


	int fontSizePixelsWidth = 5;
	int fontSizePixelsHeight = 7;

	if (fontSize == MEDIUM){
		fontSizePixelsWidth = 10;
		fontSizePixelsHeight = 14;
	}

	if (textLength %2 == 0){
		initialX = topLeft.x + width/2 - (textLength * (fontSizePixelsWidth + 1))/2;
	}
	else {
		initialX = topLeft.x + width/2 - (textLength * (fontSizePixelsWidth + 1))/2;
	}

	initialY = topLeft.y + height/2 - fontSizePixelsHeight/2;

	for (int x = 0; x < textLength; x++){
		if (fontSize == MEDIUM){
			OutGraphicsCharFont2a(initialX, initialY, textColour, textColour, (int)text[x], 0);
		}
		else {
			OutGraphicsCharFont1(initialX, initialY, textColour, textColour, (int)text[x], 0);
		}
		initialX = initialX + fontSizePixelsWidth + 1;
	}
}

//menu is buttons from top down
void draw_menu(Point leftCorner, int width, int height, int borderWidth, int borderColour, int fillColour, int textColour, int fontSize, char** menuText){
	int x = 0;
	while (menuText[x] != ""){
		draw_button(leftCorner, width, height, borderWidth, borderColour, fillColour, textColour, menuText[x], fontSize);
		leftCorner.y+= height;
		x++;
	}
}


void init_screen(){

		Point point6 = {500, 330};
		Point point7 = {650, 330}; //Adjust these to fit within the margins...

		char* firstTextArray[] = {"Info", "Photo", ""};
		char* secondTextArray[] = {"Directions", "About", ""};

		draw_information_box("Pathfinding Map (Team 22)\nAlex Charles\nAngela Cho\nCaleb Kwan\nWilliam Tang\n\nThis is our project!");
		draw_menu(point6, 150, 75, 2, BLACK, WHITE, BLACK, SMALL, firstTextArray);

		draw_menu(point7, 150, 75, 2, BLACK, WHITE, BLACK, SMALL, secondTextArray);

}

void about_screen(){
	draw_information_box("Pathfinding Map (Team 22)\nAlex Charles\nAngela Cho\nCaleb Kwan\nWilliam Tang\n\nThis is our project!");
}

void info_screen(){
	draw_information_box("BUILDING INFO");
}

void directions_screen(){
	draw_information_box("DIRECTIONS");
}

void photo_screen(){
//	char* name = "PIC.BMP";
//	Point point = {500, 0};
//	load_image(point, name, 330, 300);
	draw_information_box("BUILDING PHOTO");
}

int check_colour(char* pixel){
	if (pixel[0] ==  ((char)0xff) && pixel[1] == (char) 0x0 && pixel[2] == (char) 0x00){
		return RED;
	}
	else if (pixel[0] ==  ((char)0xB5) && pixel[1] == (char) 0xE6 && pixel[2] == (char) 0x1D){
		return LIME;
	}
	else if (pixel[0] ==  ((char)0x00) && pixel[1] == (char) 0x00 && pixel[2] == (char) 0xff){
		return BLUE;
	}
	else if (pixel[0] ==  ((char)0x00) && pixel[1] == (char) 0x00 && pixel[2] == (char) 0x00){
		return BLACK;
	}
	else if (pixel[0] ==  ((char)0xff) && pixel[1] == (char) 0xff && pixel[2] == (char) 0x00){
		return YELLOW;
	}
	else if (pixel[0] ==  ((char)0x99) && pixel[1] == (char) 0xD9 && pixel[2] == (char) 0xEA){
		return CYAN;
	}
	else if (pixel[0] ==  ((char)0xc0) && pixel[1] == (char) 0xc0 && pixel[2] == (char) 0xc){
		return SILVER;
	}
	else if (pixel[0] ==  ((char)0x80) && pixel[1] == (char) 0x80 && pixel[2] == (char) 0x80){
		return GRAY;
	}
	else if (pixel[0] ==  ((char)0xED) && pixel[1] == (char) 0x1C && pixel[2] == (char) 0x24){
		return MAROON;
	}
	else if (pixel[0] ==  ((char)0x80) && pixel[1] == (char) 0x80 && pixel[2] == (char) 0x00){
		return OLIVE;
	}
	else if (pixel[0] ==  ((char)0x22) && pixel[1] == (char) 0xB1 && pixel[2] == (char) 0x4C){
		return GREEN;
	}
	else if (pixel[0] ==  ((char)0x3F) && pixel[1] == (char) 0x48 && pixel[2] == (char) 0xCC){
		return PURPLE;
	}
	else if (pixel[0] ==  ((char)0x00) && pixel[1] == (char) 0xA2 && pixel[2] == (char) 0xE8){
		return TEAL;
	}
	else if (pixel[0] ==  ((char)0x00) && pixel[1] == (char) 0x00 && pixel[2] == (char) 0x80){
		return NAVY;
	}
	else if (pixel[0] ==  ((char)0xa5) && pixel[1] == (char) 0x2a && pixel[2] == (char) 0x2a){
		return BROWN;
	}
	else{
		return WHITE;
	}
}
