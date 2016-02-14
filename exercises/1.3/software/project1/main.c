#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"

int main(void) {
	printf("start\n\n");

	graph* graph = create_test_graph();
	printf("created graph\n");

//	for(int i = 0; i<50; i++){
//		int x = rand() % 22;
//		int y = rand() % 22;
//		print_path_console(graph, x, y);
//	}

	print_path_console(graph, 21, 12);
	print_path_console(graph, 20, 8);
	print_path_console(graph, 15, 6);


	destroy_graph(graph);
	printf("destroyed graph\n");
	load_graph("SAMPLE.TXT");
	clear_screen(WHITE);
	Point point1 = {100, 100};
	draw_keyboard(point1, 60);

	printf("\n\nend\n");

	return 0;
}
