#ifndef CONTROL_H_
#define CONTROL_H_

void init_control();

void listen();

void do_info();

void do_dir(graph* graph);

void do_photo();

void do_about();

int get_button();

int get_node(graph* graph);

//TODO: remove after sprint 1
graph* draw_test_graph(void);

#endif /* CONTROL_H_ */
