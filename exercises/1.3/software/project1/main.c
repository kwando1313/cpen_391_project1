#include <stdio.h>
#include <stdlib.h>

int main(void) {




	clear_screen(WHITE);

	Point point4 = {100,0};

	Point point5 = {50, 300};

	draw_button(point4, 300, 100, 1, BLACK, LIME, BLACK, "Longer text", SMALL);
	draw_button(point5, 200, 100, 1, BLACK, BLUE, RED, "What happens when I have text overflow?", MEDIUM);

	clear_screen(WHITE);

	Point point6 = {400, 330};
	Point point7 = {600, 330}; //Adjust these to fit within the margins...
	Point point8 = {400, 0};
	Point point9 = {400, 330};
	Point point10 = {800, 0};
	Point point11 = {800, 330};

	char* firstTextArray[] = {"Info", "Photo", NULL};
	char* secondTextArray[] = {"Directions", "Back", NULL};

	draw_text_box(point8, 400, 330,1, BLACK, WHITE, BLACK, "Information about the building will go here...");

	draw_menu(point6, 200, 75, 1, BLACK, WHITE, BLACK, SMALL, firstTextArray);

	draw_menu(point7, 200, 75, 1, BLACK, WHITE, BLACK, SMALL, secondTextArray);


	printf("end\n");
	return 0;
}
