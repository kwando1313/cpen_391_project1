#include <stdio.h>
#include <stdlib.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "graphics.h"
#include "misc_helpers.h"
#include "image.h"

extern const unsigned int ColourPalletteData[256];

/*	IMGHEIGHT 	: Full height of our BMP
 * 	IMGWIDTH 	: Full width of our BMP
 * 	BOXHEIGHT 	: Height of the box we print our image.
 * 	BOXWIDTH 	: Width of the box we print our image.
 * 	HEADERSIZE changes with type of BMP file
 * 	COLOURTABLESIZE = size of colour table containing 256 colours (with BGRA fields)
 */
//#define IMGHEIGHT 	525
//#define IMGWIDTH 	717
#define DISPLAY_HEIGHT	361
#define DISPLAY_WIDTH 	373
#define HEADERSIZE 		54
#define COLOURTABLESIZE 1024

void load_image_to_pixels_arr(short file);

// Store the integer values of the colours for each pixel.
int** image_pixels; //full_map[bmpWidth][bmpHeight]
int bmpWidth, bmpHeight;

void load_draw_image(Point topLeft, int xstart, int ystart, char* filename){
	load_image(filename);
	draw_image(topLeft, xstart, ystart);
}

/*	Load image from SD Card.
 * 	SD Card must be formatted in FAT16 to work with DE2.
 * 	Length of filenames cannot be longer than 12 characters.
 * 	including file extension (i.e. "abcdefghi.bmp" is invalid.
 */

//TODO same code as load_node, functionalize this. Pass in *f(), this gets called on file found
void load_image(char* filename){
	bool found_file = false;

	if (get_device_reference() == NULL || !alt_up_sd_card_is_Present() || !alt_up_sd_card_is_FAT16()){
		printf("Can't find device, or device not configured properly\n");
		return;
	}

	char filename_all_caps[strlen(filename)];
	to_caps(filename, filename_all_caps);
	char found_file_name[13];
	if (alt_up_sd_card_find_first(".", found_file_name) != 0){
		printf("Couldn't find root dir\n");
		return;
	}

	do {
		if (strcmp(found_file_name, filename_all_caps)== 0){
			short int file = alt_up_sd_card_fopen(found_file_name, false);
			if (file >= 0){
				printf("found file %s in SD\n", filename_all_caps);
				load_image_to_pixels_arr(file);
				found_file = true; //want to close file, so use this rather than returning
			}
			alt_up_sd_card_fclose(file);
		}
	}while(!found_file && alt_up_sd_card_find_next(found_file_name) == 0);
}

void load_image_to_pixels_arr(short file){
	get_header(file);
	get_pixels(file);
}
	//draw_img(topLeft, file, 0, ystart);

/* Get header information.
 * Iterate and print bitmap file header + Windows Bitmap Info Header.
 * Iterate and do not print the colour table.
 */
void get_header (short file){
	unsigned char height[4];
	unsigned char width[4];
	unsigned char buf[30];

	read_bytes_from_file(buf, 18, file);
	read_bytes_from_file(width, 4, file);
	read_bytes_from_file(height, 4, file);
	read_bytes_from_file(buf, 28, file);

	bmpWidth = *(int *) width;
	bmpHeight = *(int *) height;
	printf("bmp width: %d, bmp height: %d\n", bmpWidth, bmpHeight);

	image_pixels = malloc(sizeof(int*)*bmpWidth);
	for(int i = 0; i<bmpWidth; i++){
		image_pixels[i] = malloc(sizeof(int)*bmpHeight);
	}

	unsigned char entry[4];

	for (int i = 0; i < COLOURTABLESIZE; i+=4){
		read_bytes_from_file(entry, 4, file);
		int rgb = *(int*)entry;
		if(ColourPalletteData[i/4] != rgb){
			printf("entry: %d, rgb: %x\n", i/4, rgb);
		}
	}
}

/* Store pixel colours in 2-D array.
 */
void get_pixels(short file){
	printf("bmp width: %d, bmp height: %d\n", bmpWidth, bmpHeight);
	for (int j = 0; j < bmpHeight; j++){
		for (int i = 0; i < 376; i++){ //hardcoding the width because the width is WEIRD right now
			//image_pixels[i][j] = alt_up_sd_card_read(file);
			WriteAPixel(i, bmpHeight-j, alt_up_sd_card_read(file));
			//printf("At column %d\n", j);
		}

	}
}

/* Draw the pictures in the range we want.
 * We're picking the top left point to start from
 * but actually draw from the bottom left first.
 */
void draw_image(Point topLeft, int xstart, int ystart){

//	int height = (bmpHeight < DISPLAY_HEIGHT) ? bmpHeight : DISPLAY_HEIGHT;
//	int width = (bmpWidth < DISPLAY_WIDTH) ? bmpWidth: DISPLAY_WIDTH;
//
//
//	for (int y = 0; y < height; y++){
//		for (int x = 0; x < width; x++){
//			int colour = image_pixels[xstart + x][ystart + y];
////			if(getPalleteAddr(int RGB);
////			int getRGB(int addr);
//			WriteAPixel(topLeft.x + x, topLeft.y + height-y, colour);
//		}
//	}
}
