#include <stdio.h>
#include <stdlib.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "graphics.h"
#include "misc_helpers.h"
#include "image.h"
#include "directions.h"
#include "ColourPallette.h"

extern const unsigned int ColourPalletteData[256];
extern int zoom_level;

void load_zoom_in_pixels(short file);
void load_zoom_out_pixels(short file);
void get_header(short file, int zoom);
void get_pixels(short file, int zoom);
void clear_extra_map_space(int height, int width);
char get_colour(int x, int y);

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

void clear_extra_map_space(int height, int width){
	for (int y = height; y<DISPLAY_HEIGHT; y++){
		HLine(0, y, DISPLAY_WIDTH, WHITE);
	}

	if (DISPLAY_HEIGHT - height > get_font_height(MEDIUM)){
		Point topLeft = {0, height};
		char* text = "UBC WAYFINDING";
		draw_text_box(topLeft, width, DISPLAY_HEIGHT-height, 1,
				BLACK, WHITE, BLACK, text, MEDIUM);
	}
}

char get_colour(int x, int y){
	int height = image_height[zoom_level];
	//in graphics, (0,0) is topLeft. for some unknown reason, bmp (0,0) is bottom left
	return image_pixels[zoom_level][curr_image_pos.x + x][height - (curr_image_pos.y + y) - 1];
}

/* Draw the pictures in the range we want.
 * We're picking the top left point to start from
 * but actually draw from the bottom left first, since the data is stored this way
 */
void draw_image_segment(Point topLeft, Point botRight){
	for (int y = topLeft.y; y < botRight.y; y++){
		for (int x = topLeft.x; x < botRight.x; x++){
			int initialX = x;
			char colour = get_colour(x, y);
			char colour2 = get_colour(x, y);

			while (colour == colour2 && x < botRight.x){
				x++;
				colour2 = get_colour(x, y);
			}
			HLine(initialX, y, x - initialX, (int)colour);
			x--;
		}
	}
}

void draw_full_image(void){
	int height = (image_height[zoom_level] < DISPLAY_HEIGHT) ? image_height[zoom_level] : DISPLAY_HEIGHT;
	int width = (image_width[zoom_level] < DISPLAY_WIDTH) ? image_width[zoom_level]: DISPLAY_WIDTH;

	clear_extra_map_space(height, width);

	Point topLeft = {0,0};
	Point botRight = {width, height};
	draw_image_segment(topLeft, botRight);
}

/*	Move the x and y start points according to button
 * 	Draw image again.
 * 	This code is written to not go past the edge of the image.
 */
void move_img (Direction direction){
	if (direction == UP){
		if (curr_image_pos.y > image_height[zoom_level] - DISPLAY_HEIGHT - SHIFT)
			curr_image_pos.y = image_height[zoom_level] - DISPLAY_HEIGHT;
		else curr_image_pos.y += SHIFT;
		printf ("UP\n");
	}
	else if (direction == DOWN){
		if (curr_image_pos.y < SHIFT)
			curr_image_pos.y = 0;
		else curr_image_pos.y -= SHIFT;
		printf ("DOWN\n");

	}
	else if (direction == RIGHT){
		if (curr_image_pos.x > image_width[zoom_level] - DISPLAY_WIDTH - SHIFT)
			curr_image_pos.x = image_width[zoom_level] - DISPLAY_WIDTH;
		else curr_image_pos.x += SHIFT;
		printf ("RIGHT\n");
	}
	else if (direction == LEFT){
		if (curr_image_pos.x < SHIFT)
			curr_image_pos.x = 0;
		else curr_image_pos.x -= SHIFT;
		printf ("LEFT\n");
	}

	draw_full_image();
}

Point convert_pnt_to_zoom_in(Point pnt){
	Point new_pnt;
	//new_pnt.x = pnt.x*image_width[ZOOM_IN]/image_width[ZOOM_OUT];
	new_pnt.x = pnt.x*image_width[ZOOM_IN]/500;
	new_pnt.y = pnt.y*image_height[ZOOM_IN]/image_height[ZOOM_OUT];
	return new_pnt;
}
