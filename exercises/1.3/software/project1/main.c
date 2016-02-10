// The following lines are for testing the SD Card, hence why they are commented out for now.

#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
int main(void) {
	printf("start\n\n");


	for(int i = 0; i<50; i++){
		graph* graph = create_test_graph();
		printf("created graph\n");
		destroy_graph(graph);
		printf("destroyed graph\n");
	}

	printf("\n\nend\n");

	return 0;
}
