#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include <time.h>
#include "search.h"
#include "gps.h"
//#include "system.h"
//#include "sys/alt_irq.h"

int main(void) {
	printf("start\n\n");
	clear_screen(255);
	init_control();
	//alt_irq_register(TIMER_1_IRQ_INTERRUPT_CONTROLLER_ID, NULL, read_gps);

	Point x = {0,0};
	load_image(x, "zoomin.bmp", "zoomout.bmp");
	//draw_zoomout();	//set this up to be called by a button
	//draw_zoomin(x, x.x, x.y);
	s_listen();
	//read_gps();

	return 0;
}
