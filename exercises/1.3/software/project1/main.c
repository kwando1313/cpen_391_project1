#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"

int main(void) {
	printf("start\n\n");
	clear_screen(255);
	init_control();

	Point x = {0,0};
	//load_image(x, "ubcnew.BMP");
	load_image(x, "ubc1.BMP");
	Point printStart = ret_start_points ();
	printf ("%d, %d", printStart.x, printStart.y);
	draw_img(x, printStart.x, printStart.y);
	listen();
	printf("\n\nend\n");

	return 0;
}
