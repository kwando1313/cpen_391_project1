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

	s_listen();
//	draw_graph_path(full_map_graph, 0, 36, false, RED);
//	usleep(1000000);
//	draw_graph_path(full_map_graph, 6, 39, false, BLUE);
//	usleep(1000000);
//	draw_graph_path(full_map_graph, 8, 62, false, GREEN);

	printf("\nDONE\n");
	return 0;
}
