// The following lines are for testing the SD Card, hence why they are commented out for now.

#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
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
	printf("\n\nend\n");

	return 0;
}
