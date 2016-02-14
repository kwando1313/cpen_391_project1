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
//
//	print_path_console(graph, 21, 12);
//	print_path_console(graph, 8, 19);
//	print_path_console(graph, 15, 6);
	//correct path is 15->17->5->6 total cost = 374
	//incorrect path is 15->9->6 total cost = 433

	destroy_graph(graph);

	printf("\n\nend\n");

	return 0;
}
