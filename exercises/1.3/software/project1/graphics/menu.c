#include "misc_helpers.h"
#include "FontSize.h"
#include "menu.h"
#include "Colours.h"
#include "Directions.h"
#include <stdio.h>
#include <string.h>
#include <touchscreen.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "Directions.h"
#include "search.h"

/*	IMGHEIGHT 	: Full height of our BMP
 * 	IMGWIDTH 	: Full width of our BMP
 * 	BOXHEIGHT 	: Height of the box we print our image.
 * 	BOXWIDTH 	: Width of the box we print our image.
 * 	HEADERSIZE changes with type of BMP file
 * 	COLOURTABLESIZE = size of colour table containing 256 colours (with BGRA fields)
 */
#define IMGHEIGHT 	855
#define IMGWIDTH 	1256
#define BOXHEIGHT	480
#define BOXWIDTH 	500
#define HEADERSIZE 	54
#define COLOURTABLESIZE 1024
#define SHIFT 30


void draw_image_wrapper(Point topLeft, short file, int xstart, int ystart);
void read_bytes(char* str, int len, short file);
void draw_image_old(Point topLeft, short file);
int rgb_from_pixel_arr(char*** pixel, int x, int y);

// Store the integer values of the colours for each pixel.
int pixel[IMGHEIGHT][IMGWIDTH];
int xstart = 0, ystart = 0;
Point start = {0,0};
/*	Load image from SD Card.
 * 	SD Card must be formatted in FAT16 to work with DE2.
 * 	Length of filenames cannot be longer than 12 characters.
 * 	including file extension (i.e. "abcdefghi.bmp" is invalid.
 */
//void load_image(Point topLeft, char* filename){
//	bool found_file = false;
//
//	if (get_device_reference() == NULL || !alt_up_sd_card_is_Present() || !alt_up_sd_card_is_FAT16()){
//		printf("Can't find device, or device not configured properly\n");
//		return;
//	}
//
//	char filename_all_caps[strlen(filename)];
//	to_caps(filename, filename_all_caps);
//	char found_file_name[13];
//	if (alt_up_sd_card_find_first(".", found_file_name) != 0){
//		printf("Couldn't find root dir\n");
//		return;
//	}
//
//	do {
//		if (strcmp(found_file_name, filename_all_caps)== 0){
//			short int file = alt_up_sd_card_fopen(found_file_name, false);
//			if (file >= 0){
//				printf("found file %s in SD\n", filename_all_caps);
//				load_image_wrapper(file);
//				found_file = true; //want to close file, so use this rather than returning
//			}
//			alt_up_sd_card_fclose(file);
//		}
//	}while(!found_file && alt_up_sd_card_find_next(found_file_name) == 0);
//}

Point ret_start_points(void){
	Point ret = {xstart, ystart};
	return ret;
}

void load_image_wrapper(short file){
	get_header(file);
	get_pixels(file);
}

