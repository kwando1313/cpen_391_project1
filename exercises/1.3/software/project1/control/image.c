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
#define DISPLAY_HEIGHT	400
#define DISPLAY_WIDTH 	600
#define HEADERSIZE 		54
#define COLOURTABLESIZE 1024

void load_image_to_pixels_arr(short file);

// Store the integer values of the colours for each pixel.
int** image_pixels; //full_map[bmpWidth][bmpHeight]
int bmpWidth, bmpHeight;

void load_draw_image(Point topLeft, int xstart, int ystart, char* filename){
	draw_button(topLeft, DISPLAY_WIDTH, DISPLAY_HEIGHT, 1, 1, BLACK, WHITE, "LOADING...", MEDIUM);

	load_image(filename);
	draw_image(topLeft, xstart, ystart);
}

/*	Load image from SD Card.
 * 	SD Card must be formatted in FAT16 to work with DE2.
 * 	Length of filenames cannot be longer than 12 characters.
 * 	including file extension (i.e. "abcdefghi.bmp" is invalid.
 */
void load_image(char* filename){
	void (*func)(short) = &load_image_to_pixels_arr;
	load_file(filename, func);
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
	//width must be divisible by 4
	int width = (bmpWidth % 4 == 0) ? bmpWidth : (bmpWidth + 4 - (bmpWidth % 4));
	for (int j = 0; j < bmpHeight; j++){
		for (int i = 0; i < width; i++){
			image_pixels[i][j] = alt_up_sd_card_read(file);
		}

	}
}

/* Draw the pictures in the range we want.
 * We're picking the top left point to start from
 * but actually draw from the bottom left first.
 */
void draw_image(Point topLeft, int xstart, int ystart){

	int height = (bmpHeight < DISPLAY_HEIGHT) ? bmpHeight : DISPLAY_HEIGHT;
	int width = (bmpWidth < DISPLAY_WIDTH) ? bmpWidth: DISPLAY_WIDTH;


	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			int initialX = x;
			int colour = image_pixels[xstart + x][ystart + y];
			int colour2 = image_pixels[xstart + x][ystart + y];

			while (colour == colour2 && x < width){
				x++;
				colour2 = image_pixels[xstart+x][ystart+y];
			}
//			if(getPalleteAddr(int RGB);
//			int getRGB(int addr);
			HLine(topLeft.x + initialX, topLeft.y + height - y, x - initialX, colour);
			x--;
			//WriteAPixel(topLeft.x + x, topLeft.y + height-y, colour);
		}
	}
}
