#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"

int main(void) {
//	init_control();
//
//	listen();

	printf("start\n\n");

	cost default_cost = {0};
	graph* graph = init_graph(5);

	vertex v0 = init_vertex(5, 5, 0, "v0", 5, 5);
	vertex v1 = init_vertex(50, 400, 0, "v1", 50, 400);
	vertex v2 = init_vertex(10000, 10000, 0, "v2", 10000, 10000);
	vertex v3 = init_vertex(200, 200, 0, "v3", 200, 200);
	vertex v4 = init_vertex(300, 300, 0, "v4", 300, 300);
	int v0id = add_vertex(graph, v0);
	int v1id = add_vertex(graph, v1);
	int v2id = add_vertex(graph, v2);
	int v3id = add_vertex(graph, v3);
	int v4id = add_vertex(graph, v4);

	add_edge(graph, v0id, v2id, default_cost);
	add_edge(graph, v2id, v3id, default_cost);
	add_edge(graph, v3id, v4id, default_cost);
	add_edge(graph, v1id, v4id, default_cost);
	add_edge(graph, v0id, v1id, default_cost);

	path_points* path = get_path_points(graph, v0id, v3id);
	for(int i = 0; i < path->actual_size; i++){
		printf("x: %d  y:  %d\n", path->ordered_point_arr[i].x, path->ordered_point_arr[i].y);
	}
	destroy_path_points(path);

	printf("\n\nend\n");

	return 0;
}