void draw_image_old(Point topLeft, short file){
	//setUpPallete(); //TODO doesn't need to be called more than once. Should be done in some general init() function
	char header;
	unsigned char height[4];
	unsigned char width[4];
	unsigned char buf[200];

	printf("Reading file...\n");
	//54

//	read_bytes(buf, 18, file);
//	read_bytes(width, 4, file);
//	read_bytes(height, 4, file);
//	read_bytes(buf, 28, file);

	int bmpWidth = *(int *) width;
	int bmpHeight = *(int *) height;
	//printf("%d", test);

	printf("\n");
	short data =0;

	char pixel[bmpHeight][bmpWidth][3];
	char B[bmpHeight][bmpWidth];
	char G[bmpHeight][bmpWidth];
	char R[bmpHeight][bmpWidth];

	for (int j = 0; j < bmpHeight; j++){
		for (int i = 0; i < bmpWidth; i++){
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

	for (int y = 0; y < bmpHeight; y++){
		for (int x = 0; x < bmpWidth; x++){
			int initialX = x;
			int rgb = rgb_from_pixel_arr(pixel, x, y);
			//int colour = getPalleteAddr(rgb);
			int curr_rgb = rgb;
			while(rgb == curr_rgb && x < bmpWidth){
				x++;
				curr_rgb = rgb_from_pixel_arr(pixel, x, y);
			}
			int colour = 1;
			HLine(topLeft.x + initialX, topLeft.y + bmpHeight-y, x - initialX, colour);
			//WriteAPixel(topLeft.x + x, topLeft.y + bmpHeight-y, colour);
			printf("rgb: %x\n", rgb);
			printf("write colour %d\n", colour);
		}
	}
}

int rgb_from_pixel_arr(char*** pixel, int x, int y){
	int rgb = (0xff & pixel[y][x][0]) << 16 | (0xff & pixel[y][x][1]) << 8 | (0xff & pixel[y][x][2]);
	return rgb;
}

/* Get header information.
 * Iterate and print bitmap file header + Windows Bitmap Info Header.
 * Iterate and do not print the colour table.
 */
//void get_header (short file){
//	char header;
//	for(int x=0 ; x < HEADERSIZE ; x++){
//		header=(unsigned char)(alt_up_sd_card_read(file));
//		printf ("%hhx ",header & 0xff);
//	}
//	printf ("\n");
//	for (int i = 0; i < COLOURTABLESIZE; i++){
//		alt_up_sd_card_read(file);
//	}
//}
///* Store pixel colours in 2-D array.
// */
//void get_pixels (short file){
//	for (int j = 0; j < IMGHEIGHT; j++){
//		for (int i = 0; i < IMGWIDTH; i++){
//			pixel[j][i] = alt_up_sd_card_read(file);
//		}
//	}
//}

/* Draw the pictures in the range we want.
 * We're picking the top left point to start from
 * but actually draw from the bottom left first.
 */
void draw_img (Point topLeft, int xstart, int ystart){
	for (int y = 0; y < BOXHEIGHT; y++){
		for (int x = 0; x < BOXWIDTH; x++){
			int colour = pixel[ystart + y][xstart + x];
			WriteAPixel(topLeft.x + x, topLeft.y + BOXHEIGHT-y, colour);
		}
	}
}
/*	Move the x and y start points according to button
 * 	Draw image again.
 * 	This code is written to not go past the edge of the image.
 */
void move_img (int direction){
	if (direction == UP){
		if (ystart > IMGHEIGHT - BOXHEIGHT - SHIFT)
			ystart = IMGHEIGHT - BOXHEIGHT;
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
		if (xstart > IMGWIDTH - BOXWIDTH - SHIFT)
			xstart = IMGWIDTH - BOXWIDTH;
		else xstart += SHIFT;
		printf ("RIGHT\n");
	}
	else if (direction == LEFT){
		if (xstart < SHIFT)
			xstart = 0;
		else xstart -= SHIFT;
		printf ("LEFT\n");
	}
	Point printStart = ret_start_points ();
	printf ("%d, %d", printStart.x, printStart.y);
	draw_img(start, printStart.x, printStart.y);
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
	//255 is WHITE
	draw_text_box(point8, 300, 200, 2, BLACK, 255, BLACK, text, SMALL);

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

	char topRow[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '\0'};
	char homeRow[] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '\0'};
	char bottomRow[] = {'Z', 'X', 'C', 'V', 'B', 'N', 'M', '\0'};

	int x = 0;
	Point initialLeftCorner = {leftCorner.x, leftCorner.y};
	while(topRow[x] != '\0'){
		char* c = "A";
		strncpy(c, &topRow[x], 1);
		//255 is WHITE
		draw_button(leftCorner, size, size, 1, BLACK, 255, BLACK, c, MEDIUM);
		leftCorner.x += size;
		x++;
	}
	draw_button(leftCorner, size, size, 1, BLACK, 255, BLACK, "<-", MEDIUM);
	x = 0;
	leftCorner.x = initialLeftCorner.x;
	leftCorner.y = initialLeftCorner.y + size;
	while(homeRow[x] != '\0'){
		char* c = "A";
		strncpy(c, &homeRow[x], 1);
		draw_button(leftCorner, size, size, 1, BLACK, 255, BLACK, c, MEDIUM);
		leftCorner.x += size;
		x++;
	}
	draw_button(leftCorner, 2*size, size, 1, BLACK, 255, BLACK, "ENTER", MEDIUM);
	leftCorner.x = initialLeftCorner.x;
	leftCorner.y = initialLeftCorner.y + 2*size;
	x = 0;
	while(bottomRow[x] != '\0'){
		char* c = "A";
		strncpy(c, &bottomRow[x], 1);
		draw_button(leftCorner, size, size, 1, BLACK, 255, BLACK, c, MEDIUM);
		leftCorner.x += size;
		x++;
	}
	draw_button(leftCorner, 2*size, size, 1, BLACK, 255, BLACK, "SPACE", MEDIUM);
	leftCorner.x += 2*size;
	draw_button(leftCorner, 2*size, size, 1, BLACK, 255, BLACK, "BACK", MEDIUM);
	return;
}

// Initialises the RHS of the screen (i.e everything but the map)
void init_screen(){
		clear_screen(255); // 255 is WHITE

		Point point6 = {500, 380};
		Point point7 = {650, 380}; //Adjust these to fit within the margins...
		Point point8 = {500, 330};
		Point point9 = {500, 200};

		char* firstTextArray[] = {"Info", "Zoom", ""};
		char* secondTextArray[] = {"Directions", "About", ""};
		char* thirdTextArray[] = {"Search", ""};
		char* fourthTextArray[] = {" ", ""};

		about_screen();

		draw_menu(point6, 150, 50, 2, BLACK, 255, BLACK, SMALL, firstTextArray);

		draw_menu(point7, 150, 50, 2, BLACK, 255, BLACK, SMALL, secondTextArray);

		draw_menu(point8, 300, 50, 2 , BLACK, 255, BLACK, SMALL, thirdTextArray);

		draw_menu(point9, 300, 130, 2 , BLACK, 255, BLACK, SMALL, fourthTextArray);

		draw_arrows();

}

void about_screen(){
	draw_information_box("Pathfinding Map (CPEN 391 Team 22)\nAlex Charles\nAngela Cho\nCaleb Kwan\nWilliam Tang\n\nWelcome to [insert name here].\n Below this menu you may:\nSearch for directions\nGet directions between two points\nOther bs, let's write this shit at the end");
}

void info_screen(){
	draw_information_box("BUILDING INFO");
}

void directions_screen(){
	draw_information_box("DIRECTIONS");
}

void zoom_screen(){
//	char* name = "PIC.BMP";
//	Point point = {500, 0};
//	load_image(point, name, 330, 300);
	draw_information_box("ZOOMING");
}

// draw the pop up keyboard on the LHS of the screen
void pop_screen(){
	draw_information_box("ENTER YOUR SEARCH!");

	Point p = {30, 330};
	Point p1 = {0, 300};
	Point p2 = {0, 230};
	char* t[] = {" ", ""};

	//bounded in (0-500, 300-480)
	draw_menu(p1, 500, 180, 2 , BLACK, 255, BLACK, SMALL, t);
	//bounded in (0-500, 230-300)
	draw_menu(p2, 500, 70, 2 , BLACK, 255, BLACK, SMALL, t);
	//bounded in (30-470, 330-450)
	draw_keyboard(p, 40);
}

// draw the names matched with the query string and highlight the current chosen entry
void match_screen(int sel, int mn_count){
	if(mn_count == 0){
		draw_information_box("NO SEARCH RESULTS FOUND");
		return;
	}

	char* t[2];
	Point p;

	int incr = 200 / mn_count;
	name_list* nl = matched_names.head;

	for(int i = 0; i < mn_count; i++){
		p.x = 500;
		p.y = i*incr;

		t[0] = nl->name;
		t[1] = "";

		nl = nl->next;

		if(i != (sel-1))
			draw_menu(p, 300, incr, 2 , BLACK, 255, BLACK, SMALL, t);
		else if(i == (sel-1))
			draw_menu(p, 300, incr, 2 , 255, BLACK, 255, SMALL, t); // highlighted entry (i.e invert colors)
	}
}

// redraw the map when we leave pop_screen
void map_screen(){
	// TODO:

}

void draw_arrow(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, int direction){
	Point topRight = {topLeft.x + width, topLeft.y};
	Point bottomLeft = {topLeft.x, topLeft.y + height};
	Point bottomRight = {topLeft.x + width, topLeft.y + height};
	draw_filled_rectangle_border(topLeft, topRight, bottomLeft, bottomRight, fillColour, borderColour, borderWidth);

	Point cornerOne = {0, 0};
	Point cornerTwo = {0, 0};
	Point cornerThree = {0, 0};

	if (direction == UP){
		cornerOne.x = topLeft.x + width/2;
		cornerOne.y = topLeft.y + height/3;
		cornerTwo.x = topLeft.x + width/3;
		cornerTwo.y = topLeft.y + 2*height/3;
		cornerThree.x = topLeft.x + 2*width/3;
		cornerThree.y = topLeft.y + 2*height/3;
	}
	else if (direction == RIGHT){
		cornerOne.x = topLeft.x + width/3;
		cornerOne.y = topLeft.y + height/3;
		cornerTwo.x = topLeft.x + width/3;
		cornerTwo.y =  topLeft.y + 2*height/3;
		cornerThree.x = topLeft.x + 2*width/3;
		cornerThree.y = topLeft.y + height/2;
	}
	else if (direction == DOWN){

		cornerOne.x = topLeft.x + width/3;
		cornerOne.y = topLeft.y + height/3;
		cornerTwo.x = topLeft.x + 2*width/3;
		cornerTwo.y =  topLeft.y + height/3;
		cornerThree.x = topLeft.x + width/2;
		cornerThree.y = topLeft.y + 2*height/3;
	}
	else{

		cornerOne.x = topLeft.x + width/3;
		cornerOne.y = topLeft.y + height/2;
		cornerTwo.x = topLeft.x + 2*width/3;
		cornerTwo.y =  topLeft.y + height/3;
		cornerThree.x = topLeft.x + 2*width/3;
		cornerThree.y = topLeft.y + 2*height/3;
	}

	draw_filled_triangle(cornerOne, cornerTwo, cornerThree, BLACK);
}

void draw_arrows(){
	// bounded in (500-800, 200-330); midway pts: (650, 275)
	Point LPOINT = {550, 240};
	Point RPOINT = {700, 240};
	Point UPOINT = {625, 210};
	Point DPOINT = {625, 270};

	// 255 is WHITE
	draw_arrow(LPOINT, 50, 50, 1, BLACK, 255, LEFT);

	draw_arrow(RPOINT, 50, 50, 1, BLACK, 255, RIGHT);

	draw_arrow(UPOINT, 50, 50, 1, BLACK, 255, UP);

	draw_arrow(DPOINT, 50, 50, 1, BLACK, 255, DOWN);
}
