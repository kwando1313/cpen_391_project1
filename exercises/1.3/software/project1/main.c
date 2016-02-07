#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
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
