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
//	clear_screen(BLACK);
//	for(int i = 0; i<50; i++){
//		graph* graph = create_test_graph();
//		draw_graph(graph, YELLOW, RED);
//		int x = rand()%22;
//		int y = rand()%22;
//		path_points* path = get_path_points(graph, x, y);
//		printf("%d: got path %d %d\n", i, x, y);
//		//destroy_graph(graph);
//		//graph = create_test_graph();
//	}
	printf("\n\nend\n");

	return 0;
}
