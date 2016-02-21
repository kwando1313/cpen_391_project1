#ifndef IMAGE_H_
#define IMAGE_H_

#include "Directions.h"

#define ZOOM_IN 0
#define ZOOM_OUT 1

int zoom_level;

// Store the 8bit values of the colours for each pixel.
char** image_pixels[2]; //[zoom_level][bmpWidth][bmpHeight]
int image_width[2];
int image_height[2];

void load_image(char* filename);
void move_img (Direction direction);
void draw_image(Point topLeft, int xstart, int ystart);

#endif /* IMAGE_H_ */
