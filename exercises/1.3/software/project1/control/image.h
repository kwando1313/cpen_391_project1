#ifndef IMAGE_H_
#define IMAGE_H_

void draw_image(Point topLeft, short file);//, int bmpWidth, int bmpHeight);
void load_image(Point bottomLeft, char* filename);//, char* filename, int bmpheight, int bmpwidth);

void get_header (short file);
void get_pixels (short file);
void draw_img (Point topLeft, short file, int xstart, int ystart);


#endif /* IMAGE_H_ */
