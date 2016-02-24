#include "graph.h"

int graph_test(void){

	printf("Starting graph tests...");
	graph* g = init_graph(10);

	for (int x = 0; x < 100; x++){
		vertex* v = init_vertex(x, x, x, "TEST", x, x, x, x);
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
		bool c = true;
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
		vertex* v = init_vertex(x, x, x, "TEST", x, x, x, x);
		int id = add_vertex(g2, v);
		vertex* v2 = get_vertex(g2, id);
		if (v->id != v2->id){
			printf("\nTest failed: Vertex ids do not match.");
			return -1;
		}
	}

	for (int x = 0; x < 50; x++){
		vertex* v1 = get_vertex(g2, 2*x);
		vertex* v2 = get_vertex(g2, (2*x) + 1);
		bool c = true;
		add_edge(g2, v1->id, v2->id, c);
		if (!vertex_has_edge(v1, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (!vertex_has_edge(v2, v1->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if (!graph_has_edge(g2, v1->id, v2->id)){
			printf("\nTest failed: Vertex does not have edge.");
			return -1;
		}
		if(!remove_edge(g2, v1->id, v2->id)){
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

graph* create_test_graph(){
	bool road = true;
	graph* graph = init_graph(DEFAULT_GRAPH_SIZE);

	int v0id = add_vertex(graph, init_vertex(5, 5, 0, "v0", 3, 460, 3, 460));
	int v1id = add_vertex(graph, init_vertex(50, 400, 0, "v1", 10, 285, 10, 285));
	int v2id = add_vertex(graph, init_vertex(10000, 10000, 0, "v2", 26, 217, 26, 217));
	int v3id = add_vertex(graph, init_vertex(200, 200, 0, "v3", 51, 177, 51, 177));
	int v4id = add_vertex(graph, init_vertex(300, 300, 0, "v4", 107, 140, 107, 140));
	int v5id = add_vertex(graph, init_vertex(300, 300, 0, "v5", 181, 124, 181, 124));
	add_edge(graph, v0id, v1id, road);
	add_edge(graph, v1id, v2id, road);
	add_edge(graph, v2id, v3id, road);
	add_edge(graph, v3id, v4id, road);
	add_edge(graph, v4id, v5id, road);

	//going down
	int v6id = add_vertex(graph, init_vertex(5, 5, 0, "v6", 180, 280, 180, 280));
	int v7id = add_vertex(graph, init_vertex(50, 400, 0, "v7", 104, 281, 104, 281));
	int v8id = add_vertex(graph, init_vertex(10000, 10000, 0, "v8", 104, 472, 104, 472));
	int v9id = add_vertex(graph, init_vertex(200, 200, 0, "v9", 180, 478, 180, 478));
	add_edge(graph, v5id, v6id, road);
	add_edge(graph, v6id, v7id, road);
	add_edge(graph, v7id, v8id, road);
	add_edge(graph, v6id, v9id, road);

	//back to intersection
	//going right along top road
	int v10id = add_vertex(graph, init_vertex(5, 5, 0, "v10id", 378, 114, 378, 114));
	int v11id = add_vertex(graph, init_vertex(50, 400, 0, "v11id", 242, 36, 242, 36));
	int v12id = add_vertex(graph, init_vertex(10000, 10000, 0, "v12id", 173, 78, 173, 78));
	int v13id = add_vertex(graph, init_vertex(200, 200, 0, "v13id", 460, 114, 460, 114));
	add_edge(graph, v5id, v10id, road);
	add_edge(graph, v10id, v11id, road);
	add_edge(graph, v11id, v12id, road);
	add_edge(graph, v10id, v13id, road);

	//going down
	int v14id = add_vertex(graph, init_vertex(200, 200, 0, "v14id", 459, 281, 459, 281));
	add_edge(graph, v13id, v14id, road);

	//going left
	int v15id = add_vertex(graph, init_vertex(200, 200, 0, "v15id", 303, 277, 303, 277));
	add_edge(graph, v14id, v15id, road);
	add_edge(graph, v15id, v9id, road);

	//going left
	int v16id = add_vertex(graph, init_vertex(200, 200, 0, "v16id", 218, 279, 218, 279));
	add_edge(graph, v16id, v15id, road);

	//going up
	int v17id = add_vertex(graph, init_vertex(200, 200, 0, "v17id", 303, 205, 303, 205));
	add_edge(graph, v15id, v17id, road);
	add_edge(graph, v17id, v5id, road);

	//going down
	int v18id = add_vertex(graph, init_vertex(5, 5, 0, "v18id", 303, 369, 303, 369));
	int v19id = add_vertex(graph, init_vertex(50, 400, 0, "v19id", 302, 462, 302, 462));
	int v20id = add_vertex(graph, init_vertex(10000, 10000, 0, "v20id", 459, 369, 459, 369));
	int v21id = add_vertex(graph, init_vertex(200, 200, 0, "v21id", 461, 460, 461, 460));
	add_edge(graph, v15id, v18id, road);
	add_edge(graph, v18id, v19id, road);
	add_edge(graph, v18id, v20id, road);
	add_edge(graph, v20id, v21id, road);
	add_edge(graph, v14id, v20id, road);

	return graph;
}
