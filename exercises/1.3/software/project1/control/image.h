#ifndef IMAGE_H_
#define IMAGE_H_

#include "Directions.h"

/*
 * 	DISPLAY_HEIGHT 	: Height of the box we print our image.
 * 	DISPLAY_WIDTH 	: Width of the box we print our image.
 * 	COLOURTABLESIZE : size of colour table containing 256 colours (with BGRA fields)
 * 	SHIFT			: how much picture shifts on each
 */
#define DISPLAY_HEIGHT	480
#define DISPLAY_WIDTH 	500
#define COLOURTABLESIZE 1024
#define SHIFT 30

#define ZOOM_IN 0
#define ZOOM_OUT 1

int zoom_level;

// Store the 8bit values of the colours for each pixel.
char** image_pixels[2]; //[zoom_level][bmpWidth][bmpHeight]
int image_width[2];
int image_height[2];

void load_image(char* filename);
void move_img (Direction direction);
void draw_image(Point start);

#endif /* IMAGE_H_ */
