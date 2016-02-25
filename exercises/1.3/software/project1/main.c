#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "gps.h"
#include <unistd.h>

int main(void) {
	init_control();
	load_from_sd();
	s_listen();

	printf("\nDONE\n");
	return 0;
}
