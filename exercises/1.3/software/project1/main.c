#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"

int main(void) {
	printf("start\n\n");

//	for(int i = 0; i<50; i++){
//		graph* graph = create_test_graph();
//		printf("created graph\n");
//		destroy_graph(graph);
//		printf("destroyed graph\n");
//	}
//
//	printf("\n\nend\n");

	init_control();
	pop_screen();

//	clear_screen(255);
//	Point x = {0,0};
//	load_image(x, "WTF.BMP");
//
//	printf("\n\nend\n");

	return 0;
}
