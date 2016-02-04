#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
	printf("start\n\n");

	cost default_cost = {1};
	graph* graph = init_graph(5);

	vertex v0 = init_vertex(5, 5, 0, "v0", 5, 5);
	vertex v1 = init_vertex(50, 400, 0, "v1", 50, 400);
	vertex v2 = init_vertex(100, 100, 0, "v2", 100, 100);
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

//	print_path(graph, v0id, v3id);
//	print_path(graph, v0id, v2id);
//	print_path(graph, v0id, v3id);
	print_path(graph, v3id, v1id);

	printf("\n\nend\n");
	return 0;
}
