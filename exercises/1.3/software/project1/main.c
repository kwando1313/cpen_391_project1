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

	for(int i = 0; i<50; i++){
		int x = rand() % 22;
		int y = rand() % 22;
		print_path_console(graph, x, y);
	}
	print_path_console(graph, 9, 13);
	destroy_graph(graph);
	printf("destroyed graph\n");
//
//	clear_screen(WHITE);
//	Point point1 = {100, 100};
//	draw_keyboard(point1, 20);

	printf("\n\nend\n");

	return 0;
}
