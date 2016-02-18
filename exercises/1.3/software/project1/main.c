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

// TEST KEYBOARD PRESSING -- KEEP THIS FOR NOW
//	init_control();
//	for(int i = 0; i < N_KEYS; i++){
//		printf("%c: ",keyboard[i].key);
//		printf("%i - ",keyboard[i].left);
//		printf("%i, ",keyboard[i].right);
//		printf("%i - ",keyboard[i].top);
//		printf("%i\n",keyboard[i].bottom);
//	}
//	s_listen();


// TEST DISPLAYING SEARCH QUERY -- KEEP THIS FOR NOW
//  init_control();
//	pop_screen();
//	reset_query();
//
//	keyboard[4].kb_p(keyboard[4].key); //T
//	keyboard[2].kb_p(keyboard[2].key); //E
//	keyboard[12].kb_p(keyboard[12].key); //S
//	keyboard[1].kb_p(keyboard[0].key); //Q
//	DEL_BUTT.p();
//	keyboard[4].kb_p(keyboard[4].key); //T
//	SPACE_BUTT.kb_p(SPACE_BUTT.key); // " "
//	keyboard[7].kb_p(keyboard[7].key); // I
//
//	reset_query();
//
//	keyboard[16].kb_p(keyboard[16].key); //H
//	keyboard[19].kb_p(keyboard[19].key); //L
//	keyboard[9].kb_p(keyboard[9].key); //P
//	keyboard[24].kb_p(keyboard[24].key); //V


// 	ANGELA'S MAIN TESTING -- KEEP THIS FOR NOW I THINK
//	clear_screen(255);
//	init_control();

//	Point x = {0,0};
//	load_image(x, "ubcfull3.BMP");
//	//load_image(x, "ubc1.BMP");
//	draw_img(x, x.x, x.y);
//	s_listen();

//	read_gps();

//	printf("\n\nend\n");
	return 0;
}
