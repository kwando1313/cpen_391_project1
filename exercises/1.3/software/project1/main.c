#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "gps.h"

#define push_buttons123 (volatile int *) 0x80001060

int button_value;
int old_button;

int main(void) {
	init_control();
	//read_gps();
	load_from_sd();
	//do_dir();
	s_listen();

	//draw_graph_path(full_map_graph, 5, 113, true, RED);
	//find_range_of_graph(full_map_graph, 5, 113, true);

	//draw_graph_path(full_map_graph, 1, 194, false, BLUE);
	//find_range_of_graph(full_map_graph, 1, 194, false);

	//draw_graph_path(full_map_graph, 15, 46, false, YELLOW);
	//find_range_of_graph(full_map_graph, 15, 46, false);
	//draw_graph_path(full_map_graph, 58, 113, false, BLUE);
//	path_points* points = get_path_points(full_map_graph, 58, 113, true);
//
//	for (int x = 0; x < points->actual_size; x++){
//		printf("%d, %d\n", points->ordered_point_arr[x].x, points->ordered_point_arr[x].y);
//	}
//
//	draw_path(points->ordered_point_arr, points->actual_size, RED);

	printf("\nDONE\n");
	return 0;
}
