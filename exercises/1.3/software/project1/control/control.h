#ifndef CONTROL_H_
#define CONTROL_H_

#include "graph.h"
#include "button.h"

bool ROAD;

void init_control();
void s_listen();
void kb_listen();

int get_node(graph* graph);
int get_valid_vertex(graph* graph, Point p);

void load_from_sd();

#endif /* CONTROL_H_ */
