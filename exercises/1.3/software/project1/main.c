#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "menu.h"

int main(void) {
<<<<<<< e12a01364cef9f227ea5fdc6ff9c7a284f20e559



	clear_screen(WHITE);

	Point point4 = {100,0};

	Point point5 = {50, 300};

	draw_button(point4, 300, 100, 1, BLACK, LIME, BLACK, "Longer text", SMALL);
	draw_button(point5, 200, 100, 1, BLACK, BLUE, RED, "What happens when I have text overflow?", MEDIUM);

	clear_screen(WHITE);

	Point point6 = {0, 0};

	char* textArray[] = {"Item 1", "Longer Item", "Die the DEATH", "!!!!!!!!!", NULL};

	draw_menu(point6, 100, 50, 1, BLACK, LIME, BLACK, SMALL, textArray);

	draw_menu(point4, 100, 50, 3, BLUE, BLACK, WHITE, SMALL, textArray);

=======
	printf("start\n");
	test_graphics();
	//test_rs232();
>>>>>>> completed 1.7 demo
	printf("end\n");
	return 0;
}
