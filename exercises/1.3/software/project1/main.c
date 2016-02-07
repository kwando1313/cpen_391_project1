// The following lines are for testing the SD Card, hence why they are commented out for now.

#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
int main(void) {
	printf("start\n\n");

	Point topLeft = {0,0};
	clear_screen(WHITE);
	char* name = "UBC.BMP";
	load_image(topLeft, name);//, name, 459, 500);

	init_screen();
	init_control();
	listen();

	printf("\n\nend\n");

	return 0;
}
