#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "gps.h"

int main(void) {
	init_control();
	load_from_sd();
	//printf("I finished loading!");
	s_listen();

	printf("\nDONE\n");
	return 0;
}
