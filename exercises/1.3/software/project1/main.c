
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"

int main(void) {
	printf("start\n\n");
	clear_screen(BLACK);
	test_graphics();
	//load_graph("SAMPLE.TXT");

	printf("\n\nend\n");

	return 0;
}
