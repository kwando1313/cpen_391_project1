#ifndef CONTROL_H_
#define CONTROL_H_


#define NO_RESPONSE 0
#define INFO 1
#define DIR 2
#define PHOTO 3
#define ABOUT 4

#include "graph.h"


void init_control();

void listen();

// To remove after button fcns work
//int get_button();

int get_node(graph* graph);

int get_valid_vertex(graph* graph, Point p);

//TODO: remove after sprint 1
graph* create_test_graph(void);

#endif /* CONTROL_H_ */
