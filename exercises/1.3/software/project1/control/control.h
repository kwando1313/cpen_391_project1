#ifndef CONTROL_H_
#define CONTROL_H_


#define NO_RESPONSE 0
#define INFO 1
#define DIR 2
#define PHOTO 3
#define ABOUT 4

#include "graph.h"
#include "button.h"


void init_control();

void s_listen();
void kb_listen();

bool is_kb_butt(Button* butt);

int get_node(graph* graph);

int get_valid_vertex(graph* graph, Point p);

//TODO: remove after sprint 1
graph* create_test_graph(void);

#endif /* CONTROL_H_ */
