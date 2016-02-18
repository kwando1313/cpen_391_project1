#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"

int main(void) {
	printf("start\n\n");
	clear_screen(255);
	init_control();
/*
	for(int i = 0; i < N_KEYS; i++){
			printf("%c: ",keyboard[i].key);
			printf("%i - ",keyboard[i].left);
			printf("%i, ",keyboard[i].right);
			printf("%i - ",keyboard[i].top);
			printf("%i\n",keyboard[i].bottom);
		}
	s_listen();
*/

	Point x = {0,0};
	load_image(x, "ubcfull3.BMP");
	//load_image(x, "ubc1.BMP");
	draw_img(x, x.x, x.y);
	s_listen();
	printf("\n\nend\n");

	return 0;
}
