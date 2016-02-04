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

	init_control();
	listen();


	printf("\n\nend\n");

	return 0;
}
