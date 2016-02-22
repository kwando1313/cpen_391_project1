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

//Text box is left aligned and has text wrapping
void draw_text_box(Point topLeft, int width, int height, int borderWidth,
		int borderColour, int fillColour, int textColour, char* text, int fontSize){
	Point topRight = {topLeft.x + width, topLeft.y};
	Point bottomLeft = {topLeft.x, topLeft.y + height};
	Point bottomRight = {topLeft.x + width, topLeft.y + height};

	draw_filled_rectangle_border(topLeft, topRight, bottomLeft, bottomRight, fillColour, borderColour, borderWidth);
	int initialX = topLeft.x + 10; //give 10 pixels margin
	int initialY = topLeft.y + 10; //May make this an adjustable variable

	int fontSizePixelsWidth = (fontSize == MEDIUM ? 10 : 5);
	int fontSizePixelsHeight = (fontSize == MEDIUM ? 14 : 7);

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
	draw_text_box(point8, 300, 200, 1, BLACK, WHITE, BLACK, text, SMALL);

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
		draw_button(leftCorner, size, size, 1, BLACK, WHITE, BLACK, c, MEDIUM);
		leftCorner.x += size;
		x++;
	}
	draw_button(leftCorner, size, size, 1, BLACK, WHITE, BLACK, "<-", MEDIUM);
	x = 0;
	leftCorner.x = initialLeftCorner.x;
	leftCorner.y = initialLeftCorner.y + size;
	while(homeRow[x] != '\0'){
		char* c = "A";
		strncpy(c, &homeRow[x], 1);
		draw_button(leftCorner, size, size, 1, BLACK, WHITE, BLACK, c, MEDIUM);
		leftCorner.x += size;
		x++;
	}
	draw_button(leftCorner, 2*size, size, 1, BLACK, WHITE, BLACK, "ENTER", MEDIUM);
	leftCorner.x = initialLeftCorner.x;
	leftCorner.y = initialLeftCorner.y + 2*size;
	x = 0;
	while(bottomRow[x] != '\0'){
		char* c = "A";
		strncpy(c, &bottomRow[x], 1);
		draw_button(leftCorner, size, size, 1, BLACK, WHITE, BLACK, c, MEDIUM);
		leftCorner.x += size;
		x++;
	}
	draw_button(leftCorner, 2*size, size, 1, BLACK, WHITE, BLACK, "SPACE", MEDIUM);
	leftCorner.x += 2*size;
	draw_button(leftCorner, 2*size, size, 1, BLACK, WHITE, BLACK, "BACK", MEDIUM);
	return;
}

// Initialises the RHS of the screen (i.e everything but the map)
void init_screen(){
		clear_screen(WHITE);

		Point point6 = {500, 380};
		Point point7 = {650, 380}; //Adjust these to fit within the margins...
		Point point8 = {500, 330};
		Point point9 = {500, 200};

		char* firstTextArray[] = {"Info", "Photo", ""};
		char* secondTextArray[] = {"Directions", "About", ""};
		char* thirdTextArray[] = {"Search", ""};
		char* fourthTextArray[] = {" ", ""};

		about_screen();

		draw_menu(point6, 150, 50, 1, BLACK, WHITE, BLACK, SMALL, firstTextArray);

		draw_menu(point7, 150, 50, 1, BLACK, WHITE, BLACK, SMALL, secondTextArray);

		draw_menu(point8, 300, 50, 1 , BLACK, WHITE, BLACK, SMALL, thirdTextArray);

		draw_menu(point9, 300, 130, 1 , BLACK, WHITE, BLACK, SMALL, fourthTextArray);

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

void photo_screen(){
//	char* name = "PIC.BMP";
//	Point point = {500, 0};
//	load_image(point, name, 330, 300);
	draw_information_box("BUILDING PHOTO");
}

// draw the pop up keyboard on the LHS of the screen
void pop_screen(){
	draw_information_box("ENTER YOUR SEARCH!");

	Point p = {30, 330};
	Point p1 = {0, 300};
	Point p2 = {0, 230};
	char* t[] = {" ", ""};

	//bounded in (0-500, 300-480)
	draw_menu(p1, 500, 180, 2 , BLACK, WHITE, BLACK, SMALL, t);
	//bounded in (0-500, 230-300)
	draw_menu(p2, 500, 70, 2 , BLACK, WHITE, BLACK, SMALL, t);
	//bounded in (30-470, 330-450)
	draw_keyboard(p, 40);
}

// draw the names matched with the query string and highlight the current chosen entry
void match_screen(int sel, int mn_count){
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

void draw_arrow(Point topLeft, int width, int height, int borderWidth, int borderColour, int fillColour, Direction direction){
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

	draw_arrow(LPOINT, 50, 50, 1, BLACK, WHITE, LEFT);

	draw_arrow(RPOINT, 50, 50, 1, BLACK, WHITE, RIGHT);

	draw_arrow(UPOINT, 50, 50, 1, BLACK, WHITE, UP);

	draw_arrow(DPOINT, 50, 50, 1, BLACK, WHITE, DOWN);
}
