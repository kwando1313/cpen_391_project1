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


/*	BMPHEIGHT = y pixels
 * 	BMPWIDTH = x pixels
 * 	HEADERSIZE changes with type of BMP file
 * 	COLOURTABLESIZE = size of colour table containing 256 colours (with BGRA fields)
 */
#define BMPHEIGHT 480
#define BMPWIDTH 500
#define HEADERSIZE 54
#define COLOURTABLESIZE 1024

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
						char * image = "test.bmp";
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

								/*	Read BMP pixels, starting from the bottom left corner.
								 */
								int pixel[BMPHEIGHT][BMPWIDTH];

								printf("Reading file...\n");
								// Read header info.
								for(int x=0 ; x < HEADERSIZE ; x++){
									header =(unsigned char)(alt_up_sd_card_read(file));
									printf ("%hhx ",header & 0xff);
								}
								for (int i = 0; i < COLOURTABLESIZE; i++){
									(unsigned char)alt_up_sd_card_read(file);
								}
								printf("\n");

								printf("Current file: %s\n", name);
								printf("My name: %s\n", filename);
								if (strcmp(name, filename)== 0){
									for (int j = 0; j < BMPHEIGHT; j++){
										for (int i = 0; i < BMPWIDTH; i++){		// store pixel data
												pixel[j][i] = alt_up_sd_card_read(file);
										}
									}

									for (int y = 0; y < BMPHEIGHT; y++){
										for (int x = 0; x < BMPWIDTH; x++){
											int colour = pixel[y][x];
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

										int pixel[BMPHEIGHT][BMPWIDTH];

										printf("Reading file...\n");
										for(int x=0 ; x < HEADERSIZE ; x++){
											header=(unsigned char)(alt_up_sd_card_read(file));
											printf ("%hhx ",header & 0xff);
										}
										for (int i = 0; i < COLOURTABLESIZE; i++){
											(unsigned char)alt_up_sd_card_read(file);
										}
										printf("\n");

										printf("NAME: %s\n", name);
										printf("FILENAME: %s\n", filename);
										if (strcmp(name, filename)== 0){
											for (int j = 0; j < BMPHEIGHT; j++){
												for (int i = 0; i < BMPWIDTH; i++){
													pixel[j][i] = alt_up_sd_card_read(file);												}
											}

											for (int y = 0; y < BMPHEIGHT; y++){
												for (int x = 0; x < BMPWIDTH; x++){
													int colour = pixel[y][x];
													WriteAPixel(topLeft.x + x, topLeft.y + BMPHEIGHT-y, colour);
												}
											}
											printf("Finished reading file!!!!\n");

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
	draw_text_box(point8, 300, 330,2, BLACK, 255, BLACK, text, SMALL);

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

void draw_keyboard(Point leftCorner, int size){
//qwertyuiop
	//asdfghjkl
	//zxcvbnm

	char* topRow[] = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", ""};
	char* homeRow[] = {"A", "S", "D", "F", "G", "H", "J", "K", "L", "<-", ""};
	char* bottomRow[] = {"Z", "X", "C", "V", "B", "N", "M", ""};

	int x = 0;
	Point initialLeftCorner = {leftCorner.x, leftCorner.y};
	while(topRow[x] != ""){
		draw_button(leftCorner, size, size, 1, BLACK, WHITE, BLACK, topRow[x], SMALL);
		leftCorner.x += size;
		x++;
	}
	x = 0;
	leftCorner.x = initialLeftCorner.x;
	leftCorner.y = initialLeftCorner.y + size;
	while(homeRow[x] != ""){
		draw_button(leftCorner, size, size, 1, BLACK, WHITE, BLACK, homeRow[x], SMALL);
		leftCorner.x += size;
		x++;
	}
	leftCorner.x = initialLeftCorner.x;
	leftCorner.y = initialLeftCorner.y + 2*size;
	x = 0;
	while(bottomRow[x] != ""){
		draw_button(leftCorner, size, size, 1, BLACK, WHITE, BLACK, bottomRow[x], SMALL);
		leftCorner.x += size;
		x++;
	}
	draw_button(leftCorner, 3*size, size, 1, BLACK, WHITE, BLACK, "SPACE", SMALL);
	return;
}

void init_screen(){

		Point point6 = {500, 330};
		Point point7 = {650, 330}; //Adjust these to fit within the margins...

		char* firstTextArray[] = {"Info", "Photo", ""};
		char* secondTextArray[] = {"Directions", "About", ""};

		draw_information_box("Pathfinding Map (Team 22)\nAlex Charles\nAngela Cho\nCaleb Kwan\nWilliam Tang\n\nThis is our project!");
		draw_menu(point6, 150, 75, 2, BLACK, 255, BLACK, SMALL, firstTextArray);

		draw_menu(point7, 150, 75, 2, BLACK, 255, BLACK, SMALL, secondTextArray);

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
