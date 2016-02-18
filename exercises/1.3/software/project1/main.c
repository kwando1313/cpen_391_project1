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
	Point y = {400, 0};

	//load_draw_image(x, 0, 0, "zoomout.bmp"); //Zoomed out map image.
	load_draw_image(x, 200, 0, "ubcfull3.bmp"); //This is the full size one that we can move around on.


	//load_image("ubcfull3.bmp");
	//load_image("ubcfull3.bmp");

	printf("\n\nend\n");
	return 0;
}
