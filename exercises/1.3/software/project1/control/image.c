#include <stdio.h>
#include <stdlib.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "graphics.h"
#include "misc_helpers.h"
#include "image.h"
#include "directions.h"
#include "ColourPallette.h"

extern const unsigned int ColourPalletteData[256];

Point start = {0,0};
int startx = 0, ystart = 0;

Point ret_start_points(void){
	Point ret = {start.x, ystart};
	return ret;
}

void load_zoom_in_pixels(short file);
void load_zoom_out_pixels(short file);
void get_header(short file, int zoom);
void get_pixels(short file, int zoom);

/*	Load image from SD Card.
 * 	SD Card must be formatted in FAT16 to work with DE2.
 * 	Length of filenames cannot be longer than 12 characters.
 * 	including file extension (i.e. "abcdefghi.bmp" is invalid.
 */
void load_zoom_out_image(char* filename){
	void (*func)(short) = &load_zoom_out_pixels;
	load_file(filename, func);
}

void load_zoom_in_image(char* filename){
	void (*func)(short) = &load_zoom_in_pixels;
	load_file(filename, func);
}

void load_zoom_out_pixels(short file){
	get_header(file, ZOOM_OUT);
	get_pixels(file, ZOOM_OUT);
}

void load_zoom_in_pixels(short file){
	get_header(file, ZOOM_IN);
	get_pixels(file, ZOOM_IN);
}

/* Get header information.
 * Iterate and print bitmap file header + Windows Bitmap Info Header.
 * Iterate and do not print the colour table.
 */
void get_header (short file, int zoom){
	unsigned char height[4];
	unsigned char width[4];
	unsigned char buf[30];

	read_bytes_from_file(buf, 18, file);
	read_bytes_from_file(width, 4, file);
	read_bytes_from_file(height, 4, file);
	read_bytes_from_file(buf, 28, file);

	int bmpWidth = *(int *)width;
	int bmpHeight = *(int *)height;
	image_width[zoom] = bmpWidth;
	image_height[zoom] = bmpHeight;

	printf("bmp width: %d, bmp height: %d\n", bmpWidth, bmpHeight);

	image_pixels[zoom] = malloc(sizeof(char*)*bmpWidth);
	for(int i = 0; i<bmpWidth; i++){
		image_pixels[zoom][i] = malloc(sizeof(char)*bmpHeight);
	}

	unsigned char entry[4];

	for (int i = 0; i < COLOURTABLESIZE; i+=4){
		read_bytes_from_file(entry, 4, file);
		int rgb = *(int*)entry;
		// sanity checking we have all the colours we need
		if(ColourPalletteData[i/4] != rgb){
			printf("entry: %d, rgb: %x is missing from colour pallette!\n", i/4, rgb);
		}
	}
}

/* Store pixel colours in 2-D array.
 */
void get_pixels(short file, int zoom){
	//width must be divisible by 4
	int width = (image_width[zoom] % 4 == 0) ? image_width[zoom] : (image_width[zoom] + 4 - (image_width[zoom] % 4));
	for (int j = 0; j < image_height[zoom]; j++){
		for (int i = 0; i < width; i++){
			image_pixels[zoom][i][j] = alt_up_sd_card_read(file);
		}
	}
}

/* Draw the pictures in the range we want.
 * We're picking the top left point to start from
 * but actually draw from the bottom left first.
 */
void draw_image(Point start){
	int height = (image_height[zoom_level] < DISPLAY_HEIGHT) ? image_height[zoom_level] : DISPLAY_HEIGHT;
	int width = (image_width[zoom_level] < DISPLAY_WIDTH) ? image_width[zoom_level]: DISPLAY_WIDTH;

	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			int initialX = x;
			char colour = image_pixels[zoom_level][start.x + x][start.y + y];
			char colour2 = image_pixels[zoom_level][start.x + x][start.y + y];

			while (colour == colour2 && x < width){
				x++;
				colour2 = image_pixels[zoom_level][start.x+x][start.y+y];
			}
			HLine(initialX, height - y, x - initialX, (int)colour);
			x--;
		}
	}
}

/*	Move the x and y start points according to button
 * 	Draw image again.
 * 	This code is written to not go past the edge of the image.
 */
void move_img (Direction direction){
	if (direction == UP){
		if (ystart > image_height[zoom_level] - DISPLAY_HEIGHT - SHIFT)
			ystart = image_height[zoom_level] - DISPLAY_HEIGHT;
		else ystart += SHIFT;
		printf ("UP\n");
	}
	else if (direction == DOWN){
		if (ystart < SHIFT)
			ystart = 0;
		else ystart -= SHIFT;
		printf ("DOWN\n");

	}
	else if (direction == RIGHT){
		if (start.x > image_width[zoom_level] - DISPLAY_WIDTH - SHIFT)
			start.x = image_width[zoom_level] - DISPLAY_WIDTH;
		else start.x += SHIFT;
		printf ("RIGHT\n");
	}
	else if (direction == LEFT){
		if (start.x < SHIFT)
			start.x = 0;
		else start.x -= SHIFT;
		printf ("LEFT\n");
	}
	Point printStart = ret_start_points ();
	printf ("%d, %d", printStart.x, printStart.y);
	draw_image(printStart);
}
