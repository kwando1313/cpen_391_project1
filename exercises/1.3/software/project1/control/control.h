#ifndef CONTROL_H_
#define CONTROL_H_

void init_control();

void listen();

void do_info();

void do_dir(graph* graph);

void do_photo();

void do_about();

int get_button();

<<<<<<< HEAD
vertex get_node();
=======
int get_node(graph* graph);

//TODO: remove after sprint 1
graph* create_test_graph(void);
>>>>>>> ba9b23ebdfbe695602226e4daa5636085ea43ed7

#endif /* CONTROL_H_ */
