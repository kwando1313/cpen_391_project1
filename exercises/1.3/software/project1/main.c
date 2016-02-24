#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "gps.h"

int main(void) {
	init_control();
	load_from_sd();
	//printf("I finished loading!");
	s_listen();
//	draw_graph_path(full_map_graph, 0, 36, false, RED);
//	usleep(1000000);
//	draw_graph_path(full_map_graph, 6, 39, false, BLUE);
//	usleep(1000000);
//	draw_graph_path(full_map_graph, 8, 62, false, GREEN);

	printf("\nDONE\n");
	return 0;
}
