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
	usleep(100000);
	//do_draw_nodes();
	if (vertex_had_road_edge(full_map_graph, 99)){
		printf("HOW");
	}
//	load_and_draw_graph_path(full_map_graph, 55, 99, true, RED);
//
//	usleep(100000);
//	load_and_draw_graph_path(full_map_graph, 55, 99, true, BLUE);
//	usleep(100000);
//	load_and_draw_graph_path(full_map_graph, 55, 99, true, GREEN);
//	usleep(100000);
//	load_and_draw_graph_path(full_map_graph, 55, 99, true, RED);
	//do_dir();
//	usleep(1000000);
	//do_zoom();
//	usleep(1000000);
//	load_and_draw_graph_path(full_map_graph, 49, 46, false, RED);
//	usleep(1000000);
//	load_and_draw_graph_path(full_map_graph, 50, 48, false, BLUE);
//	usleep(1000000);
//	load_and_draw_graph_path(full_map_graph, 100, 39, false, YELLOW);
//	usleep(1000000);
//	load_and_draw_graph_path(full_map_graph, 50, 48, false, BLUE);
//	usleep(1000000);
//	load_and_draw_graph_path(full_map_graph, 0, 190, false, GREEN);
//	usleep(1000000);
//	load_and_draw_graph_path(full_map_graph, 50, 48, false, BLUE);
//	do_south();
//	usleep(1000000);
//	do_south();
//	usleep(1000000);
//	do_south();
//	usleep(1000000);
//	do_east();
//	usleep(1000000);
//	do_east();
//	usleep(1000000);
//	do_east();
//	usleep(1000000);
//	do_east();
//	usleep(1000000);
	//do_zoom();


	//usleep(10000);
	//do_zoom();
	//s_listen();
//	draw_graph_path(full_map_graph, 0, 36, false, RED);
//	usleep(1000000);
//	draw_graph_path(full_map_graph, 6, 39, false, BLUE);
//	usleep(1000000);
//	draw_graph_path(full_map_graph, 8, 62, false, GREEN);

	printf("\nDONE\n");
	return 0;
}
