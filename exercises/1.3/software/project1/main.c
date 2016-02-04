#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"

int main(void) {
	printf("start\n\n");
	clear_screen(BLACK);

	cost default_cost = {0};
	graph* graph = init_graph(30);


	int v0id = add_vertex(graph, init_vertex(5, 5, 0, "v0", 4, 425));
	int v1id = add_vertex(graph, init_vertex(50, 400, 0, "v1", 6, 260));
	int v2id = add_vertex(graph, init_vertex(10000, 10000, 0, "v2", 15, 214));
	int v3id = add_vertex(graph, init_vertex(200, 200, 0, "v3", 35, 178));
	int v4id = add_vertex(graph, init_vertex(300, 300, 0, "v4", 105, 132));
	int v5id = add_vertex(graph, init_vertex(300, 300, 0, "v5", 181, 92));
	add_edge(graph, v0id, v1id, default_cost);
	add_edge(graph, v1id, v2id, default_cost);
	add_edge(graph, v2id, v3id, default_cost);
	add_edge(graph, v3id, v4id, default_cost);
	add_edge(graph, v4id, v5id, default_cost);

	//going down
	int v6id = add_vertex(graph, init_vertex(5, 5, 0, "v6", 179, 249));
	int v7id = add_vertex(graph, init_vertex(50, 400, 0, "v7", 103, 251));
	int v8id = add_vertex(graph, init_vertex(10000, 10000, 0, "v8", 105, 428));
	int v9id = add_vertex(graph, init_vertex(200, 200, 0, "v9", 181, 424));
	add_edge(graph, v5id, v6id, default_cost);
	add_edge(graph, v6id, v7id, default_cost);
	add_edge(graph, v7id, v8id, default_cost);
	add_edge(graph, v6id, v9id, default_cost);

	//back to intersection
	//going right along top road
	int v10id = add_vertex(graph, init_vertex(5, 5, 0, "v10id", 394, 75));
	int v11id = add_vertex(graph, init_vertex(50, 400, 0, "v11id", 272, 8));
	int v12id = add_vertex(graph, init_vertex(10000, 10000, 0, "v12id", 172, 46));
	int v13id = add_vertex(graph, init_vertex(200, 200, 0, "v13id", 455, 75));
	add_edge(graph, v5id, v10id, default_cost);
	add_edge(graph, v10id, v11id, default_cost);
	add_edge(graph, v11id, v12id, default_cost);
	add_edge(graph, v10id, v13id, default_cost);

	//going down
	int v14id = add_vertex(graph, init_vertex(200, 200, 0, "v14id", 455, 249));
	add_edge(graph, v13id, v14id, default_cost);

	//going left
	int v15id = add_vertex(graph, init_vertex(200, 200, 0, "v15id", 305, 248));
	add_edge(graph, v14id, v15id, default_cost);
	add_edge(graph, v15id, v9id, default_cost);

	//going left
	int v16id = add_vertex(graph, init_vertex(200, 200, 0, "v16id", 226, 249));
	add_edge(graph, v16id, v15id, default_cost);

	//going up
	int v17id = add_vertex(graph, init_vertex(200, 200, 0, "v17id", 306, 160));
	add_edge(graph, v15id, v17id, default_cost);
	add_edge(graph, v17id, v5id, default_cost);

	//going down
	int v18id = add_vertex(graph, init_vertex(5, 5, 0, "v18id", 306, 346));
	int v19id = add_vertex(graph, init_vertex(50, 400, 0, "v19id", 306, 432));
	int v20id = add_vertex(graph, init_vertex(10000, 10000, 0, "v20id", 456, 347));
	int v21id = add_vertex(graph, init_vertex(200, 200, 0, "v21id", 456, 436));
	add_edge(graph, v15id, v18id, default_cost);
	add_edge(graph, v18id, v19id, default_cost);
	add_edge(graph, v18id, v20id, default_cost);
	add_edge(graph, v20id, v21id, default_cost);
	add_edge(graph, v14id, v20id, default_cost);

	for(int i = 0; i<graph->num_vertices; i++) {
		vertex* v = get_vertex(graph, i);
		WriteAPixel(v->x, v->y, CYAN);
		adjacencyList* adjList = v->adjList;
		int num_edges = adjList->num_neighbours;
		for (int j = 0; j<num_edges; j++) {
			vertex* w = get_vertex(graph, adjList->neighbours[j]);
			Line(v->x, v->y, w->x, w->y, RED);
		}
	}

//	path_points* path = get_path_points(graph, v0id, v3id);
//	for(int i = 0; i < path->actual_size; i++){
//		printf("x: %d  y:  %d\n", path->ordered_point_arr[i].x, path->ordered_point_arr[i].y);
//	}
//	destroy_path_points(path);

	printf("\n\nend\n");

	return 0;
}
