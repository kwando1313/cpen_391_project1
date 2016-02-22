#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "gps.h"

int main(void) {
	printf("start\n\n");

// ADD ALL TESTS TO A TEST DIRECTORY
	init_control();
	Point p = {0,0};
	//load_image(p, "ubcfull3.BMP");
	//draw_image(p, p.x, p.y);
	for(int i = 0; i < N_KEYS; i++){
		printf("%c: ",keyboard[i].key);
		printf("%i - ",keyboard[i].left);
		printf("%i, ",keyboard[i].right);
		printf("%i - ",keyboard[i].top);
		printf("%i\n",keyboard[i].bottom);
	}
	s_listen();


	printf("\n\nend\n");
	return 0;
}
