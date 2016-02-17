#ifndef IMAGE_H_
#define IMAGE_H_

void load_draw_image(Point topLeft, int xstart, int ystart, char* filename);

void load_image(char* filename);//, char* filename, int bmpheight, int bmpwidth);

void get_header(short file);
void get_pixels(short file);
void draw_image(Point topLeft, int xstart, int ystart);


#endif /* IMAGE_H_ */
