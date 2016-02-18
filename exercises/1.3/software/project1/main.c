#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "image.h"

int main(void) {
	clear_screen(255);
	//init_control();
	Point x = {0,0};

	//load_draw_image(x, 0, 0, "ubcnew.bmp");
	load_draw_image(x, 0, 0, "ubcnew.bmp");

	printf("\n\nend\n");
	return 0;
}
