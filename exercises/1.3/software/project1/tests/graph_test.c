#include "graph.h"

int graph_test(void){

	printf("Starting graph tests...");
	graph* g = init_graph(10);

	for (int x = 0; x < 100; x++){
		vertex* v = init_vertex(x, x, x, "TEST", x, x);
		int id = add_vertex(g, v);
		vertex* v2 = get_vertex(g, id);
		if (v->id != v2->id){
			printf("\nTest failed: Vertex ids do not match.");
			return -1;
		}
	}

	for (int x = 0; x < 50; x++){
		vertex* v1 = get_vertex(g, 2*x);
		vertex* v2 = get_vertex(g, (2*x) + 1);
		cost c = {1};
		add_edge(g, v1->id, v2->id, c);
		if (!vertex_has_edge(v1, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (!vertex_has_edge(v2, v1->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (!graph_has_edge(g, v1->id, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if(!remove_edge(g, v1->id, v2->id)){
			printf("\nTest failed: Remove edge didn't work.");
			return -1;
		}
		if (vertex_has_edge(v1, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (vertex_has_edge(v2, v1->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (graph_has_edge(g, v1->id, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}

	}
	destroy_graph(g);

	graph* g2 = init_graph(100);

	for (int x = 0; x < 100; x++){
		vertex* v = init_vertex(x, x, x, "TEST", x, x);
		int id = add_vertex(g, v);
		vertex* v2 = get_vertex(g, id);
		if (v->id != v2->id){
			printf("\nTest failed: Vertex ids do not match.");
			return -1;
		}
	}

	for (int x = 0; x < 50; x++){
		vertex* v1 = get_vertex(g, 2*x);
		vertex* v2 = get_vertex(g, (2*x) + 1);
		cost c = {1};
		add_edge(g, v1->id, v2->id, c);
		if (!vertex_has_edge(v1, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (!vertex_has_edge(v2, v1->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (!graph_has_edge(g, v1->id, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if(!remove_edge(g, v1->id, v2->id)){
			printf("\nTest failed: Remove edge didn't work.");
			return -1;
		}
		if (vertex_has_edge(v1, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (vertex_has_edge(v2, v1->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (graph_has_edge(g, v1->id, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
	}

	printf("\nAll tests passed!");
	return 0;
}
